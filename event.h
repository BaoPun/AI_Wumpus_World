#ifndef EVENTH
#define EVENTH

#include <iostream> //cout
#include <stdio.h> //snprintf
#include <ncurses.h>
#include <stdlib.h> 
#include <string.h> //char array manipulations
#include <assert.h> //assertions made

using namespace std;

class Event{
	protected:
		char percept[100];
	public:
		Event();
		virtual void read_percept() = 0;	

};

#endif
