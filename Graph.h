/*
 * Graph.h
 *
 *  Created on: 30.04.2016
 *      Author: philipp
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <Widget.h>
#include <Point.h>
#include <StdGraphController.h>
#include <iostream>

namespace BLL {
class Graph : protected Widget{
public:

	Graph(int x, int y, int width, int height
			, int xOffset, int yOffset);
	Graph();

	template <class T>
	void initGraphController(){
		gCont = dynamic_cast<StdGraphController*>(new T());
	}

	virtual ~Graph();

	void render();
	void operator<<(Point p);

	using BLL::Widget::x;
	using BLL::Widget::y;
	using BLL::Widget::xOffset;
	using BLL::Widget::yOffset;
	using BLL::Widget::width;
	using BLL::Widget::height;
	using BLL::Widget::name;

protected:
	std::vector <Point> points{0};
	sf::Font font;
	StdGraphController* gCont;
	bool isFontSetup = false;
	bool isStdGraphSetUp = false;
};
}
#endif /* GRAPH_H_ */
