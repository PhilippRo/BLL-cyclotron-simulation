/*
 * Graph.h
 *
 *  Created on: 30.04.2016
 *      Author: philipp
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <SFML/Graphics.hpp>
#include <Widget.h>
#include <Point.h>
#include <StdGraphController.h>
#include <boost/thread.hpp>

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
        \brief ein Konstruktor für manuelle Konfiguration

        Ist als interner Konstruktor gedacht, um die Geometrie von dem
        Fenster zugewiesen zu bekommen. Er kann aber auch zur manuellen 
        Konfiguration eines Graphen verwendet werden.
        Er ruft initGraphController mit StdGraphController auf.

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
        \brief  der Standardkonstruktor

        Er ruft initGraphController mit StdGraphController auf.
        */
        Graph();

        Graph(const Graph& other);

        /**
        \brief initialisiert den Graphkontroller

        Der Graphkontroller wird mit der Klasse im Templateargument initialisiert.
        Das Tenplateargument muss von StdGraphController erben.

	\tparam T der GraphController, der eingerichtet werden soll.
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
        \brief malt den Inhalt des Graphen in das Window::instance() -> Window& Objekt

        */
	void render();

        /**
        \brief fügt dem Graphen einen Wert hinzu
 
        Hängt dem GraphController des Graphen einen Punkt an. Dieser Punkt wird dann durch void Graph::render() gemalt.

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
        
        /// die Schriftart für die Überschrift des Graphen
	sf::Font font;
        
        /// der GraphController des Graphen
	StdGraphController* gCont;
        
        /// Status der Schriftart font (ob font geladen ist)
	/// legt fest ob "Font.ttf" geladen werden muss
	bool isFontSetup = false;
        
	/// Status des GraphControllers (ist gCont ein Nullpointer)
	/// legt fest, ob ein neuer StdGraphController erstellt werden muss
        bool isStdGraphSetUp = false;

        /// ein Mutex für interne Sperrung
        boost::mutex graphMtx;
};
}
#endif /* GRAPH_H_ */
