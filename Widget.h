/*
 * Widget.h
 *
 *  Created on: 17.05.2016
 *      Author: philipp
 */

#ifndef WIDGET_H_
#define WIDGET_H_

#include <string>

namespace BLL {

class Widget {
public:
	Widget();
	virtual ~Widget();

	virtual void render() = 0;

	int x,y,width,height, xOffset, yOffset;

	std::string name;

};

} /* namespace BLL */

#endif /* WIDGET_H_ */
