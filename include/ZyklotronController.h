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
	\brief verwaltet die simulierten Zyklotrone

	Der ZyklotronController verwaltet, started und beendet die Zyklotrone. Er ist
	ein Singletonobjekt.

*/
class ZyklotronController{
protected:

	///die verwalteten Zyklotrone
	std::vector<Zyklotron*> zyks;
	
	/**
		\brief der Standardkonstruktor

		Er ist protected, da es ein Singleton ist.
	*/
	ZyklotronController();

	~ZyklotronController();
	

	/**
		speichert die Namen der Graphen für ein Zyklotron
		der n-te vector enthält die Graphnamen für das n-te Zyklotron
        */
	std::vector<std::vector<std::string>> names;

	///in eine HTML-Datei zu schreibende Daten
	///(siehe writeToLog)
	std::stringstream to_log;

public:

	///eine Singletontypische Methode
	static ZyklotronController& instance(){
		static ZyklotronController staticThis;
		return staticThis;
	}


	/**
		\brief fügt ein Zyklotron zu dem ZyklotronController hinzu

		Das neue Zyklotron wird an zyks hinzugefügt und die Graphnamen werden
		an names angehängt.

		\param strs Namen der Graphen des Zyklotrons
	*/
	void addZyklotron(std::vector<std::string> strs);

	/**
		\brief ein Getter für ein Zyklotron

                Der Getter gibt das Zyklotron an der index-ten Stelle
                im vector zyks zurück.

		\param index die nummer der Zyklotrons

		\return eine Referenz auf das Zyklotron an der index-ten Stelle in zyks
	*/
	Zyklotron& getZyklotron(int index);

	/**
		\brief fährt alle Zyklotrone hoch

		Die Simulation wird mit in dieser Methode gestartet. Das Window muss 
		eingerichtet sein, das heißt Window::instance().create() muss
		aufgerufen worden sein, sowie Zyklotron::instance().insertGraphs().
	*/
	void run();

	/**
		\brief erstellt die Graphen für die Zyklotrone

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

		Diese Methode löscht jedes Zykltron und ruft damit den Destruktor desselbigen auf.
	*/
	void shut_down();

	/**
		\brief merkt Daten vor, um sie in einer HTML-Datei zu speichern

		Diese Methode Methode schreibt zu protokollierende Daten in den
		Stingstream to_log und in der Methode shut_down werden die Daten in
		die Datei log.html geschrieben.

		\param names Namen der Datensätze; häufig Namen der Graphen; es sind
				immer 7 Namen
		\param data Datensatz
	*/
	void writeToLog(std::vector <std::string> names, ZyklotronParts::ZykSet data);

};

}
#endif
