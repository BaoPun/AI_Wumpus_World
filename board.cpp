#include "./board.h"

Board::Board(){
	/*
		What the game board will look like:
	
		.	G	.	.	.	.
		.	.	.	.	P	.
		.	P	.	.	.	.
		W	.	.	.	B	.
		.	.	.	A	.	.
		.	.	B	.	.	.
		
		where A = player or AI, G for gold, P for pit, B for bat, W for wumpus.  
		There is 1 player, 1 gold, 2 pits, 2 bats, and 1 wumpus
	
		To win, we must retrieve the gold, kill the wumpus, and then return to the starting position.
		Order of either killing wumpus or gold doesn't matter, but both must happen
	
	*/
	
	//Initialize the non empty room spots first 
	board[0][1].setSymbol('G');
	board[1][4].setSymbol('P');
	board[2][1].setSymbol('P');
	board[3][0].setSymbol('W');
	board[4][3].setSymbol('A');
	board[3][4].setSymbol('B');
	board[5][2].setSymbol('B');
	
	//Initialize the rest of the board
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 6; j++){
			if(board[i][j].getSymbol() == ' ')
				board[i][j].setSymbol('.');
		}
	}
}

void Board::viewBoard(){
	//cout << "\nViewing the wumpus board\n";
	printw("\nViewing the wumpus board\n");
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 6; j++){
			if(board[i][j].getSymbol() != '.' && board[i][j].getSymbol() != 'A')
				//cout << ".\t";
				printw(".\t");
			else
				//cout << board[i][j].getSymbol() << "\t";
				printw("%c\t", board[i][j].getSymbol());
		}
		//cout << "\n";
		printw("\n");
	}
	//cout << "\n";
	printw("\n");
}

void Board::scanEvents(int u, int v){
	assert(board[u][v].getSymbol() == 'A'); //if this assertion fails, then something has gone wrong
	if(u - 1 >= 0) //search up if the x coordinate is not on top edge
		board[u - 1][v].displayMessage();
	if(u + 1 <= 5) //search down if the x coordinate is not on bottom edge
		board[u + 1][v].displayMessage();
	if(v - 1 >= 0) //search left if the y coordinate is not on left edge
		board[u][v - 1].displayMessage();
	if(v + 1 <= 5) //search right if the y coordinate is not on right edge
		board[u][v + 1].displayMessage();
	printw("\n");
}

