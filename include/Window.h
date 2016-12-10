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
#include <cstdlib>

namespace BLL {
using namespace std;

/**
\brief Window ist ein Fenster mit Geometriemanager für Widgets

Das Hauptwidget für Window ist Graph
*/
class Window{

protected:
	sf::Clock renderTimer;
	sf::Event ev;
	vector<Graph> graph;
	vector<string> graphName;
	vector<StdGraphController*> graphController;
	unsigned int graphsInARow = 4;

public:
	sf::RenderWindow* win;

	Window();
	virtual ~Window();

	// templates kompilieren nicht in einem cpp file
	template<class t>
	void addGraph(std::string name){
		this->graphName.push_back(name);
		Graph g;
		g.initGraphController<t>();
		this->graph.push_back(g);
	}

	Graph* getGraph(std::string name);
	void render();
	void create();
	void mainloop();

	static Window& instance(){
		static Window win;
		return win;
	}
};

} /* namespace BLL */

#endif /* WINDOW_H_ */
