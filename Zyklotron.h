/*
 * Zyklotron.h
 *
 *  Created on: 17.05.2016
 *      Author: philipp
 *
 *  Wird wie eine PointBuiĺder im Sachzusammenhang benutzt
 *
 *  Dadurch, dass private Felder in der Klassse Point nur durch Kinder der Klasse
 *  Point verändert werden können, aber in dem Programm nur die Klasse Zyklotron
 *  die Klasse Point beerbt, kann nur der Zyklotron Punkte verändern.
 *
 *  Das ist nötig, da der Zyklotron und das Window in verschieden Thread laufen werden
 *  und durch die Klaase Application verbunden werden, ein Thread sicheres Prinzip gefunden
 *  werden muss.
 *
 *  Ein Grundprinzip von Threadsicherheit is:
 *  	Einer Schreibt
 *  	Alle lesen.
 *
 *  Nur der Zyklotron kann Punkte schreiben, aber jeder kann Punkte lesen.
 */

#ifndef ZYKLOTRON_H_
#define ZYKLOTRON_H_

#include <Point.h>
#include <Channel.h>
#include <queue>
#include <boost/thread.hpp>

#include <vector>
#include <string>

namespace BLL {

namespace ZyklotronParts{
        /*!
            Das ZykSet <br /> 
            ist eine Menge von Messdaten, die zwischen dem Berechnungsthread und dem 
            dem ManagementThread ausgetauscht werden
            
        */
	class ZykSet{
		//POD attributes meant to be public
		public:
                        /// der Zeitpunkt, wenn die Datenmenge valide ist, in Sekunden
			Double time;
                        /// Geschwindigkeit in Metern pro Sekunde
			Double v;
                        /// zurückgelegte Strecke in Metern
			Double s;
                        /// kinetische Energie in Joule
			Double ke;
			/// aktuelle Masse in Kilogramm (Basiseinheit) 
                        Double me;
                        /// gesamt Energie in Joule
			Double re;
                        /// Radius in Metern
			Double r;
                        /// Umlaufzeit in Sekunden
			Double roundtime;
                        /// beschleunigte Zeit im Kondesator
			Double timeInCondensator;
	};
}

class Zyklotron {

private :

	bool configured = false;
	//static configureable values
	Double q, u, d, v0, m0, b, f;

	//static non-personal configureable values
	Double a0;

	float timeScale = 1.0;

	BLL::Channel<ZyklotronParts::ZykSet>* chan;
	boost::thread *calcThread;

	std::vector <std::string> names;

	bool relativistic=true;
public:
	
	Zyklotron();
	virtual ~Zyklotron();

	void configure(Double paraQ, Double paraU,
			Double paraD, Double paraV0, Double paraM0, Double paraB, Double paraF, float PTimeScale, bool pRelativistic );

void configure(Double paraQ, Double paraU,
			Double paraD, Double paraV0, Double paraM0, Double paraB, Double paraF, float PTimeScale);

	void run();

	void calc();

	void setGraphNames(std::vector <std::string>);
};

} /* namespace BLL */

#endif /* ZYKLOTRON_H_ */
