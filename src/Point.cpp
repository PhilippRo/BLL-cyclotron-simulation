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

Point::~Point() {
	// TODO Auto-generated destructor stub
}

Double Point::getX(){
	return x; //Value von x KEINE referenz
}

Double Point::getY(){
	return y; //Value von x KEINE referenz
}

} /* namespace BLL */
