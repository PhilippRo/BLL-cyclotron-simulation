/*
 * Channel.h
 *
 *  Created on: 16.07.2016
 *      Author: philipp
 */

#ifndef CHANNEL_H_
#define CHANNEL_H_

#include <deque>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>


namespace BLL {

/**
\brief Channel ist ein Kommunikationsmedium für Zwischenthreadkommunikation

Der Channel basiert auf einer Standard-Doppeltverkette-Liste, die mit Mutexen so geschützt wird, dass
sich werder der RAM füllt noch doppelter gleichzeitiger Zugriff auf die Liste 
stattfinden kann.

\tparam T stellt dabei den Inhalt des Channels da.

*/
template<class T>
class Channel {
private:

        /// Channelaktivität
        bool active;

        /// Inhalt       
	std::deque<T> qu;

        /// Mutex zur Kontrolle des Channels
	boost::mutex writemutex;

        /// Bedingungen wenn der Channel warten muss
        boost::condition_variable read_cond;
        
        /// Maximale Anzahl an Einträgen
	static constexpr int capacity{10000};

        /// aktuelle Größe
        int size;

public:
        ///Standardkonstruktor
	Channel() : active{true}
                  , size{0} {
        }

        ///Destruktor
	~Channel() {	
		deactivate();
	}

	/**
		\brief deaktiviert den Channel

		macht den Channel unnutzbar.
	*/
	void deactivate(){
		boost::mutex::scoped_lock lock(writemutex);

		active = false;

		read_cond.notify_all();	
	}

	/**
           \brief Gibt ein Element des Channels zurück
 
           Sollte der Channel leer sein, wird so lange gewartet, bis 
           wieder ein Element im Channel ist

           \return aktuelles Element
        */
	T read(){
	        boost::mutex::scoped_lock lock(writemutex);

		//return, wenn nötig
		if(!active){
			return T{};
                }

                //warted, bis ein Element im Channel ist
                //while because of spontaniously wake up of condition_variable
	        while(size == 0 ){
                    read_cond.wait(lock);
                }
		
		//hole Objekt
		T ret{qu.front()};
		qu.pop_front();
		
                //reduziere size 
                --size;
                read_cond.notify_all();
		return ret;
	}

        /**
           \brief schreibt ein Objekt in den Channel

           Sollte der Channel voll sein warted die Methode, bis ein
	   Element aus dem Channel entfernt wird
           \param content das zu schreibende Objekt
        */
	void write(T content){
		boost::mutex::scoped_lock lock(writemutex);
 		
		if(!active){
			return;
                }

               //warte, bis Channel nicht mehr vollständig gefüllt ist
               //while because of spontaniously wake up of condition variable
		while(size > capacity){
			read_cond.wait(lock);
		}
                //schreibe Objekt
		qu.push_back(content);
                //erhöhe size
                ++size;
		read_cond.notify_all();
	}

};


} /* namespace BLL */

#endif /* CHANNEL_H_ */
