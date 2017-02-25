/*
 * Window.h
 *
 *  Created on: 30.04.2016
 *      Author: philipp
 */

#ifndef WINDOW_H_
#define WINDOW_H_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Graph.h>
#include <StdGraphController.h>
#include <vector>
#include <string>
#include <utility>

namespace BLL {
using namespace std;

/**
\brief Window ist ein Fenster mit Geometriemanager für Widgets

Das Hauptwidget für Window ist Graph und Window ist ein Singletonobjekt.
*/

class Window{

protected:

         /// Standardkonstructor (protected weil es sich um ein Singleton handelt)
	Window();       
	
	/// eine Uhr, um die Framerate festzulegen, damit nicht zu viel Zeit auf
	/// das Rendern der Graphen verschwendet wird
	sf::Clock renderTimer;

        /// ein Event, das lokal verwendet wird, um das Fenster auf Tastendruck zu
        /// schließen
	sf::Event ev;

	/// die Liste von Graphen, die verwaltet und gerendert werden
	vector<Graph> graph;

	/// eine Liste von Graphnamen, damit die Graphen verwaltet werden können
        /// der n-te Entrag der Liste ist der Name des n-ten Graphen
	vector<string> graphName;

	/// Variabel für die Geometrie
	unsigned int graphsInARow = 4;

public:

	/// Fenster, um die Werte zu rendern
	sf::RenderWindow* win;


  
	/// Destruktor
	virtual ~Window();

	// templates kompilieren nicht in einem cpp file bzw. g++ hat Probleme
	/**
		\brief Fügt einen Graphen hinzu

		Fügt einen Graphen mit dem GraphController vom Typ t zu dem Window hinzu

		\param name Name des Graphen

		\tparam t Typ des GraphController des Graphen

	*/
	template<class t>
	void addGraph(std::string name){
		this->graphName.push_back(name);
		Graph g;
		g.initGraphController<t>();
		this->graph.push_back(std::move(g));
	}

	/**
		\brief Getter für Graphen

		Gibt einen Graphen zurück.

		\param name Name des Graphen

		\return der entsprechende Graph
	*/
	Graph* getGraph(std::string name);

	/**
		\brief rendert die Punkte

		ruft für jeden Graphen die Methode render auf
	*/
	void render();

	/**
		\brief erstellt das Fenster

		ruft den Algorithmus für die Geometrie auf und überträgt die 
		errechneten Dimensionen auf die Graphen
	*/
	void create();

	/**
		\brief Mainloop des Fensters

		ruft die Methode Window::render auf, die nur 25 mal in der Sekunde 
		rendert und wartet auf einen Tastendruck, um dannach das Fenster zu 
		schließen.
	*/
	void mainloop();

	///Singleton typische Methode
	static Window& instance(){
		static Window win;
		return win;
	}
};

} /* namespace BLL */

#endif /* WINDOW_H_ */
