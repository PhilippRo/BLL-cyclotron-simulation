/*
 * Channel.h
 *
 *  Created on: 16.07.2016
 *      Author: philipp
 */

#ifndef CHANNEL_H_
#define CHANNEL_H_

#include <list>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>


namespace BLL {

/**
\brief Channel ist ein Kommunikationsmedium für Zwischenthreadkommunikation

Channel basiert auf einer Standartliste, die mit Mutexen so geschützt wird, dass
sich werder der RAM füllt noch doppelter gleichzeitiger Zugriff auf die Liste 
stattfinden kann.

T stellt dabei den Inhalt des Channels da.

*/
template<class T>
class Channel {
private:
        /// Inhalt       
	std::list<T> qu;

        /// Mutex zur Kontrolle des Channels
	boost::mutex writemutex;

        /// Bedingungen wenn der Channel warten muss
        boost::condition_variable read_cond;
        
        /// Maximale Anzahl an Einträgen
	int capaticity = 10000;

        /// aktuelle Größe
        int size = 0;

public:
        ///Standartkonstruktor
	Channel() {}

        ///Standartdestruktor
	~Channel() {}

	/**
           \brief Gibt ein Element des Channels zurück
 
           Sollte der Channel leer sein, wird so lange gewartet, bis 
           wieder ein Element im Channel ist

           \return aktuelles Element
        */
	T read(){
                boost::mutex::scoped_lock lock(writemutex);
                //warted, bis ein Element im Channel ist
		if(size == 0){
                    read_cond.wait(lock);
                }
                //hole Objekt
		T ret;
		ret = qu.front();
		qu.pop_front();
                //reduziere size 
                size--;
                read_cond.notify_all();
		return ret;
	}

        /**
           \brief schreibt ein Objekt in den Channel

           Sollte der Channel voll sein warted die Methode, bis ein
	   Element aus dem Channel entfernt wird.

           \param content das zu schreibende Objekt
        */
	void write(T content){
		boost::mutex::scoped_lock lock(writemutex);
                //warte, bis Channel nicht mehr vollständig gefüllt ist
		if(size > capaticity){
			read_cond.wait(lock);
		}
                //schreibe Objeckt
		qu.push_back(content);
                //erhöhe size
                size++;
		read_cond.notify_all();
	}

};

} /* namespace BLL */

#endif /* CHANNEL_H_ */
