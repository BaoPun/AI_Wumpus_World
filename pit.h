#ifndef PITH
#define PITH

#include "./event.h"

class Pit : public Event{
	public:
		Pit();
		void read_percept();
};


#endif
