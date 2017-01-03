#ifndef ZYKLOTRON_CONTROLLER_H 
#define ZYKLOTRON_CONTROLLER_H

#include <Zyklotron.h>
#include <Window.h>
#include <Graph.h>
#include <StdGraphController.h>

#include <vector>
#include <string>

namespace BLL{


/**
	\brief Verwaltet die Zyklotrons

	Der ZyklotronController verwaltet, started und beendet die Zyklotrons. Er ist
	ein Singletonobjekt.

*/
class ZyklotronController{
protected:

	///Die verwalteten Zyklotrons
	std::vector<Zyklotron*> zyks;
	
	///Standardkonstruktor
	///Protected, da es ein Singleton ist.
	ZyklotronController();

	~ZyklotronController();
	

	///Speichert die Namen der Graphen für ein Zyklotron
	///der n-te vector enthält die Graphnamen für das n-te Zyklotron
	std::vector<std::vector<std::string>> names;

public:

	///Singletontypische Methode
	static ZyklotronController& instance(){
		static ZyklotronController staticThis;
		return staticThis;
	}


	/**
		\brief fügt ein Zyklotron zu dem ZyklotronController hinzu

		Das neue Zyklotron wird als zyks hinzugefügt und die Graphnamen werden
		an names angehängt

		\param strs Namen der Graphen des Zyklotrons
	*/
	void addZyklotron(std::vector<std::string> strs);

	/**
		\brief Getter für ein Zyklotron

		\param index die nummer der Zyklotrons

		\return eine Refferenz auf das Zyklotron an der index-ten Stelle in zyks
	*/
	Zyklotron& getZyklotron(int index);

	/**
		\brief fährt alle Zyklotrons hoch

		Die Simulation mit in dieser Methode gestartet. Das Window muss 
		eingerichtet sein, dass heißt Window::instance().create() muss
		aufgerufen worden sein, sowie Zyklotron::instance().insertGraphs()
	*/
	void run();

	/**
		\brief erstellt die Graphen für die Zyklotrons

		Diese Methode fügt in Window für jedes Zyklotron die entsprechen Graphen
		ein.

		\param order 	legt die Reihnfolge der Graphen fest. Wenn es true ist,
				werden zuerst alle ersten Graphen eines jeden Zyklotrons
				eingesetzt, sonst werden alle Graphen des ersten 
				Zyklotrons im Window eingerichtet.

	*/
	void insertGraphs(bool order);

	/**
		\brief fährt die Simlation herunter

		löscht jedes Zykltron und ruft damit den Destructor derselbigen auf.
	*/
	void shut_down();
};

}
#endif
