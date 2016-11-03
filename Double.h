/*
 * Double.h
 *
 *  Created on: 17.05.2016
 *      Author: philipp
 *
 *  Im Prinzip ist Double value * 10 hoch power
 *  als POD (Plain Old Data)
 *  mit einigen Helferfunktionen
 */

#ifndef DOUBLE_H_
#define DOUBLE_H_

#include <typeinfo>
#include <cmath>
#include <string>

namespace BLL {

class  Double {
public:
	Double();
	Double(double val, double pow);
	Double(std::string n);
	virtual ~Double();

	static Double c(){
		Double d;
		d.value = 3;//29.9792458;
		d.power = 8;//7;
		return d;
	}

	static Double pi(){
		return Double(3.14159265359,0);
	}

	double toStd();
	Double operator*(Double d);
	Double operator/(Double d);
	Double operator+(Double d);
	Double operator-(Double d);
	Double operator%(Double d);
	Double sqrt();
	bool operator<(Double d);
	bool operator==(Double d);
	std::string toString();
	Double adapt();

	double value;
	double power = 1;
};

} /* namespace BLL */

#endif /* DOUBLE_H_ */
