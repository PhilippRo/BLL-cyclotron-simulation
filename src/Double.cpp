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
	, power(0){
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

Double::Double(double val, int pow)
	: value(val)
	, power(pow) {
}

Double Double::operator*(Double d){
	return Double(
		value * d.value,
		power + d.power);
}

Double BLL::Double::operator/(Double d){
	Double ret(
		value / d.value,
		power - d.power);
	return ret;
}

Double Double::operator+(Double d){
	Double ret(
		value + d.value*std::pow(10, d.power - power),
		power);
	return ret;
}

Double Double::operator-(Double d){
	Double ret;
	ret.value = value - (d.value * std::pow(10, d.power - power));
	ret.power = power;
	return ret.adapt();
}


//TODO Rewrite
Double BLL::Double::operator%(BLL::Double d){
	Double temp = *this - d; 
	Double ret{0.0,0};
	while(temp.toStd() > 0.0){
		ret = temp;
		temp = ret - d;
	} 
	return ret;
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
	return value * std::pow(10, power);
}

std::string Double::toString(){
	std::stringstream ret;
	ret.precision(5);
	ret << value;
	ret << " e";
	ret << power;
	std::string retstr = ret.str();
	return retstr;
}

Double Double::sqrt(){
	Double d;
	if((power & 1) == 0){
		d.value = std::sqrt(value);
		d.power = power >> 1;
	}else{
		d.value = std::sqrt(value * 10.0);
		d.power = (power + 1) >> 1;
	}
	return d.adapt();
}

Double Double::adapt(){
	if(value != 0.0){
		bool neg = value < 0 ? true : false;
		
 		auto abso = neg ? -1*value : value; 
		
		while(abso > 1000.0){
			value /= 1000;
			abso  /= 1000;
			power+=3;
		}
		while( abso < 0.001){
			value *= 1000;
			abso  *= 1000;	
			power-=3;
		}
	}
	return (*this);
}

}
