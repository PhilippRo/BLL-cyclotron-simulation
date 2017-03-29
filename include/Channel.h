/*
 * Channel.h
 *
 *  Created on: 16.07.2016
 *      Author: philipp
 */

#ifndef CHANNEL_H_
#define CHANNEL_H_

#include <boost/thread.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/thread/mutex.hpp>
#include <deque>

namespace BLL {

/**
\brief der Channel ist ein Kommunikationsmedium für Zwischenthreadkommunikation

Der Channel basiert auf einer Standard-Doppeltverketten-Liste, die mit Mutexen
so geschützt ist, dass
sich weder der RAM füllt noch doppelter gleichzeitiger Zugriff auf die Liste
stattfinden kann.

\tparam T stellt dabei den Inhalt des Channels da.

*/
template <class T> class Channel {
private:
  /// Channelaktivität
  bool active;

  /// Inhalt
  std::deque<T> qu;

  /// Mutex zur Kontrolle des Channels
  boost::mutex writemutex;

  /// Bedingungen wenn der Channel warten muss
  boost::condition_variable read_cond;

  /// maximale Anzahl an Einträgen
  static constexpr int capacity{10000};

  /// aktuelle Größe
  int size;

public:
  /// der Standardkonstruktor
  Channel() : active{true}, size{0} {}

  /// der Destruktor
  ~Channel() {}

  /**
          \brief deaktiviert den Channel

          Die Methode macht den Channel unnutzbar.
  */
  void deactivate() {
    boost::mutex::scoped_lock lock(writemutex);

    active = false;

    // simulate a proper wake up
    size = capacity / 2;
    if (qu.size() == 0) {
      qu.push_back(T{});
    }
    read_cond.notify_all();
  }

  /**
     \brief gibt ein Element des Channels zurück

     Sollte der Channel leer sein, wird so lange gewartet, bis
     wieder ein Element im Channel ist.

     \return aktuelles Element
  */
  T read() {
    boost::mutex::scoped_lock lock(writemutex);

    // return, wenn nötig
    if (!active) {
      return T{};
    }

    // warted, bis ein Element im Channel ist
    // while um read_cond, da condition_variable spontan aufwachen kann
    while (size == 0) {
      read_cond.wait(lock);
    }

    // hole Objekt
    T ret{qu.front()};
    qu.pop_front();

    // reduziere size
    --size;
    read_cond.notify_all();
    return ret;
  }

  /**
     \brief schreibt ein Objekt in den Channel

     Sollte der Channel voll sein, warted die Methode solange, bis ein
     Element aus dem Channel entfernt wird.
     \param content das zu schreibende Objekt
  */
  void write(T content) {
    boost::mutex::scoped_lock lock(writemutex);

    if (!active) {
      return;
    }

    // warte, bis Channel nicht mehr vollständig gefüllt ist
    // while because of spontaniously wake up of condition variable
    while (size > capacity) {
      read_cond.wait(lock);
    }
    // schreibe Objekt
    qu.push_back(content);
    // erhöhe size
    ++size;
    read_cond.notify_all();
  }
};

} /* namespace BLL */

#endif /* CHANNEL_H_ */
