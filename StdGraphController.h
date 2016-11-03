/*
 * StdGraphController.h
 *
 *  Created on: 02.07.2016
 *      Author: philipp
 */

#ifndef STDGRAPHCONTROLLER_H_
#define STDGRAPHCONTROLLER_H_

#include <vector>
#include <Point.h>
#include <boost/thread.hpp>

namespace BLL {

class StdGraphController {
protected:
	int pointsToFilter;
	int pointsFiltered;
	std::vector<BLL::Point> *points;
	boost::mutex mtx;
public:
	std::vector<BLL::Point> getPoints();
	StdGraphController();
	void setPoints(std::vector<BLL::Point>* p);
	virtual void operator<<(BLL::Point p);
	virtual ~StdGraphController();
	BLL::Point max();
};

} /* namespace BLL */

#endif /* STDGRAPHCONTROLLER_H_ */
