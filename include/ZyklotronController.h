#ifndef ZYKLOTRON_CONTROLLER_H 
#define ZYKLOTRON_CONTROLLER_H

#include <Zyklotron.h>
#include <Window.h>
#include <Graph.h>
#include <StdGraphController.h>

#include <vector>
#include <string>
#include <sstream>


namespace BLL{


/**
	\brief Verwaltet die simulierten Zyklotrons

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

	///In eine HTML-Datei zu schreibende Daten
	///siehe writeToLog
	std::stringstream to_log;

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
		(vor Window::instance().create() & vgl. Application code).
	*/
	void run();

	/**
		\brief erstellt die Graphen für die Zyklotrons

		Diese Methode fügt in Window für jedes Zyklotron die entsprechen Graphen
		ein.

		\param order 	legt die Reihenfolge der Graphen fest. Wenn es true ist,
				werden zuerst alle ersten Graphen eines jeden Zyklotrons
				eingesetzt, sonst werden alle Graphen des ersten 
				Zyklotrons im Window eingerichtet.

	*/
	void insertGraphs(bool order);

	/**
		\brief fährt die Simlation herunter

		löscht jedes Zykltron und ruft damit den Destructor desselbigen auf.
	*/
	void shut_down();

	/**
		\brief Merkt Daten vor, um sie in einer HTML-Datei zu speichern.

		Diese Methode Methode schreibt zu protokollierende Daten in den
		Stingstream to_log und in der Methode shut_down werden die Daten in
		die Datei log.html geschrieben

		\param names Namen der Datensätze häufig Namen der Graphen; es sind
				immer 6 Namen
		\param data Datensatz
	*/
	void writeToLog(std::vector <std::string> names, ZyklotronParts::ZykSet data);

};

}
#endif