bool Board::move(int u, int v, int a, int b, bool arrow){
	//u and v are where the player are, a and b are the starting position coordinates of the player, and arrow is a bool, which depends on whether wumpus is alive or not
	assert(board[u][v].getSymbol() == 'A'); //if this assertion fails, then something has gone wrong
	board[u][v].setVisited(); //before moving our character, mark our current spot to let us know that we've already visited this area before
	board[u][v].setCaution(false); //also uncaution our position
	board[u][v].setDanger(false); //also undanger our position
	board[u][v].setKill(false);
	
	//check each of the directions
	/*
		Prioritize non-dangers over danger zones
		If there are unanimous danger/nondanger zones, then randomize 
		Heuristic values depend on the situation of the adjacent zones:
			1. If a space has not yet been visited, and it has not been caution flagged nor danger flagged, then the max heuristic value of 20 shall be granted
			2. If a space has not yet been visited, but it has been caution flagged, then the heuristic value of 15 shall be granted 
			3. If a space has not yet been visited, but it has been danger flagged, then the heuristic value of 10 shall be granted
			4. If a space has been visited, then the heuristic value of 5 shall be granted
	*/
	int direction[4] = {-9000, -9000, -9000, -9000}; //0 up, 1 down, 2 left, 3 right.  Negative -9000 means that the direction cannot be possible (out of bounds)
	bool tie[4] = {false, false, false, false}; //tie values between ONLY the max values, determined if we will have to use RNG if any ties occur
	if(u - 1 >= 0){ //up
		if(!board[u - 1][v].hasVisited()){
			if(!board[u - 1][v].getDanger() && !board[u - 1][v].getCaution() && !board[u - 1][v].getKill())
				direction[0] = 20;
		}
		else
			direction[0] = 0;
	}
	if(u + 1 <= 5){ //down
		if(!board[u + 1][v].hasVisited()){
			if(!board[u + 1][v].getDanger() && !board[u + 1][v].getCaution() && !board[u + 1][v].getKill())
				direction[1] = 20;
		}
		else
			direction[1] = 0;
	}
	if(v - 1 >= 0){ //left
		if(!board[u][v - 1].hasVisited()){
			if(!board[u][v - 1].getDanger() && !board[u][v - 1].getCaution() && !board[u][v - 1].getKill())
				direction[2] = 20;
		}
		else
			direction[2] = 0;
	}
	if(v + 1 <= 5){ //right 
		if(!board[u][v + 1].hasVisited()){
			if(!board[u][v + 1].getDanger() && !board[u][v + 1].getCaution() && !board[u][v + 1].getKill())
				direction[3] = 20;
		}
		else
			direction[3] = 0;
	}
	
	if(killWumpus(u, v)) //if we manage to kill the wumpus, then do not move your character
		return false;
	
	if(!arrow && !checkGold()){ //if the wumpus is dead and there's no gold on the map, then find the way back home, using the visited areas
		//Manhattan distance, only take the smallest result
		int result = 9000, smallMan = 0;
		if(u - 1 >= 0){ //up
			int xDistance = abs(a - (u - 1)), yDistance = abs(b - v), manhattan = xDistance + yDistance; //abs is absolute value.  
			if(manhattan < result){
				result = manhattan;
				smallMan = 0;
			}
		}
		if(u + 1 <= 5){ //down
			int xDistance = abs(a - (u + 1)), yDistance = abs(b - v), manhattan = xDistance + yDistance; //abs is absolute value. 
			if(manhattan < result){
				result = manhattan;
				smallMan = 1;
			}
		}
		if(v - 1 >= 0){ //left
			int xDistance = abs(a - u), yDistance = abs(b - (v - 1)), manhattan = xDistance + yDistance; //abs is absolute value. 
			if(manhattan < result){
				result = manhattan;
				smallMan = 2;
			}
		}
		if(v + 1 <= 5){ //right
			int xDistance = abs(a - u), yDistance = abs(b - (v + 1)), manhattan = xDistance + yDistance; //abs is absolute value. 
			if(manhattan < result){
				result = manhattan;
				smallMan = 3;
			}
		}
		moveTo(smallMan);
		return false;
	}		
	
	int maxIndex = 0; //check up first
	//Choose the max value. In the case of a tie, randomize which direction to choose
	for(int i = 1; i < 4; i++){
		if(direction[i] > direction[maxIndex]){
			maxIndex = i;
			tie[0] = false, tie[1] = false, tie[2] = false, tie[3] = false;
		}
		else if(direction[i] == direction[maxIndex])
			tie[maxIndex] = true, tie[i] = true;
	}
		
	if(checkTies(tie)){ 
		int ran = rand() % 4;
		while(!tie[ran] || direction[ran] == -9000)
			ran = rand() % 4;
		moveTo(ran);
	}
	else
		moveTo(maxIndex);
	return true;
}

int Board::wumpusHorizontal(){
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 6; j++){
			if('W' == board[i][j].getSymbol())
				return i;
		}
	}
}

int Board::wumpusVertical(){
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 6; j++){
			if('W' == board[i][j].getSymbol())
				return j;
		}
	}
}

bool Board::wumpusAlive(){
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 6; j++){
			if('W' == board[i][j].getSymbol())
				return true;
		}
	}
	return false;
}

