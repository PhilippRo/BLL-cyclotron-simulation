/*
 * Window.cpp
 *
 *  Created on: 30.04.2016
 *      Author: philipp
 */

#include <Window.h>
#include <cstdlib>

namespace BLL {

Window::Window() { win = NULL; }

Window::~Window() {}

Graph *Window::getGraph(std::string name) {
  // wait until window is created;
  int size = this->graphName.size();
  for (int i = 0; i < size; i++) {
    if (this->graphName.at(i) == name)
      return &(this->graph[i]);
  }
  return NULL;
}

void Window::render() {
  // 25 fps
  if (renderTimer.getElapsedTime().asSeconds() < 0.04)
    return;
  win->clear(sf::Color::Black);
  for (unsigned int i = 0; i < graph.size(); i++) {
    graph[i].render();
  }
  this->win->display();
  renderTimer.restart();
}

void Window::create() {
  win = new sf::RenderWindow(sf::VideoMode::getFullscreenModes().at(0), "BLL",
                             sf::Style::Fullscreen);

  int y = sf::VideoMode::getDesktopMode().height;
  int x = sf::VideoMode::getDesktopMode().width;

  int n;
  if (graphName.size() < graphsInARow)
    n = 1;
  else {
    n = (graphName.size() / graphsInARow);
    n = graphName.size() % graphsInARow == 0 ? n : n + 1;
  }

  int xn =
      graphName.size() > this->graphsInARow ? graphsInARow : graphName.size();

  int xAdd = (int)x / xn;
  int yAdd = (int)y / n;

  int i = 0;
  for (int j = 0; j < n; j++) {
    for (int k = 0; k < xn; k++) {
      if (!((i < graphName.size()) && (i < graph.size())))
        return;
      graph[i].x = k * xAdd, graph[i].y = j * yAdd, graph[i].width = xAdd,
      graph[i].height = yAdd, graph[i].xOffset = xAdd * 0.1,
      graph[i].yOffset = yAdd * 0.1, graph[i].name = graphName[i];
      i++;
    }
  }
}

void Window::mainloop() {
  win->setActive(true);
  while (win->isOpen()) {
    while (win->pollEvent(ev)) {
      if (ev.type == sf::Event::KeyPressed) {
        win->capture().saveToFile("log_window.jpg");
        win->close();
      }
    }
    render();
  }
}

} /* namespace BLL */
