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
  \brief diese Klasse ist die Basisklasse für Widgets in dem Window

  Die Klasse Graph erbt von dieser Klasse. Der Sinn dieser Klasse
  besteht in potentiellen (d.h. noch nicht implementierten)
  Erweiterungen des Funktionsumfangs des Windows.

*/
class Widget {
public:
  /// der Standardkonstruktor
  Widget();

  /// der Desktruktor sollte überschrieben werden
  virtual ~Widget();

  /// eine Methode, die in Window::instance().win rendert
  virtual void render() = 0;

  /// die X-Startpostion des Widgets
  int x;
  /// die Y-Startpostion des Widgets
  int y;
  /// die Breite des Widgets
  int width;
  /// die Höhe des Widgets
  int height;
  /// der Horizontialer Abstand von Widgetrand zum eigentlichen Inhalt
  int xOffset;
  /// der Horizontialer Abstand von Widgetrand zum eigentlichen Inhalt
  int yOffset;

  /// ein internes Identifikationstoken
  std::string name;
};

} /* namespace BLL */

#endif /* WIDGET_H_ */
