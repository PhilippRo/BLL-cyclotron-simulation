/*
 * Zyklotron.h
 *
 *  Created on: 17.05.2016
 *      Author: philipp
 *
 */

#ifndef ZYKLOTRON_H_
#define ZYKLOTRON_H_

#include <Point.h>
#include <Channel.h>
#include <boost/thread.hpp>

#include <vector>
#include <string>

namespace BLL {

namespace ZyklotronParts{
        /*!
            \brief das ZykSet
 
            Das ZykSet ist eine Menge von Messdaten, die zwischen dem Berechnungsthread 
	    und dem dem Verwaltungsthread ausgetauscht werden. (vgl. Zyklotron)

	    Das ZykSet ist eine Plain-Old-Data-Klasse (kurz POD).
            
        */
	class ZykSet{
		//POD attributes meant to be public
		public:
                        ///der Standardkonstruktor
                        ZykSet();
                        ///der Copykonstruktor
                        ZykSet(const ZykSet& o);

                        /// der Zeitpunkt, wenn die Datenmenge valide ist, in Sekunden
			Double time;
                        /// die Geschwindigkeit in Metern pro Sekunde
			Double v;
                        /// zurückgelegte Strecke in Metern
			Double s;
                        /// kinetische Energie in Joule
			Double ke;
			/// aktuelle Masse in Kilogramm (Basiseinheit) 
                        Double me;
                        /// gesamt Energie in Joule
			Double re;
                        /// der Radius in Metern
			Double r;
                        /// die Umlaufzeit in Sekunden
			Double roundtime;
                        /// beschleunigte Zeit im Kondesator in Sekunden
			Double timeInCondensator;
	};
}

/**
	\brief das eigentliche Zyklotron

	Diese Klasse stellt das eigentliche Zyklotron dar und implementiert ein
	relativistisches und ein klassisches Modell eines Zyklotrons.

*/
class Zyklotron {

protected:

	/// hält fest, ob das Zyklotron schon konfiguriert wurde
	bool configured = false;
	
	///die Ladung des beschleunigten Teilchens
	Double q;

	///die Beschleunigungsspannung des Kondensators
	Double u;

	///die Breite des Beschleunigungskondensators
	Double d; 

	///die Eintrittsgeschwindigkeit des Teilchens (Startgeschwindigkeit)
	Double v0;

	///die Ruhemasse des Teilchens
	Double m0;

	///die Stärke des Magnetfeldes
	Double b;

	///die Frequenz, mit der das Vorzeichen der Spannung am Kondensator geändert wird
	Double f;

	///die Beschleunigung im Kondensator
	Double a0;

	///der Radius des Zyklotrons
	Double r_max;

	///der Zeitmaßstab legt die Abbildung der simulierten auf der realen Zeit fest
	float timeScale = 1.0;

	///der Channel für die Kommunikation zwischen calcThread und thisThread
	BLL::Channel<ZyklotronParts::ZykSet>* chan;

	///auf dem calcThread läuft die eigentliche Berechnung
	boost::thread *calcThread;

	///auf dem thisThread kommuniziert das Zyklotron mit dem Fenster
	boost::thread *thisThread;

	///die Namen der Graphen, die von dem Zyklotron gefüllt werden
	std::vector <std::string> names;

	///legt fest, ob das relativistische Modell verwendet wird
	bool relativistic;

        ///legt fest, ab das Zyklotron noch läuft
        boost::atomic<bool> running{true};

        ///finales Ergebnis der Simulation
        boost::atomic<ZyklotronParts::ZykSet> to_log;

public:

	///der Standardkonstruktor	
	Zyklotron();
	
	/**	\brief der Destruktor

		Es muss noch shutdown() aufgerufen werden, da das Herunterfahren der
        	Threads Exceptions werfen kann und es nötig Threads zu beenden, bevor sie
        	gelöscht werden.
	*/
	virtual ~Zyklotron();

        /** 
		\brief fährt die Threads herunter

		Shutdown setzt das Feld running auf false und beendet die internen Threads.
        */
        void shutdown();

	/**
		\brief konfiguriert das Zyklotron

		Die Methode konfiguriert das Zyklotron mit den angegebenen Parametern.

		\param paraQ die Ladung des Teilchens

		\param paraU die Beschleunigungsspannung

		\param paraD die Breite des Beschleunigungskondensators

		\param paraV0 die Eintrittsgeschwindigkeit in das Zyklotron

		\param paraM0 die Ruhemasse des Teilchens

		\param paraB Stärke des Magnetfeldes

		\param paraF Frequenz mit der die Spannung am Kondensator geändert wird

		\param PTimeScale der Zeitmaßstab

		\param pRelativistic wählt das Modell (setzt das Feld relativistic)

		\param paraR setzt den maximalen Umlaufradius im Zyklotron
	*/
	void configure(Double paraQ, Double paraU,
			Double paraD, Double paraV0, Double paraM0, Double paraB, Double paraF, float PTimeScale, 
                        bool pRelativistic = true, Double paraR = Double{1.0, 0});

	/**
		\brief startet das Zyklotron

		Diese Methode startet das Zykotron und damit die Threads thisThread und
		calcThread.

		Sie gibt calcThrad die Methode clac als Code und thisThread ein Lamda,
		das aus chan liest und die Werte an die Graphen übergibt.

	*/
	void run();


	/**
		\brief berechnet Werte

		Diese Methode berechnet die Werte für die Simulation und ist der Code 
		für den calcThread.

		Sie schreibt die Teilergebnisse in den Channel chan.
	*/
	void calc();

	/**
		\brief ein Setter für die Graphnamen

		\param names Namen der Graphen
	*/
	void setGraphNames(std::vector <std::string> names );


};

} /* namespace BLL */

#endif /* ZYKLOTRON_H_ */
