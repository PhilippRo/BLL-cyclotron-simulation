/*
 * StdGraphController.h
 *
 *  Created on: 02.07.2016
 *      Author: philipp
 */

#ifndef STDGRAPHCONTROLLER_H_
#define STDGRAPHCONTROLLER_H_

#include <vector>
#include <Point.h>
#include <boost/thread.hpp>

namespace BLL {

/**
  \brief Standardimplementation eines GraphControllers

  Der StdGraphController übernimmt die Aufgaben die Punkte im Graphen zu verwalten.
  Seine Aufgaben sind das Aufnehmen, Ordnen und Bereitstellen von Punkten bzw.
  Punktsammelungen.
  Er muss dabei Threadsicher, schnell sein und auf den Speicherverbrauch achten.
  Diese Implementation erlaubt maximal 1000 Werte.
  Sollte dieser Wert überschritten werden, werden die überschüssigen Werte gelöscht.
*/
class StdGraphController {
protected:
        
        /**
           Wie viele Punkte nach einem Löschvorgang nicht aufgenommen werden. Dieser
           Wert vedoppelt sich nach jedem Löschvorgang. Wenn der Wert gleich 
           pointsFiltered ist, wird der neue Wert aufgenommen,
           Da ist notwending um die Werte repräsentativ zu halten.
           Der Startwert ist 1.
        */
	int pointsToFilter;
	
        /**
           vergleiche pointsToFilter.
           Dieser Wert wird bei jedem ignorierten Wert um 1 erhöht. Nachdem 
           pointsToFilter gleich pointsFiltered ist und der Wert aufgenommen ist,                  wird der Wert auf 1 zurückgesetz.
        */
        int pointsFiltered;
	

        ///Punkte des Controllers
        std::vector<BLL::Point> *points;
	
        ///locked den Contrainer
        boost::mutex mtx;
public:

        /**
           \brief gibt eine Kopie der Punkte zurück
	   \return eine Kopie der Punkte
        */
	std::vector<BLL::Point> getPoints();

        ///Standardkonstruktor
	StdGraphController();

        /**
            \brief Setzt den internen Punktecontainer. 
            Diese Methode ist für die Konfiguration im Graphen gedacht.
            Soll das Feld points auf p setzen.
            \param p der zusetzende Pointer
        */
	void setPoints(std::vector<BLL::Point>* p);

        /**
            \brief Fügt einen Punkte zum Container hinzu

            Diese Methode ist auch für das Löschen der überschüssigen Werte verantwortlich.

            \param p Der hinzuzufügende Punkt
        */
	virtual void operator<<(BLL::Point p);
	virtual ~StdGraphController();

        /**
            \brief gibt den maximalen Wert im Conatiner zurück.

	    Diese Implementation nutzt einen Sortieralgorithmus aus der 
	    Standardbibliothek.

            \return der maximale Wert
        */
	BLL::Point max();
};

} /* namespace BLL */

#endif /* STDGRAPHCONTROLLER_H_ */
