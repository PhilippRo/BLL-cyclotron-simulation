/*
 * Application.h
 *
 *  Created on: 30.05.2016
 *      Author: philipp
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include<Window.h>

namespace BLL {

/**
   \brief Die Application 
   
   Klasse ist eine Klasse, die die Programmlogik in objektorientiert darstellt
   Application started und konfiguriert die anderen Programmteile.
*/
class Application {
public:
	Application();
	virtual ~Application();

	///\brief führt die Programmlogik ohne Parameter aus
        ///Standartbeispiel einer Simulation
        ///wird aufgerufen, wenn Programm ohne Parameter aufgerufen wird
	void operator()();

        /** \brief führt die Programmlogik mit den Parametern der Mainfunkion aus 
                   übergibt die Konsolenparameter an die Programmlogik 
             
            \param argc sollte argc der Mainfunktion sein
            \param argv sollte argv der Mainfunktion sein

        */
	void operator()(int argc, char** argv);
};

} /* namespace BLL */

#endif /* APPLICATION_H_ */
