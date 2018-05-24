# AI_Wumpus_World

Wumpus World in the eyes of a basic AI
Compiled using g++ -lncurses *.cpp (-o [exe name]), where () is optional.
Used <ncurses.h> to get keyboard input. 

# Objective

Kill the wumpus, grab the gold bag, and then return to the starting position (order of wumpus hunting and gold grabbing doesn't matter)

# Obstacles in Wumpus World

1 wumpus, 1 bag of gold, 2 pits, 2 bats.
Wumpus is the creature we're trying to kill.
Bag of gold is what we want to grab.
Pit is a bottomless crevice that we do not want to fall into.
Bat is a swarm of winged creatures that will randomly place us in a different location within the maze. It can even land on any events described above.

# Moving Wumpus

Mark current area as visited, scan area around AI.  Any percepts should be flagged with its respective boolean variable.
Determines the best move by usage of boolean logic (how many percepts are read, how safe is it to traverse through an unknown space)
If there is a "tie", then randomly choose the best move. 

# Killing Wumpus

Check rooms adjacent to player.  To determine if the AI can certainly kill the wumpus, do the following:
1. Scan the adjacent rooms
2. Keep track of safe areas and obstacles (obstacles = all events + wall)
3. Check if the following formula is true: saw = 4 - obstacle.
	A. saw is the # of safe spaces, obstacle is # of walls and/or events that affect the player when they try to approach that way.  4 is the max # of paths player can take.
	B. By itself, the formula does not guarantee that the wumpus is near the player.
	C. But we can include a flag to determine if the wumpus is nearby (if there's a stench).  If there's a stench, then this formula will detect presence of wumpus.
4. If formula is true, and we detected a stench, then return true
5. Else, return false.

# End game

After killing wumpus and grabbing the gold, use manhattan distance to get optimal path from current location to start location
Manhattan distance = |xstart - xcurrent| + |ystart - ycurrent|, where current = current location of player and start = starting location upon playing the game
