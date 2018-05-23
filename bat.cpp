#include "./bat.h"

Bat::Bat(){
	snprintf(percept, sizeof(percept), "You sense a malicious gaze nearby");
	percept[strcspn(percept, "\n")] = '\0';
}

void Bat::read_percept(){
	printw("%s\n", percept);
	//cout << percept << "\n";
}