bool Board::killWumpus(int x, int y){
	//we know where the wumpus is.
	//if we are adjacent to the wumpus, and the ai deduces that the wumpus is at that location, then immediately shoot
	//if we are able to perform this algorithm, then return true
	if(!wumpusAlive())
		return false;
	int u = wumpusHorizontal(), v = wumpusVertical();
	
	/*
		More optimized algorithm to kill the wumpus
		This time, focus wrt the player.  
		If the player isn't adjacent to a wumpus, then return false
		Otherwise, determine if the predicted wumpus location is the only area not visited
		If so, return true
		Return false otherwise
	*/
	int saw = 0, obstacle = 0, wumpus = 0;
	if(x - 1 >= 0){ //up
		if(board[x - 1][y].getSymbol() == 'W')
			wumpus = 1;
		if(board[x - 1][y].hasVisited())
			saw++;
		if(board[x - 1][y].getSymbol() != '.')
			obstacle++;
	}
	else
		obstacle++;
	if(x + 1 <= 5){ //down
		if(board[x + 1][y].getSymbol() == 'W')
			wumpus = 1;
		if(board[x + 1][y].hasVisited())
			saw++;
		if(board[x + 1][y].getSymbol() != '.')
			obstacle++;
	}
	else
		obstacle++;
	if(y - 1 >= 0){ //left
		if(board[x][y - 1].getSymbol() == 'W')
			wumpus = 1;
		if(board[x][y - 1].hasVisited())
			saw++;
		if(board[x][y - 1].getSymbol() != '.')
			obstacle++;
	}
	else
		obstacle++;
	if(y + 1 <= 5){ //right 
		if(board[x][y + 1].getSymbol() == 'W')
			wumpus = 1;
		if(board[x][y + 1].hasVisited())
			saw++;
		if(board[x][y + 1].getSymbol() != '.')
			obstacle++;
	}
	else
		obstacle++;
	if(saw > 0 && saw == 4 - obstacle && wumpus == 1){
		if(x - 1 == u && y == v){
			printw("You have successfully killed the wumpus!\n");
			board[u][v].setKill(false);
			board[u][v].setSymbol('.');
			return true;
		}
		if(x + 1 == u && y == v){ //down
			printw("You have successfully killed the wumpus!\n");
			board[u][v].setKill(false);
			board[u][v].setSymbol('.');
			return true;
		}
		if(y - 1 == v && x == u){
			printw("You have successfully killed the wumpus!\n");
			board[u][v].setKill(false);
			board[u][v].setSymbol('.');
			return true;
		}
		if(y + 1 == v && x == u){
			printw("You have successfully killed the wumpus!\n");
			board[u][v].setKill(false);
			board[u][v].setSymbol('.');
			return true;
		}
	}
	return false;
}

void Board::moveTo(int d){
	int x = horizontal(), y = vertical();
	board[x][y].setSymbol('.');
	switch(d){
		case 0: //up
			printw("Moved to (%d, %d)\n", x - 1, y);
			moveEvent(x - 1, y);
			break;
		case 1: //down
			printw("Moved to (%d, %d)\n", x + 1, y);
			moveEvent(x + 1, y);
			break;
		case 2: //left
			printw("Moved to (%d, %d)\n", x, y - 1);
			moveEvent(x, y - 1);
			break;
		case 3: //right
			printw("Moved to (%d, %d)\n", x, y + 1);
			moveEvent(x, y + 1);
			break;
	}
}

void Board::moveEvent(int x, int y){
	if(board[x][y].getSymbol() == 'G'){
		printw("You have found gold!\n");
		board[x][y].setSymbol('A');
	}
	else if(board[x][y].getSymbol() == 'P'){
		printw("You have fallen into the pit and will rot for eternity!\n");
		board[x][y].setSymbol('-');
	}
	else if(board[x][y].getSymbol() == 'B'){
		printw("Oh no, the swarm of bats have placed you in a different location!\n");
		board[x][y].setVisited();
		moveEvent(rand() % 6, rand() % 6);
	}
	else if(board[x][y].getSymbol() == 'W'){
		printw("Oh no, you have become food for the wumpus!\n");
		board[x][y].setSymbol('-');
	}
	else
		board[x][y].setSymbol('A');
}

bool Board::checkTies(bool *tie){
	for(int i = 0; i < 4; i++){
		if(tie[i])
			return true;
	}
	return false;
}

int Board::horizontal(){
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 6; j++){
			if('A' == board[i][j].getSymbol())
				return i;
		}
	}
}

int Board::vertical(){
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 6; j++){
			if('A' == board[i][j].getSymbol())
				return j;
		}
	}
}

bool Board::playerAlive(){
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 6; j++){
			if('-' == board[i][j].getSymbol())
				return false;
		}
	}
	return true;
}

bool Board::checkGold(){
	for(int i = 0; i < 6; i++){
		for(int j = 0; j < 6; j++){
			if('G' == board[i][j].getSymbol())
				return true;
		}
	}
	return false;
}

bool Board::gameDone(int x, int y){
	//x and y are the coordinates holding where the player started out at
	if(checkGold() || wumpusAlive()) //if the wumpus is alive, or the gold is still in the map, then immediately return false
		return false;
	return (x == horizontal() && y == vertical()); // if both the starting coordinates match up with where the player is on the board, then we win
}