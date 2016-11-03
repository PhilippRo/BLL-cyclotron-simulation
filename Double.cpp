/*
 * Double.cpp
 *
 *  Created on: 17.05.2016
 *      Author: philipp
 */

#include <Double.h>
#include <sstream>
#include <iostream>

namespace BLL {

Double::Double()
	: value(0.0)
	, power(0.0){
}
	
Double::Double(std::string n){
	char s = 'e';
	std::string v;
	std::string p;
	int i;
	for(i = 0; i < n.size(); i++){
		if(n[i] == s){
			i++;
			break;
		}
		v.push_back(n[i]);
	}
	for(i=i; i < n.size(); i++){
		p.push_back(n[i]);
	}
	value = std::stod(v);
	power = std::stod(p);
}

Double::Double(double val, double pow)
	: value(val)
	, power(pow) {
}

Double::~Double() {
	// TODO Auto-generated destructor stub
}

Double Double::operator*(Double d){
	Double ret;
	ret.value = value * d.value;
	ret.power = power + d.power;
	return ret.adapt();
}

Double BLL::Double::operator/(Double d){
	Double ret;
	ret.value = value / d.value;
	ret.power = power - d.power;
	return ret.adapt();
}

Double Double::operator+(Double d){
	Double ret;
	ret.value = value + (d.value * pow(10, d.power - power));
	ret.power = power;
	return ret.adapt();
}

Double Double::operator-(Double d){
	Double ret;
	ret.value = value - (d.value * pow(10, d.power - power));
	ret.power = power;
	return ret.adapt();
}

Double BLL::Double::operator%(BLL::Double d){
	int prec = 100000000;
	return Double((double)((int)(value*prec)%(int)(std::pow(d.value, d.power - power)*prec)), power - prec).adapt(); 
}

bool BLL::Double::operator <(BLL::Double d){
	return ((*this)/d).toStd() < 1.0;
}

bool BLL::Double::operator==(Double d){
	Double t = *this;
	t.adapt();
	d.adapt();
	return t.value == d.value && d.power == t.power; 
}

double Double::toStd(){
	return value * pow(10, power);
}

std::string Double::toString(){
	std::stringstream ret;
	ret.precision(2);
	ret << value;
	ret << " e";
	ret << power;
	std::string retstr = ret.str();
	return retstr;
}

Double Double::sqrt(){
	Double d;
	d.value = std::sqrt(value);
	d.power = power / 2;
	return d.adapt();
}

Double Double::adapt(){
	if(value != 0.0){
		while(std::abs(value) > 10.0){
			value /= 10;
			power ++;
		}
		while(std::abs(value) < 0.1){
			value *= 10;
			power --;
		}
	}
	return (*this);
}

}
