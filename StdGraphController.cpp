/*
* StdGraphController.cpp
*
 *  Created on: 02.07.2016
 *      Author: philipp
 */

#include <StdGraphController.h>
#include <algorithm>
#include <iterator>
#include <iostream>

namespace BLL {

StdGraphController::StdGraphController() {
	points = new std::vector <Point>();
	pointsToFilter = 1;
	pointsFiltered = 1;
}

StdGraphController::~StdGraphController() {
	// TODO Auto-generated destructor stub
}

void StdGraphController::operator<<(BLL::Point p){
	mtx.lock();
	if(points->size() > 1000){
		auto& points = *this->points;
		std::vector<BLL::Point> *tp = new std::vector <BLL::Point>(500);
		for(int i = 0; i < 500; i++){
			tp->at(i) = points.at(2*i);
		}
		auto *op = this->points;
		this->points = tp;
		delete op;
		pointsToFilter *= 2;
		pointsFiltered = 1;
	}
	if(pointsFiltered >= pointsToFilter){
		(points)->push_back(p);
		pointsFiltered = 1;
	}else{
		pointsFiltered ++;
	}
	mtx.unlock();
}

void StdGraphController::setPoints(std::vector<BLL::Point>* p){
	mtx.lock();
	this->points = p;
	mtx.unlock();
}

BLL::Point StdGraphController::max(){
	mtx.lock();
	if(points->size() == 0){
		mtx.unlock();
		return Point(Double(1,0), Double(1,0));
	}
	Point p = * std::max_element(points->begin(), points->end(),[](Point a,Point b){
		return a.getY() < b.getY();
	});
	auto lp = points->at(points->size() - 1);
	mtx.unlock();
	return Point(lp.getX(), p.getY());
}

std::vector<Point> StdGraphController::getPoints(){
	mtx.lock();
	auto tpoints = *points;
	mtx.unlock();
	return tpoints;
}

}


