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
#include <queue>
#include <boost/thread.hpp>

#include <vector>
#include <string>

namespace BLL {

namespace ZyklotronParts{
        /*!
            \brief Das ZykSet
 
            Das ZykSet ist eine Menge von Messdaten, die zwischen dem Berechnungsthread 
	    und dem dem Managementthread ausgetauscht werden. (vgl. Zyklotron)

	    Das ZykSet ist eine Plain-Old-Data-Klasse (kurz POD).
            
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

/**
	\brief das eigentliche Zyklotron

	Diese Klasse stellt das eigentliche Zyklotron da und implementiert ein
	relativisches und ein klassisches Modell für ein Zyklotron


*/
class Zyklotron {

protected:

	/// hält fest, ob das Zyklotron schon konfiguriert wurde
	bool configured = false;
	
	///Ladung des Beschleunigten Teilchens
	Double q;

	///Beschleunigungsspannung des Kondensators
	Double u;

	///Breite des Beschleunigungskondensators
	Double d; 

	///Eintritsgeschwindigkeit des Teilchens (Startgeschwindigkeit)
	Double v0;

	///Ruhemasse des Teilchens
	Double m0;

	///Stärke des Magnetfeldes
	Double b;

	///Frequenz, mit der das Vorzeichen der Spannung am Kondensator geändert wird
	Double f;

	///Beschleunigung im Kondensator
	Double a0;

	///Zeitmaßstab: gibt die Möglichkeit die Simulation zu verlangsamen 
	///oder zu beschleunigen
	float timeScale = 1.0;

	///Channel für die Kommunikation zwischen clalcThread und thisThread
	BLL::Channel<ZyklotronParts::ZykSet>* chan;

	///Auf dem clacThread läuft die eigentliche Berechnung
	boost::thread *calcThread;

	///Auf dem thisThread kommuniziert das Zyklotron mit dem Fenster
	boost::thread *thisThread;

	///Die Namen der Graphen, die von dem Zyklotron gefüllt werden
	std::vector <std::string> names;

	///Legt fest, ob das relativistische Modell verwendet wird
	bool relativistic=true;

public:

	///Standardkonstruktor	
	Zyklotron();
	
	///Destruktor
	/// fährt das Zyklotron runter
	virtual ~Zyklotron();

	/**
		\brief konfiguriert das Zyklotron

		Die Methode konfiguriert das Zyklotron mit den Parametern:

		\param paraQ die Ladung des Teilchens

		\param paraU die Behschleunigungsspannung

		\param paraD die Breite des Beschleunigungskondensators

		\param paraV0 die Eintrittsgeschwindigkeit in das Zyklotron

		\param paraM0 die Ruhemasse des Teilchens

		\param paraB Stärke des Magnetfeldes

		\param paraF Frequenz mit der die Spannung am Kondensator geändert wird

		\param PTimeScale der Zeitmaßstab

		\param pRelativistic wählt das Modell (setzt relativistic)
	*/
	void configure(Double paraQ, Double paraU,
			Double paraD, Double paraV0, Double paraM0, Double paraB, Double paraF, float PTimeScale, bool pRelativistic );

	/**
		\brief konfiguriert das Zyklotron

		Die Methode konfiguriert das Zyklotron mit den Werten

		\param paraQ die Ladung des Teilchens

		\param paraU die Behschleunigungsspannung

		\param paraD die Breite des Beschleunigungskondensators

		\param paraV0 die Eintrittsgeschwindigkeit in das Zyklotron

		\param paraM0 die Ruhemasse des Teilchens

		\param paraB Stärke des Magnetfeldes

		\param paraF Frequenz mit der die Spannung am Kondensator geändert wird

		\param PTimeScale der Zeitmaßstab
	*/
	void configure(Double paraQ, Double paraU,
			Double paraD, Double paraV0, Double paraM0, Double paraB, Double paraF, float PTimeScale);

	/**
		\brief startet das Zyklotron

		diese Methode startet das Zykotron und damit die Threads thisThread und
		calcThread

		Sie gibt calcThrad die Methode clac als Code und thisThread ein Lamda,
		das aus chan ließt und die Werte an die Graphen übergibt.

	*/
	void run();


	/**
		\brief berechnet Werte

		Diese Methode berechnet die Werte für die Simulation und ist der Code 
		für den calcThread

		Sie schreibt in den Channel chan
	*/
	void calc();

	/**
		\brief Setter für die Graphnames

		\param names Namen der Graphen
	*/
	void setGraphNames(std::vector <std::string> names );


};

} /* namespace BLL */

#endif /* ZYKLOTRON_H_ */
