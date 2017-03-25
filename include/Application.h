/*
 * Application.h
 *
 *  Created on: 30.05.2016
 *      Author: philipp
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

namespace BLL {

/**
   \brief die Application oder Implementierung der Programmlogik 
   
   Die Application-Klasse ist eine Klasse, die die Programmlogik in 
   objektorientierter Form darstellt.
   Sie started und konfiguriert sie die anderen Programmteile.
*/
class Application {
public:
	///der Standardkonstruktor
	Application();
	virtual ~Application();

	///\brief führt die Programmlogik ohne Parameter aus
        ///Die Methode startet eine einfache Beispielsimulation und
        ///gibt Hinweise zur Bedienung aus.  
        void operator()();

        /** \brief führt die Programmlogik mit Parametern aus
            
            Die Methode started die Programmlogik mit Parametern, die die
            Simulation konfigurieren. Es können beliebig Zyklotrone über diese
            Methode gestartet werden. Ein Zyklotron wird folgendermaßen konfiguriert:
            -[rel/cla] [Name] [Ladung] [Beschleunigungsspannung] [Breite des Kondensators] 
            [Startgeschwindigkeit] [Ruhemasse] [Magnetfeld] [Frequenz] [Radius] 

            Am Ende kann Wahlweise noch ein Zeitmaßstab mit -timeScale angegeben werden

            \param argc Anzahl der Parameter; sollte argc der Mainfunktion sein
            \param argv Paramter als Cstringarray; sollte argv der Mainfunktion sein

        */
	void operator()(int argc, char** argv);
};

} /* namespace BLL */

#endif /* APPLICATION_H_ */
