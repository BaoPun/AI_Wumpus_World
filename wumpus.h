#ifndef WUMPUSH
#define WUMPUSH

#include "./event.h"

class Wumpus : public Event{
	public:
		Wumpus();
		void read_percept();
};

#endif
