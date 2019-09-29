#ifndef _EVENT_SYSTEM_H_
#define _EVENT_SYSTEM_H_

#include "EventListener.h"
#include <vector>

class Game;


class EventSystem
{
public:
	EventSystem(Game* game);
	~EventSystem();

	void QueueEvent(Event* event);
	void TriggerQueuedEvents();
	void TriggerAnEvent(Event* event);

	void RegisterListener(EventListener* listener);
	void UnregisterListener(EventListener* listener);

private:
	std::vector<Event*> m_eventQueue;
	std::vector<EventListener*> m_eventListeners;
	Game* m_game;
};


#endif // _EVENT_SYSTEM_H_