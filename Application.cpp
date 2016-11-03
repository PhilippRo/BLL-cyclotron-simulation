/*
 * Application.cpp
 *
 *  Created on: 30.05.2016
 *      Author: philipp
 */

#include <Application.h>
#include <SFML/Graphics.hpp>
#include <Graph.h>
#include <iostream>
#include <cstdlib>
#include <iostream>
#include <Zyklotron.h>
#include <ZyklotronController.h>
#include <StdGraphController.h>
#include <boost/thread/thread.hpp>
#include <X11/Xlib.h>
#include <vector>
#include <string>

namespace BLL {

typedef struct mainloopAppl{
public:
	void operator()(){
		BLL::Window::instance().mainloop();
	}
} mainloopAppl;

Application::Application() {
	// TODO Auto-generated constructor stub

}

Application::~Application() {
	// TODO Auto-generated destructor stub
}

void Application::operator ()(){
	//BLL::Window::instance().addGraph<StdGraphController>("Beschleunigung [m/ s^2]");
	std::vector <std::string> str;
	str.push_back("Geschwindigkeit [m/s] (rel)");
	str.push_back("Umlaufzeit [s] (rel)");
	str.push_back("Beschleunigte Zeit [s] (rel)");
	str.push_back("kinetische Energie [N] (rel)");
	str.push_back("gesamte Energie [N] (rel)");
	str.push_back("Masse [kg] (rel)");
	//str.push_back("Umlaufzeit [s] (rel)");

	std::vector <std::string> strc;
	strc.push_back("Geschwindigkeit [m/s] (cla)");
	strc.push_back("Umlaufzeit [s] (cla)");
	strc.push_back("Beschleunigte Zeit [m] (cla)");
	strc.push_back("kinetische Energie [N] (cla)");
	strc.push_back("gesamte Energie [N] (cla)");
	strc.push_back("Masse [kg] (cla)");
	//strc.push_back("Umlaufzeit [s] (cla)");

	ZyklotronController::instance().addZyklotron(str);
	ZyklotronController::instance().addZyklotron(strc);
	
	//like ab ab ab ab not aaaa bbbb
	ZyklotronController::instance().insertGraphs(true);
	
	Window::instance().create();	
	
	ZyklotronController::instance().getZyklotron(0).setGraphNames(str);	
	ZyklotronController::instance().getZyklotron(1).setGraphNames(strc);
	
	BLL::Window::instance().win->setActive(true);
	
	ZyklotronController::instance().getZyklotron(0).configure(
		// q u d v0 m0 b f
		Double(1.6, -19.0),Double(1.0,-1.0),
		Double(1.0, -2.0),Double(1.0, -1.0),
		Double(9.1, -31.0), Double(1.0,-1.0),
		Double(9, -11.0), 0.01, true);

	ZyklotronController::instance().getZyklotron(1).configure(
		// q u d v0 m0 b f
		Double(1.6, -19.0),Double(1.0,-1.0),
		Double(1.0, -2.0),Double(1.0, -1.0),
		Double(9.1, -31.0), Double(1.0,-1.0),
		Double(9, -11.0), 0.01, false);

//	new boost::thread([](){ZyklotronController::instance().getZyklotron(0).run();});

//	new boost::thread([](){ZyklotronController::instance().getZyklotron(1).run();});
	ZyklotronController::instance().run();

	Window::instance().mainloop();
	//thr.join();

}

void Application::operator()(int argc, char** argv){
	//getting timeScale
	float tc = 1.0;
	for(int i = 0; i < (argc-1); i++){
		if(std::string(argv[i]) == "-timeScale")
			tc = std::stod(argv[i+1]);
	}

	//Configuring Zyks
	for(int i = 0; 9*(i+1) <argc ; i++ ){
		std::string name(argv[2 + (i*9)]);
		std::vector <std::string> str;
		str.push_back(name + " Geschwindigkeit [m/s]");
		str.push_back(name + " Umlaufzeit [s]");
		str.push_back(name + " Beschleunigte Zeit [s]");
		str.push_back(name + " kinetische Energie [N]");
		str.push_back(name + " gesamte Energie [N]");
		str.push_back(name + " Masse [kg]");

		std::string typeStr(argv[1 + (i*9)]);
		ZyklotronController::instance().addZyklotron(str);
		ZyklotronController::instance().getZyklotron(i).setGraphNames(str);
		ZyklotronController::instance().getZyklotron(i).configure(
			Double(std::string(argv[3 + (i*9)])),
			Double(std::string(argv[4 + (i*9)])),
			Double(std::string(argv[5 + (i*9)])),
			Double(std::string(argv[6 + (i*9)])),
			Double(std::string(argv[7 + (i*9)])),
			Double(std::string(argv[8 + (i*9)])),
			Double(std::string(argv[9 + (i*9)])),
			tc,
			typeStr == "-rel"
		);
	}
	ZyklotronController::instance().insertGraphs(true);
	Window::instance().create();
	ZyklotronController::instance().run();
	Window::instance().mainloop();
}

} /* namespace BLL */
