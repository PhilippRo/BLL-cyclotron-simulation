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


/**
  \brief Basisklasse als Inhalt für das Window

  Die Klasse Graph erbt von dieser Klasse. Der Sinn dieser Klasse
  besteht in potentiellen Erweiterungen des Funktionsumpfangs des Windows.

*/
class Widget {
public:

        ///Standartkonstruktor
	Widget();

        ///Desktruktor sollte überschrieben werden
	virtual ~Widget();

        ///Methode, die in Window::instance().win rendert
	virtual void render() = 0;

        ///X-Startpostion des Widgets
	int x;
        ///Y-Startpostion des Widgets
        int y;
        ///Breite des Widgets
        int width;
        ///Hoehe des Widgets
        int height;
        ///Horizontialer Rand von Widgetrand zum eigentlichen Inhalt
        int xOffset;
        ///Horizontialer Rand von Widgetrand zum eigentlichen Inhalt
        int yOffset;

	///Ein interens Identifikationstoken
	std::string name;

};

} /* namespace BLL */

#endif /* WIDGET_H_ */
