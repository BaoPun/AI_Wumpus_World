#ifndef TILEH
#define TILEH

#include "./gold.h"
#include "./pit.h"
#include "./bat.h"
#include "./wumpus.h"

class Tile{
	private:
		bool visit, caution, danger, kill;
		char symbol;
		Event *percept;
		Gold gold;
		Pit pit;
		Bat bat;
		Wumpus wumpus;
	public:
		Tile();
		
		//Accessor Functions
		bool hasVisited();
		char getSymbol();
		bool getDanger();
		bool getCaution();
		bool getKill();
		
		//Mutator Functions
		void setVisited();
		void setSymbol(char);
		void setDanger(bool);
		void setCaution(bool);
		void setKill(bool);
		
		void displayMessage();
};

#endif
