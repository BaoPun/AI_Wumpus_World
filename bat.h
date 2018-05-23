#ifndef BATH
#define BATH

#include "./event.h"

class Bat : public Event{
	public:
		Bat();
		void read_percept();
};

#endif
