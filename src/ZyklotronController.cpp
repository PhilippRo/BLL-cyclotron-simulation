#include <ZyklotronController.h>
#include <boost/thread.hpp>

namespace BLL{

ZyklotronController::ZyklotronController(){}

void ZyklotronController::shut_down(){
	for(int i = 0; i < zyks.size(); i++){
		if(zyks[i] != 0)
			delete zyks[i];
	}

}

ZyklotronController::~ZyklotronController(){

}

void ZyklotronController::addZyklotron(std::vector<std::string> strs){
	names.push_back(strs);
	auto zyk = new Zyklotron();
	zyk->setGraphNames(strs);
	zyks.push_back(zyk);
}

Zyklotron& ZyklotronController::getZyklotron(int index){
	return *zyks[index];
}

void ZyklotronController::run(){
	if(zyks.size() == 0){
		return;
	}
	for(int i = 0; i < zyks.size(); i++){
		zyks[i]->run();
	}
}
	/* if true set GraphsNames of Zyk 1,2 3:
		123 123 123
	 
	   else
		111 222 333

	*/
	void ZyklotronController::insertGraphs(bool order){
		if(order){
			bool finish = false;
			int index = 0;
			while( !finish){
				finish = true;
				for(int zyk = 0; zyk < zyks.size(); zyk++){
					if(index < names[zyk].size()){
						Window::instance().addGraph<StdGraphController>(names[zyk][index]);
						finish = false;
					}
				}
				index ++;
			}
		}
	}
}
