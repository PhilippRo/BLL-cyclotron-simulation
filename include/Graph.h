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

/**
\brief Graph ist eine Klasse, um Werte zu plotten

Graph ist eine Klasse, die an ein Window angeschlossen werden kann, um Punkte zu plotten.
Graph implementiert die Widget Klasse und ist als Hauptwidget für das Window gedacht.
Sie unterstützt nur positive Werte.

*/
class Graph : protected Widget{
public:

        /**
        \brief Konstruktor für manuelle Konfiguration

        Ruft initGraphController mit StdGraphController auf

        \param x X-Position des Graphen
        \param y Y-Position des Graphen
        \param width Breite des Graphen
        \param height Höhe des Graphen
        \param xOffset horizontaler Abstand zwischen dem Wertebereich und dem Rand des Graphen
        \param yOffset vertikaler Abstand zwischen dem Wertebereich und dem Rand des Graphen    
        */ 
	Graph(int x, int y, int width, int height
			, int xOffset, int yOffset);
	
        /**
        \brief  Standartkonstruktor

        Ruft initGraphController mit StdGraphController auf
        */
        Graph();

        /**
        \brief initialisiert den Graphkontroller

        Der Graphkontroller wird mit der Klasse im Templateargument initialisiert.
        Das Tenplateargument muss von StdGraphController erben.
        */
	template <class T>
	void initGraphController(){
                if(gCont != NULL){
                    delete gCont;
                }
		gCont = dynamic_cast<StdGraphController*>(new T());
                isStdGraphSetUp = true;
	}

	virtual ~Graph();

        /**
        \brief Malt den Inhalt des Graphen in das Window::instance() -> Window& Objekt

        */
	void render();

        /**
        \brief fügt dem Graphen einen Wert hinzu
 
        Hängt dem Graphkontroller des Graphen einen Punkt hinzu. Dieser Punkt wird dann durch void Graph::render() gemalt.

        \param p der anzuhängende BLL::Point
        */
	void operator<<(Point p);

	using BLL::Widget::x;
	using BLL::Widget::y;
	using BLL::Widget::xOffset;
	using BLL::Widget::yOffset;
	using BLL::Widget::width;
	using BLL::Widget::height;
	using BLL::Widget::name;

protected:

        ///die Punktesammlung
	std::vector <Point> points{0};
        
        /// die Schriftart für die Überschrift des Graphen
	sf::Font font;
        
        /// der Graphkontroller des Graphen
	StdGraphController* gCont;
        
        /// Status der Schriftart font
	bool isFontSetup = false;
        
	/// Status des Graphkontrollers
        bool isStdGraphSetUp = false;
};
}
#endif /* GRAPH_H_ */