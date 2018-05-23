#ifndef BOARDH
#define BOARDH

#include "./tile.h"

class Board{
	private:
		Tile board[6][6];
	public:
		Board();
		void viewBoard();
		void scanEvents(int, int);
		bool move(int, int, int, int, bool);
		void moveTo(int); 
		void moveEvent(int, int);
		bool killWumpus(int, int);
		bool checkGold();
		
		//the following functions return the x and y coordinate for the player
		int horizontal();
		int vertical();
		int wumpusHorizontal();
		int wumpusVertical();
	
		bool checkTies(bool *);
		bool playerAlive();
		bool wumpusAlive();
		bool gameDone(int, int);
};

#endif
