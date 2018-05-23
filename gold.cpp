#include "./gold.h"

Gold::Gold(){
	snprintf(percept, sizeof(percept), "There is a yellow glow nearby");
	percept[strcspn(percept, "\n")] = '\0';
}

void Gold::read_percept(){
	printw("%s\n", percept);
	//cout << percept << "\n";
}
