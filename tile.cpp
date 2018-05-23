#include "./tile.h"

Tile::Tile(){
	visit = false, caution = false, danger = false, kill = false;
	symbol = ' ';
}

bool Tile::hasVisited(){
	return visit;
}

char Tile::getSymbol(){
	return symbol;
}

bool Tile::getDanger(){
	return danger;
}

bool Tile::getCaution(){
	return caution;
}

bool Tile::getKill(){
	return kill;
}

void Tile::setVisited(){
	visit = true;
}

void Tile::setSymbol(char s){
	symbol = s;
}

void Tile::setDanger(bool d){
	danger = d;
}

void Tile::setCaution(bool c){
	caution = c;
}

void Tile::setKill(bool k){
	kill = k;
}

void Tile::displayMessage(){
	switch(symbol){
		case 'G':
			percept = &gold;
			percept->read_percept();
			break;
		case 'P':
			percept = &pit;
			percept->read_percept();
			if(!visit && !caution)
				danger = true;
			break;
		case 'B':
			percept = &bat;
			percept->read_percept();
			if(!visit)
				caution = true;
			break;
		case 'W':
			percept = &wumpus;
			percept->read_percept();
			if(!visit && !caution && !danger)
				kill = true;
			break;
	}
}
