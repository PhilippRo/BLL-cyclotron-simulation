/*
 * Application.h
 *
 *  Created on: 30.05.2016
 *      Author: philipp
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include<Window.h>

namespace BLL {

class Application {
public:
	Application();
	virtual ~Application();

	void operator()();
	void operator()(int argc, char** argv);
};

} /* namespace BLL */

#endif /* APPLICATION_H_ */
