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

class Point {
public:
	Point();
	Point(Double paraX, Double paraY);
	virtual ~Point();

	Double getX();
	Double getY();

protected:
	Double x;
	Double y;
};

} /* namespace BLL */

#endif /* POINT_H_ */
