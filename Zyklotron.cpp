/*
 * Zyklotron.cpp
 *
 *  Created on: 17.05.2016
 *      Author: philipp
 *
 *
 * testing eq:
 *  t(s) = 				((Double::c()*
 *						(( (((dist + dist) / a) +
 *						(Double(1.0,0.0) + ((v0 / Double::c())*(v0 / Double::c()))).sqrt() )*( (((dist + dist) / a) +
 *						(Double(1.0,0.0) + ((v0 / Double::c())*(v0 / Double::c()))).sqrt() )) - (Double(1.0,0.0)) ).sqrt()  ) -
 *						v0) / a);
 */

#include <Zyklotron.h>
#include <cmath>
#include <limits.h>
#include <SFML/System.hpp>
#include <Window.h>
#include <iostream>
#include <vector>
#include <iostream>

namespace BLL {

Zyklotron::Zyklotron() {
	chan=new BLL::Channel<ZyklotronParts::ZykSet>();
}

Zyklotron::~Zyklotron() {
	if(calcThread != 0){
		calcThread->interrupt();
		delete calcThread;
	}
	delete chan;
}

void Zyklotron::configure(Double paraQ, Double paraU, Double paraD, Double paraV0, 
			Double paraM0, Double paraB, Double paraF, float PTimeScale){
	q = paraQ;
	u = paraU;
	d = paraD;
	v0 = paraV0;
	m0 = paraM0;
	b = paraB;
	a0 = (q * (u/d)) / m0;
	f = paraF;
	timeScale = PTimeScale;
	configured = true;
}

void Zyklotron::configure(Double paraQ, Double paraU, Double paraD, Double paraV0, 
	Double paraM0, Double paraB, Double paraF, float PTimeScale, bool paraReal){
	this->relativistic=paraReal;
	configure( paraQ, paraU, paraD, paraV0, paraM0, paraB, paraF, PTimeScale);

}

void Zyklotron::run(){
	if(!configured) throw "Zyklotron was not configured [Zyklotron.cpp run]";
	calcThread = new boost::thread(boost::bind(&BLL::Zyklotron::calc, this));
	sf::Clock cl;
	while(true){
		ZyklotronParts::ZykSet res = chan->read();
		int i = 0;
		while((float)cl.getElapsedTime().asSeconds()*timeScale<res.time.toStd())
		{
			//std::cout << "waiting" << std::endl;
			i++;
		
		}
		(*BLL::Window::instance().getGraph(names[0])) << Point(res.time, res.v);
		(*BLL::Window::instance().getGraph(names[1])) << Point(res.time, res.roundtime);
		(*BLL::Window::instance().getGraph(names[2])) << Point(res.time, res.timeInCondensator);
		(*BLL::Window::instance().getGraph(names[3]))<< Point(res.time, res.ke);
		(*BLL::Window::instance().getGraph(names[4])) << Point(res.time, res.re);
		(*BLL::Window::instance().getGraph(names[5])) << Point(res.time, res.me);
	}
}

void Zyklotron::calc(){

	using namespace ZyklotronParts;
	// Todo Fork Thread for Calculating the shit
	ZyklotronParts::ZykSet it;
	it.v = this->v0;
	it.time = Double(0,0);
	Double a = a0;
	long i = 1;
		while(true){
			ZyklotronParts::ZykSet res;
			
			Double c(3, 8);
			auto v0 = it.v;
			
			Double timePosAccel = (((v0 * v0)/(Double(4,0) * a * a)) + (d / a)).sqrt() - v0/(Double(2,0) * a);
			//Double timePosAccel = (Double(2*i, 0) * d / a).sqrt();	
			

			Double timeNegAccel = ((it.time + timePosAccel) %  f);
			timeNegAccel = timeNegAccel == ((it.time + timePosAccel) % (Double(2,0)* f)) ? timeNegAccel : Double (0,0);
			if(relativistic){
				res.v = (a*(timePosAccel-timeNegAccel) + v0) / (Double(1,0)+ ((a*(timePosAccel - timeNegAccel)+ v0)*(a*(timePosAccel-timeNegAccel) + v0)/(c*c))).sqrt();
			

				auto m = m0 / (Double(1,0) - ((res.v*res.v) /(c*c))).sqrt(); 
			
				res.me = m - m0;

				res.ke = (m - m0) * c* c;

				res.re = m * c * c;
			
			}else{
				res.v = a*(timePosAccel- timeNegAccel) + it.v;
				auto& v = res.v;
				res.me = m0;
				res.ke = m0 * v * v * Double (0.5,0);
				res.re = res.ke;
			}
			res.r = (res.me  * res.v)/(q * b);
			auto r0 = (m0 * res.v)/(q * b);
			
			res.roundtime = (res.r)/res.v;

			res.timeInCondensator = timePosAccel- timeNegAccel;

			res.s = it.s + res.r + d;

			res.time = it.time + res.roundtime + timePosAccel+timeNegAccel;			
			it = res;
			i++;
			chan->write(res);
		}
	}

void Zyklotron::setGraphNames(std::vector <std::string> paraNames){
	//check the correct name list length
	if(paraNames.size() > 5){
		names = paraNames;	
	}
}

} /* namespace BLL */
