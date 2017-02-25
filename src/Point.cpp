/*
 * Point.cpp
 *
 *  Created on: 17.05.2016
 *      Author: philipp
 */

#include <Point.h>

namespace BLL {

Point::Point() {
	// TODO Auto-generated constructor stub

}

Point::Point(Double paraX, Double paraY){
	x = paraX;
	y = paraY;
}

Point::Point(const Point& o) : x(o.x)
                        , y(o.y) {
}

Point::~Point(){
}

Double Point::getX() const{
	return x; //Value von x KEINE referenz
}

Double Point::getY() const{
	return y; //Value von x KEINE referenz
}

} /* namespace BLL */
