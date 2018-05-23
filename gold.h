#ifndef GOLDH
#define GOLDH

#include "./event.h"

class Gold : public Event{
	public:
		Gold();
		void read_percept();
};

#endif
