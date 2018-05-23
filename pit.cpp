#include "./pit.h"

Pit::Pit(){
	snprintf(percept, sizeof(percept), "A chilling breeze can be felt");
	percept[strcspn(percept, "\n")] = '\0';
}

void Pit::read_percept(){
	printw("%s\n", percept);
	//cout << percept << "\n";
}
