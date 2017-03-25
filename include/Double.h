/*
 * Double.h
 *
 *  Created on: 17.05.2016
 *      Author: philipp
 *
 */

#ifndef DOUBLE_H_
#define DOUBLE_H_

#include <string>

namespace BLL {


/**
    \brief die Doubleklasse ist eine wissenschaftlichen Darstellung von Zahlen.

    Double versucht das Floatingpointprecisionproblem annähernd zu lösen.
    Dabei werden Zahl als float * (10 ^ n) dargestellt. 
*/
class  Double {
public:
        
        ///der Standardkonstruktor
	Double();
        
        /**
            \brief ein Konstruktor, der einen Double mit Werten konstruiert

            \param val das f von f * (10^n)
            \param pow das n von f * (10^n)
        */
	Double(double val, int pow);

        Double(const Double& other);

       /**
            \brief erstellt Double aus String

             Diese methode parsed einen Double aus einem String.

             Der String hat die Form "[float]e[int]"

             Umkehrfunktion zu toString().

             \param n der zu parsende String

        */
	Double(std::string n);

        /**
            \brief die Lichtgeschwindigkeit (ca. 3 * 10^8)

            Diese Methode gibt die ungefäre Lichtgeschwindigkeit im Vakuum zurück.

            \return Lichtgeschwindigkeit

       */
	static Double c(){
		Double d;
		d.value = 29.9792458;
		d.power = 7;
		return d;
	}

        /**
            \brief gibt Pi (ca 3.1415...) zurück

            \return Pi 
        */
	static Double pi(){
		return Double{3.14159265359, 0};
	}

        /** 
            \brief formt BLL::Double nach double um
           
            Diese Methode formt die wissenschaftliche Darstellung in die normale um.
            Dabei kann es zu Genauigkeitsproblemen aufgrund der Schwächen eines double
            kommen.

            \return Wert als double
        */    
	double toStd() const;

        /**
           \brief multipliziert zwei Zahlen vom Typ Double

           \return Produkt zweier Zahlen vom Typ Double
        */	
        Double operator*(const Double& d);
	
        /**
           \brief dividiert zwei Zahlen vom Typ Double

           \return Quotient zweier Zahlen vom Typ Double
        */
        Double operator/(const Double& d);

        /**
           \brief addiert zwei Zahlen vom Typ Double

           \return Summe zweier Zahlen vom Typ Double
        */
	Double operator+(const Double& d);

        /**
           \brief subtrahiert zwei Zahlen vom Typ Double

           \return Differenz zweier Zahlen vom Typ Double
        */
	Double operator-(const Double& d) ;

         /**
           \brief Modulo-operator für zwei Zahlen vom Typ Double

	   Diese Methode zieht d so lange von this ab, bis this kleiner
           als d ist und gibt den Rest zurück.

           \return Rest eines Doubles geteilt d
        */
	Double operator%(const Double& d);

	/**
             \brief zieht die Wurzel aus einem Double

             \return Wurzel aus einem Double
        */
	Double sqrt();

        /**
            \brief vergleicht zwei Zahlen von Typ Double

            \return ob a kleiner ist als d ( a < d )
        */
	bool operator<(const Double& d);
	
        /**
            \brief prüft zwei Doubles auf Gleichheit

            \return ob 2 Doubles sich entsprechen
        */
        bool operator==(Double& d);

        /**
            \brief prüft zwei Doubles auf Gleichheit

            \return ob 2 Doubles sich entsprechen
        */
        bool operator==(Double d);


        /**
            \brief stellt Double als string da
 
            stellt ein Double als String da in der Form "f e n"

            ist die Umkehrfunktion zum Double(std::string n) 

            \return Double in Stringdastellung
        */
	std::string toString() const;

        /**
            \brief passt die Datstellung der Zahlen an

            Wenn in der Form f * 10^n f in einen Bereich kommt, in dem das
            Floatingpointprecisionproblem relevant wird, kann mit dieser Methode f 
            durch Anpassen des Exponenten in eine günstigere Form gebracht werden.
        */
	Double adapt();

protected:
	///der Wert der Zahl
	double value;

	///der Exponent über der Zehn
	int    power = 1;
};

} /* namespace BLL */

#endif /* DOUBLE_H_ */
