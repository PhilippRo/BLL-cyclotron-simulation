/*
 * Graph.cpp
 *
 *  Created on: 30.04.2016
 *      Author: philipp
 */

#include "Graph.h"
#include <SFML/System/Vector2.hpp>
#include <Window.h>
#include <string>

BLL::Graph::Graph(int x, int y, int width, int height
		, int xOffset, int yOffset) {
	Graph();
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->xOffset = xOffset;
	this->yOffset = yOffset;
}

BLL::Graph::Graph()
		/*: points()*/ {
	this->x = 0;
	this->y = 0;
	this->width = 0;
	this->height = 0;
	this->xOffset = 0;
        this->gCont = 0;
	this->initGraphController<BLL::StdGraphController>();
}

BLL::Graph::~Graph() {
	// TODO Auto-generated destructor stub
}

void BLL::Graph::operator<<(BLL::Point p){
	if(this == 0)
		return;	

	if(! isStdGraphSetUp){
	    std::cout << "error: Graph is not configured" << std::endl;
            return;
        }
	if(gCont != 0)
		(*gCont) << (p);
}

void BLL::Graph::render(){

	if (!isFontSetup){
		font.loadFromFile("font.ttf");
		isFontSetup = true;
	}
	
	points = gCont->getPoints();
	
	sf::Text text(name, font, 16);
	text.setPosition(x+xOffset,y);
	Window::instance().win->draw(text);

	//draw the axis
	sf::VertexArray units(sf::Lines,4);
    units[0].position =  sf::Vector2f(x+(2*xOffset), y+yOffset);
	units[1].position = sf::Vector2f(x+(2*xOffset), y+(height-yOffset));
	units[2].position =  sf::Vector2f(x+xOffset, y+height-(2*yOffset));
	units[3].position = sf::Vector2f(x+width-xOffset, y+height-(2*yOffset) );
	Window::instance().win->draw(units);

	//draw the units
	std::vector<sf::Text> texte;
	sf::VertexArray units2 (sf::Lines, 20);
	for (double i = 1.0; i < 5.0; i += 1.0){
		units2[(i*4)] = sf::Vector2f(x + 1.75 * xOffset , y + yOffset + ( ((i/5) * (height-3*yOffset))));
		units2[(i*4) + 1] = sf::Vector2f(x + 2.25 * xOffset , y + yOffset + ( (i/5) * (height-3*yOffset)));
		if(points.size() > 0){
			Double d{std::move((points.at(points.size() - 1)).getY())};
			d.value *= ((i/5));
			sf::Text t1(d.toString(),font, 9);
			t1.setPosition(x + 0.75 * xOffset , y + yOffset + ( (((5-i)/5) * (height-3*yOffset))));
			Window::instance().win->draw(t1);
			d = std::move((points.at(points.size() - 1)).getX());
			d.value *= ((i/5));
			sf::Text t2(d.toString(),font, 9);
			t2.setPosition( x+ width - (2*xOffset)- ( ((5-i)/5) * (width - 3*xOffset)), y + height - 1.75 * yOffset );
			Window::instance().win->draw(t2);
		}
		units2[(i*4) + 2] = sf::Vector2f( x+ width - xOffset- ( (i/5) * (width - 3*xOffset)), y + height - 1.75 * yOffset );
		units2[(i*4) + 3 ] = sf::Vector2f(x+ width - xOffset -( (i/5) * (width - 3*xOffset)), y + height - 2.25 * yOffset);
	}
	Window::instance().win->draw(units2);

	//draw points
	sf::VertexArray points(sf::LinesStrip, this->points.size());
	const BLL::Point& max = gCont->max();
	for( int i = 0; i< points.getVertexCount(); i++){
		points[i].position = sf::Vector2f(
		 x + 2*xOffset + ((this->points.at(i).getX() / max.getX()).toStd() * (width-3*xOffset)),
		 y+ height - (2*yOffset) - ( ((this->points.at(i).getY() / max.getY()).toStd() * (height - 3*yOffset))));
	}
	Window::instance().win->draw(points);
}
