#ifndef _EVENT_LISTENER_H_
#define _EVENT_LISTENER_H_

#include "Event.h"


class EventListener
{
public:

	virtual void HandleEvent(Event* e) = 0;
};


#endif // _EVENT_LISTENER_H_