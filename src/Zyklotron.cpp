/*
 * Zyklotron.cpp
 *
 *  Created on: 17.05.2016
 *      Author: philipp
 *
 *
*/

#include <Zyklotron.h>
#include <ZyklotronController.h>
#include <SFML/System.hpp>
#include <Window.h>
#include <utility>

namespace BLL {

namespace ZyklotronParts{
   ZykSet::ZykSet(){}
   ZykSet::ZykSet(const ZykSet& o) : time(o.time)
                                   , v(o.v)
                                   , s(o.s)
                                   , ke(o.ke)
                                   , me(o.me)
                                   , re(o.re)
                                   , r(o.r)
                                   , roundtime(o.roundtime)
                                   , timeInCondensator(o.timeInCondensator){
   }
}


Zyklotron::Zyklotron() {
	chan=new BLL::Channel<ZyklotronParts::ZykSet>();
}

//TODO exceptions are thrown in destructor
Zyklotron::~Zyklotron() {
	BLL::ZyklotronController::instance().writeToLog(names, to_log);

	if( calcThread != 0)
		delete calcThread;

	if(thisThread !=0)
		delete thisThread;

	if(chan == 0)
		delete chan;
}

void Zyklotron::shutdown(){
    if(!running)
        return;

    running = false;

    chan->deactivate();

    calcThread->join();

    thisThread->join();
}

void Zyklotron::configure(Double paraQ, Double paraU, Double paraD, Double paraV0, 
			Double paraM0, Double paraB, Double paraF, float PTimeScale, 
                        bool paraRelativistic, Double paraR){
	q = paraQ;
	u = paraU;
	d = paraD;
	v0 = paraV0;
	m0 = paraM0;
	b = paraB;
	a0 = (q * (u/d)) / m0;
	f = paraF;
	timeScale = PTimeScale;
        relativistic = paraRelativistic;
        r_max = paraR;
	configured = true;
}



void Zyklotron::run(){
	if(!configured) throw "Zyklotron was not configured [Zyklotron.cpp run]";
	calcThread = new boost::thread(boost::bind(&BLL::Zyklotron::calc, this));
	thisThread = new boost::thread([&](){
		sf::Clock cl;
		while(running){
			if(!chan)
				return;

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
			boost::this_thread::interruption_point();
		}
	});
}

void Zyklotron::calc(){

	using namespace ZyklotronParts;
	ZyklotronParts::ZykSet it;
	it.v = this->v0;
	it.time = Double(0,0);
	Double a{a0};
        Double one{1,0};
		while(running){
			ZyklotronParts::ZykSet res;
			
			Double c = Double::c();
			auto& v0 = it.v;
	
			Double timePosAccel;
			if(relativistic){
				timePosAccel = std::move((c/a) * ( ( (d * a /(c*c) + (one+ (v0*v0/
					(c*c))).sqrt()) * (d * a /(c*c) + (one + (v0*v0/
					(c*c))).sqrt()) - one).sqrt() - (v0/c)));
			}else{
				timePosAccel = std::move((((v0 * v0)/(Double(4,0) * a*a))+ 
					(d / a)).sqrt() - v0/(Double(2,0) * a));
			}	
			

			Double timeNegAccel = std::move((it.time + timePosAccel) %  f);
			timeNegAccel = timeNegAccel == ((it.time + timePosAccel) % 
				(Double(2,0)* f)) ? timeNegAccel : Double (0,0);
			
			if(relativistic){
				res.v = std::move((a*(timePosAccel-timeNegAccel) + v0) / 
					(Double(1,0)+ ((a*(timePosAccel - timeNegAccel)
					+ v0)*(a*(timePosAccel-timeNegAccel) + v0)/
					(c*c))).sqrt());
			
				auto m = std::move(m0 / 
					(Double(1,0) - ((res.v*res.v) /(c*c))).sqrt()); 
				//Massendifferenz	
				res.me = std::move(m - m0);

				res.ke = std::move((m - m0) * c* c);

				res.re = std::move(m * c * c);
			
			}else{
				res.v = a*(timePosAccel- timeNegAccel) + std::move(it.v);
				auto& v = res.v;
				//Keine Massendifferenz
				res.me = m0;
				res.ke = std::move(m0 * v * v * Double (0.5,0));
				res.re = std::move(res.ke);
			}
			res.r = std::move((res.me  * res.v)/(q * b));
			auto r0 = std::move((m0 * res.v)/(q * b));
			
			// Falsch
			// gesucht ist eine Halbe Umrundungszeit
			// U/2*v = pi * r / v
			res.roundtime = std::move((res.r)/res.v);

			res.timeInCondensator = std::move(timePosAccel- timeNegAccel);

			res.s = std::move(std::move(it.s) + res.r + d);

			res.time = std::move(std::move(it.time) + res.roundtime + std::move(timePosAccel)+std::move(timeNegAccel));			
			it = res;

			if(!chan)
				return;

			chan->write(std::move(res));
			boost::this_thread::interruption_point();
		}
                to_log = it;
	}

void Zyklotron::setGraphNames(std::vector <std::string> paraNames){
	//check the correct name list length
	if(paraNames.size() > 5){
		names = paraNames;	
	}
}

} /* namespace BLL */
