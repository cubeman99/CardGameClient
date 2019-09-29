#ifndef _COMMON_TRIGGER_EVENT_H_
#define _COMMON_TRIGGER_EVENT_H_

#include <string>
//#include "Card.h"
#include "TriggerFunction.h"
#include "events/Event.h"
#include "events/EventListener.h"


// listen to event, return true/false on event trigger.
class TriggerEvent : public TriggerFunction<bool>, public EventListener
{
public:
	TriggerEvent() {}

	virtual bool CheckEvent(Context* context, Event* event) 
	{
		return true;
	}
	
	void HandleEvent(Event* e) override;

private:
};


#endif // _COMMON_TRIGGER_EVENT_H_