/*
 * Point.h
 *
 *  Created on: 17.05.2016
 *      Author: philipp
 */

#ifndef POINT_H_
#define POINT_H_

#include <Double.h>

namespace BLL {

/** 
    \brief repräsentiert einen Punkt im Graphen
*/
class Point {
public:
        ///der Standardkonstruktor
	Point();
        /**
          \brief ein Konstruktor, der Point aus 2 Doubles erstellt

          \param paraX X-Wert des Punktes
          \param paraY Y-Wert des Punktes
        */
	Point(Double paraX, Double paraY);

        ///Copykonstruktor
        Point(const Point& o);
  
	virtual ~Point();


        /**
          \brief ein Getter für die X-Wert

          \return der X-Wert des Punktes
        */
	Double getX() const;
	
        /**
          \brief ein Getter für die Y-Wert

          \return der Y-Wert des Punktes
        */
        Double getY() const;

protected:

	/// der X-Wert
	Double x;

	/// der Y-Wert
	Double y;
};

} /* namespace BLL */

#endif /* POINT_H_ */
