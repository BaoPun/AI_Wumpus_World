#include "./event.h"

Event::Event(){
	memset(percept, sizeof(percept), '\0');
	snprintf(percept, sizeof(percept), "");
	percept[strcspn(percept, "\n")] = '\0';
}
