/*
 * Double.cpp
 *
 *  Created on: 17.05.2016
 *      Author: philipp
 */

#include <Double.h>
#include <sstream>
#include <cmath>

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

Double::Double(const Double& o)
        : value (o.value)
        , power (o.power) {
}

Double Double::operator*(const Double& d) {
	return Double{
		value * d.value,
		power + d.power}.adapt();
}

Double BLL::Double::operator/(const Double& d){
	Double ret{
		value / d.value,
		power - d.power};
	return ret.adapt();
}

Double Double::operator+(const Double& d) {
	Double ret{
		value + d.value*std::pow(10, d.power - power),
		power};
	return ret.adapt();
}

Double Double::operator-(const Double& d) {
	Double ret{
	      value - (d.value * std::pow(10, d.power - power)),
	      power};
	return ret.adapt();
}


//TODO Rewrite
Double BLL::Double::operator%(const BLL::Double& d) {
	Double temp = *this - d; 
	Double ret{0.0,0};
	while(temp.toStd() > 0.0){
		ret = temp;
		temp = ret - d;
	} 
	return ret;
}

bool BLL::Double::operator <(const BLL::Double& d) {
	return ((*this)/d).toStd() < 1.0;
}

bool BLL::Double::operator==( Double& d){
	Double t{*this};
	t.adapt();
	d.adapt();
	return t.value == d.value && d.power == t.power; 
}

bool BLL::Double::operator==( Double d){
	Double t{*this};
	t.adapt();
	d.adapt();
	return t.value == d.value && d.power == t.power; 
}

double Double::toStd() const{
	return value * std::pow(10, power);
}

std::string Double::toString() const{
	std::stringstream ret;
	ret.precision(5);
	ret << value;
	ret << " e";
	ret << power;
	std::string retstr = ret.str();
	return retstr;
}

Double Double::sqrt() {
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
		
		while(abso > 1e5){
			value /= 1e5;
			abso  /= 1e5;
			power+=5;
		}
		while( abso < 1e-5){
			value *= 1e5;
			abso  *= 1e5;	
			power-=5;
		}
	}
	return (*this);
}

}
