/*
 * main.cpp
 *
 *  Created on: 07.04.2016
 *      Author: philipp
 */

#include <Application.h>
#include<iostream>
#include <Channel.h>
#include <boost/thread.hpp>
#include <string>


int main( int argc, char ** argv ){
	for(int i = 0; i < argc; i++){
		std::cout << i << " " << argv[i] << std::endl;
	}
	try{
		if(argc == 1){ 
			std::cout << "usage: [-rel/-cla] name q u d v0 m0 b f " << std::endl;
			std::cout << "					      -timeScale" << std::endl;
			std::cout << "starting standart sim" << std::endl;
			BLL::Application app;
			app();
		}else{
			BLL::Application app;
			app(argc, argv);
		}
	}catch(char const* exp){
		std::cout << exp << std::endl;
		return -1;
	}

	return 0;
}
