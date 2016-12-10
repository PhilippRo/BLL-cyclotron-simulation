#ifndef ZYKLOTRON_CONTROLLER_H 
#define ZYKLOTRON_CONTROLLER_H

#include <Zyklotron.h>
#include <Window.h>
#include <Graph.h>
#include <StdGraphController.h>

#include <vector>
#include <string>

namespace BLL{

class ZyklotronController{
protected:
	std::vector<Zyklotron*> zyks;
	
	ZyklotronController();

	~ZyklotronController();
	
	std::vector<std::vector<std::string>> names;

public:
	static ZyklotronController& instance(){
		static ZyklotronController staticThis;
		return staticThis;
	}

	void addZyklotron(std::vector<std::string> strs);
	Zyklotron& getZyklotron(int index);
	void run();
	/* if true set GraphsNames of Zyk 1,2 3:
		123 123 123
	 
	   else
		111 222 333

	*/
	void insertGraphs(bool order);

	void shut_down();
};

}
#endif
