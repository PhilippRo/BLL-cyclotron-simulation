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
  \brief eine Standardimplementation eines GraphControllers

  Der StdGraphController übernimmt die Verwaltung von Punkten im Graphen.
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
           Wert vedoppelt sich nach jedem Löschvorgang. Ein Löschvorgang wird aufgerufen,
           wenn die Anzahl der Punkte größer als 1000 ist.
           Der Startwert ist 1.
        */
	int pointsToFilter;
	
        /**
            Dieser Wert zählt Punkte, die von dem StdGraphController ignoriert wurden.
            Bei jedem ignorierten Wert wird pointsFiltered um eins erhöht. Wenn pointsFiltered
            gleich pointsToFilter sind wird ein Wert aufgenommen und pointsFiltered auf 1 gesetzt.
        */
        int pointsFiltered;
	

        ///die Punkte des Controllers
        std::vector<BLL::Point> *points;
	
        ///lockt den Contrainer
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
            Die Methode übernimmt die Ownerschip von p. Das heißt der die Klasse
            kann wird p bei erneuten Aufrufen von setPoints oder im Destruktor p löschen.
            \param p der zusetzende Pointer
        */
	void setPoints(std::vector<BLL::Point>* p);

        /**
            \brief fügt einen Punkte zum Container hinzu

            Diese Methode fügt wenn alle Bedingungen erfüllt sind einen Punkt der Punktesammlung
            hinzu. Sind die Bedingungen nicht erfüllt wird der Punkte einfach ignoriert.
            Diese Methode ist auch für das Löschen der überschüssigen Werte verantwortlich.
            (Siehe pointsFiltered und pointsToFilter)

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
