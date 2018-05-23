#include "./wumpus.h"

Wumpus::Wumpus(){
	snprintf(percept, sizeof(percept), "You can hear the sounds of a grunt nearby");
	percept[strcspn(percept, "\n")] = '\0';
}

void Wumpus::read_percept(){
	printw("%s\n", percept);
	//cout << percept << "\n";
}
