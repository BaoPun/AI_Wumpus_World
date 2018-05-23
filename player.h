#ifndef PLAYERH
#define PLAYERH

#include "./board.h"

class Player{ //although this is a player class, this will be implemented as if the AI was going to play
	private:
		Board huntwumpus; //player interacts with board
		int x, y; //holds the current player coordinates
		int startx, starty; //holds the initial starting position
		bool arrowCount;
	public:
		Player();
		
		//Accessor Functions
		int getX();
		int getY();
		
		//Mutator Functions
		void setX(int);
		void setY(int);
		
		/*
			Heuristics (after each movement):
				- if no dialogues, then every single non-diagonal neighbor is safe
				- if gold dialogue, then same as above
				- if pit dialogue, then every non-true adjacent space is a danger
				- if wumpus dialogue, then shoot at all non-visited danger zones
		*/
		
		void viewBoard();
		void play();
		void scanEvents();
		bool move(); 
		void confirm();
		void updatePlayer();
		bool playerAlive();
		bool gameDone();
};

#endif
