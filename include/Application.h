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
   \brief Die Application
   
   Die Application-Klasse ist eine Klasse, die die Programmlogik in 
   objektorientierter Form darstellt.
   Außerdem started und konfiguriert sie die anderen Programmteile.
*/
class Application {
public:
	///Standardkonstruktor
	Application();
	virtual ~Application();

	///\brief führt die Programmlogik ohne Parameter aus
        ///Deshalb wird eine einfache Beispielsimulation gestartet und es werden 
	///Hinweise zur Benutzung ausgegeben
	void operator()();

        /** \brief führt die Programmlogik mit Parametern aus
             
            \param argc sollte argc der Mainfunktion sein
            \param argv sollte argv der Mainfunktion sein

        */
	void operator()(int argc, char** argv);
};

} /* namespace BLL */

#endif /* APPLICATION_H_ */
