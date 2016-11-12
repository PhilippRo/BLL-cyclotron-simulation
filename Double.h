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


/**
    \brief Double ist eine einfach mp Klasse

    Double ist eine Multiprecision Klasse und versucht dem Floatingpointprecisionproblem    annähernd zu lösen.
    Dabei werden Zahl als float * (10 ^ n) dagestellt. 
*/
class  Double {
public:
        
        //Standartkonstruktor
	Double();

        /**
            \brief Konstruktor mit Wert

            Erstellt eine Instanz von Double mit Werten

            \param val das f von f * (10^n)
            \param pow das n von f * (10^n)
        */
	Double(double val, double pow);

        /**
            \brief Erstellt Double aus String

             Parsed ein Double aus einem String

             Umkehrfunktion zu toString()

             \param n der zu parsende String

        */
	Double(std::string n);

        ///Standartdestruktor
	virtual ~Double();

        /**
            \brief Lichtgeschwindigkeit (ca 3 * 10^8)

            Gibt die ungefäre Lichtgeschwindigkeit im Vakuum zurück

            \return Lichtgeschwindigkeit

       */
	static Double c(){
		Double d;
		d.value = 3;//29.9792458;
		d.power = 8;//7;
		return d;
	}

        /**
            \brief Pi (ca 3.1415...)

            \return Pi 
        */
	static Double pi(){
		return Double(3.14159265359,0);
	}

        /** 
            \brief formt BLL::Double nach double um
           
            formt die Exponentielle Dastellung in die normale um

            \return Wert als Double
        */    
	double toStd();

        /**
           \brief multiplizirt zwei Zahlen vom Typ Double

           \return Produkt zweier Zahlen vom Typ Double
        */	
        Double operator*(Double d);
	
        /**
           \brief dividirt zwei Zahlen vom Typ Double

           \return Quotient? zweier Zahlen vom Typ Double
        */
        Double operator/(Double d);

        /**
           \brief addiert zwei Zahlen vom Typ Double

           \return Summe zweier Zahlen vom Typ Double
        */
	Double operator+(Double d);

        /**
           \brief subtrahiert zwei Zahlen vom Typ Double

           \return Differenz zweier Zahlen vom Typ Double
        */
	Double operator-(Double d);

         /**
            \brief Modulooperator für zwei Zahlen vom Typ Double

           \return Restklasse eines Doubles modulo d
        */
	Double operator%(Double d);

	/**
             \brief zieht die Wurzel aus einer Zahl

             \return Wurzel aus einem Double
        */
	Double sqrt();

        /**
            \brief vergleicht zwei Zahlen von Typ Double

            \return ob a kleiner ist als d ( a < d)
        */
	bool operator<(Double d);
	
        /**
            \brief prüft zwei Doubles auf Gleichheit

            \return ob 2 Double gleich sind
        */
        bool operator==(Double d);

        /**
            \brief stellt Double als string da
 
            stellt ein Double als String da in der Form "f e n"

            ist die Umkehrfunltion zum Double(std::string n) 

            \return Double in Stringdastellung
        */
	std::string toString();

        /**
            \brief passt die Datstellung der Zahlen an

            Wenn in der Form f * 10^n f in einen Bereich kommt, in dem das
            Floatingpointprecisionproblem relevant wird kann mit diese Methode f 
            in eine günstigere Form gebracht werden.
        */
	Double adapt();

	double value;
	double power = 1;
};

} /* namespace BLL */

#endif /* DOUBLE_H_ */
