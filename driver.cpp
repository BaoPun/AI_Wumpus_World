#include "./player.h"


int main(){
	srand((unsigned int)time(NULL));
	initscr();
	raw();
	noecho();
	keypad(stdscr, TRUE);
	
	Player AI; 
	AI.play();

	refresh();
	endwin();

	return 0;
}
