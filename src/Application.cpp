/*
 * Application.cpp
 *
 *  Created on: 30.05.2016
 *      Author: philipp
 */

#include <Application.h>
#include <StdGraphController.h>
#include <Zyklotron.h>
#include <ZyklotronController.h>
#include <boost/thread/thread.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

namespace BLL {

Application::Application() {}

Application::~Application() {}

void Application::operator()() {
  // Beispiel eines Zyklotrons (ohne Parameter)

  std::vector<std::string> str;
  str.push_back("Geschwindigkeit [m/s] (rel)");
  str.push_back("Umlaufzeit [s] (rel)");
  str.push_back("Beschleunigte Zeit [s] (rel)");
  str.push_back("kinetische Energie [N] (rel)");
  str.push_back("gesamte Energie [N] (rel)");
  str.push_back("Masse [kg] (rel)");

  std::vector<std::string> strc;
  strc.push_back("Geschwindigkeit [m/s] (cla)");
  strc.push_back("Umlaufzeit [s] (cla)");
  strc.push_back("Beschleunigte Zeit [m] (cla)");
  strc.push_back("kinetische Energie [N] (cla)");
  strc.push_back("gesamte Energie [N] (cla)");
  strc.push_back("Masse [kg] (cla)");

  ZyklotronController::instance().addZyklotron(str);
  ZyklotronController::instance().addZyklotron(strc);

  // like ab ab ab ab not aaaa bbbb
  ZyklotronController::instance().insertGraphs(true);

  Window::instance().create();

  ZyklotronController::instance().getZyklotron(0).setGraphNames(str);
  ZyklotronController::instance().getZyklotron(1).setGraphNames(strc);

  BLL::Window::instance().win->setActive(true);

  ZyklotronController::instance().getZyklotron(0).configure(
      // q u d v0 m0 b f
      Double(1.6, -19), Double(1.0, -1), Double(1.0, -2), Double(1.0, -1),
      Double(9.1, -31), Double(1.0, -1), Double(9, -11), 0.01, true);

  ZyklotronController::instance().getZyklotron(1).configure(
      // q u d v0 m0 b f
      Double(1.6, -19), Double(1.0, -1), Double(1.0, -2), Double(1.0, -1),
      Double(9.1, -31), Double(1.0, -1), Double(9, -11), 0.01, false);

  ZyklotronController::instance().run();

  Window::instance().mainloop();

  ZyklotronController::instance().shut_down();
}

void Application::operator()(int argc, char **argv) {
  // getting timeScale
  float tc = 1.0;
  for (int i = 0; i < (argc - 1); i++) {
    if (std::string(argv[i]) == "-timeScale")
      tc = std::stod(argv[i + 1]);
  }

  // Configuring Zyks
  for (int i = 0; 10 * (i + 1) < argc; i++) {
    std::string name(argv[2 + (i * 10)]);
    std::vector<std::string> str;
    // Titel der Graphen
    str.push_back(name + " Geschwindigkeit [m/s]");
    str.push_back(name + " Umlaufzeit [s]");
    str.push_back(name + " Beschleunigte Zeit [s]");
    str.push_back(name + " kinetische Energie [N]");
    str.push_back(name + " gesamte Energie [N]");
    str.push_back(name + " Masse [kg]");
    str.push_back(name + " Radius [m]");

    std::string typeStr(argv[1 + (i * 10)]);
    // Zykltron wird erstellt
    ZyklotronController::instance().addZyklotron(str);
    // dem aktuellen Zyklotron werden die Graphnamen gegeben
    ZyklotronController::instance().getZyklotron(i).setGraphNames(str);
    // der Zyklotron wird mit den entsprechenden Werten konfiguriert
    ZyklotronController::instance().getZyklotron(i).configure(
        Double(std::string(argv[3 + (i * 10)])),
        Double(std::string(argv[4 + (i * 10)])),
        Double(std::string(argv[5 + (i * 10)])),
        Double(std::string(argv[6 + (i * 10)])),
        Double(std::string(argv[7 + (i * 10)])),
        Double(std::string(argv[8 + (i * 10)])),
        Double(std::string(argv[9 + (i * 10)])), tc, typeStr == "-rel",
        Double(std::string(argv[10 + (i * 10)])));
  }
  ZyklotronController::instance().insertGraphs(true);
  Window::instance().create();
  ZyklotronController::instance().run();
  Window::instance().mainloop();

  ZyklotronController::instance().shut_down();
}

} /* namespace BLL */
