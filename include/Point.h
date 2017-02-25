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
    \brief Repräsentiert einen Punkt im Graphen
*/
class Point {
public:
        ///Standardkonstruktor
	Point();
        /**
          \brief Konstruktor

          \param paraX X-Koordinate des Punktes
          \param paraY Y-Koordinate des Punktes
        */
	Point(Double paraX, Double paraY);

        ///Copykonstruktor
        Point(const Point& o);
  
	virtual ~Point();


        /**
          Getter für die X-Koordinate

          \return der X-Wert des Punktes
        */
	Double getX() const;
	
        /**
          Getter für die Y-Koordinate

          \return der Y-Wert des Punktes
        */
        Double getY() const;

protected:
	///Der X-Wert
	Double x;
	///Der Y-Wert
	Double y;
};

} /* namespace BLL */

#endif /* POINT_H_ */
