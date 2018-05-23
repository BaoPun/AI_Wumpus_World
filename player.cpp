#include "./player.h"

Player::Player(){
	x = 4, y = 3, arrowCount = true;
	startx = x, starty = y;
}

int Player::getX(){
	return x;
}

int Player::getY(){
	return y;
}

void Player::setX(int a){
	x = a;
}

void Player::setY(int b){
	y = b;
}

void Player::viewBoard(){
	huntwumpus.viewBoard();
}

void Player::play(){
	/*
		Each turn, scan for events that are non-diagonally adjacent to the player
		Player makes a decision and moves based on the events
		Repeat until the game is over
	*/
	int moveCounter = 0;
	printw("Hunt the Wumpus, with an AI playing this game\n");
	viewBoard();
	while(playerAlive() && !gameDone()){
		updatePlayer();
		scanEvents();
		//printw("\nNumber of moves made: %d", moveCounter);
		moveCounter++;
		arrowCount = move();
		if(!playerAlive()){
			confirm();
			return;
		}
		if(gameDone()){
			printw("\nCongratulations, you have completed the game!");
			printw("\nThe AI has completed the game in %d moves\n", moveCounter);
			confirm();
			return;
		}
		confirm();
		clear();
		printw("Hunt the Wumpus, with an AI playing this game\n");
		viewBoard();
	}
}

void Player::scanEvents(){
	huntwumpus.scanEvents(x, y);
}

bool Player::move(){
	return huntwumpus.move(x, y, startx, starty, arrowCount);
}

void Player::confirm(){
	int c;
	printw("\nPress the 'f' button to continue\n");
	c = getch();
	while(c != 'f')
		c = getch();
}

void Player::updatePlayer(){
	x = huntwumpus.horizontal();
	y = huntwumpus.vertical();
	printw("Currently at: (%d, %d)\n", x, y);
}

bool Player::playerAlive(){
	return huntwumpus.playerAlive();
}

bool Player::gameDone(){
	return huntwumpus.gameDone(startx, starty);
}