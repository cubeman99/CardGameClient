#include "EventSystem.h"
#include "Game.h"
#include "triggers/TriggerEvent.h"


EventSystem::EventSystem(Game* game) :
	m_game(game)
{
}

EventSystem::~EventSystem()
{

}


void EventSystem::QueueEvent(Event* event)
{
	m_eventQueue.push_back(event);
}

void EventSystem::TriggerQueuedEvents()
{
	while (m_eventQueue.size() > 0)
	{
		TriggerAnEvent(m_eventQueue[0]);
		m_eventQueue.erase(m_eventQueue.begin());
	}
}

void EventSystem::TriggerAnEvent(Event* event)
{
	//printf("Triggering event\n");

	Context context;
	context.game = m_game;
	context.event = event;

	// Loop through each player.
	for (unsigned int i = 0; i < 2; ++i)
	{
		context.player = m_game->GetPlayer(i);
		context.opponent = m_game->GetPlayer(1 - i);

		// Loop through all the player's cards on board.
		for (unsigned int j = 0; j < context.player->GetPlayField()->m_cards.size(); ++j)
		{
			context.card = context.player->GetPlayField()->m_cards[j];

			// Loop through card effects.
			for (auto iterEffect = context.card->effects_begin();
				iterEffect != context.card->effects_end();
				++iterEffect)
			{
				context.effect = *iterEffect;
				
				// Loop through effect triggers.
				for (auto iterTrigger = context.effect->triggers_begin();
					iterTrigger != context.effect->triggers_end();
					++iterTrigger)
				{
					context.trigger = *iterTrigger;
					
					// Loop through trigger events.
					for (auto iterEvent = context.trigger->events_begin();
						iterEvent != context.trigger->events_end();
						++iterEvent)
					{
						TriggerEvent* triggerEvent = *iterEvent;
						
						if (triggerEvent->CheckEvent(&context, event))
						{
							bool passedConditions = true;

							// Check conditions.
							for (auto iterCondition = context.trigger->conditions_begin();
								iterCondition != context.trigger->conditions_end();
								++iterCondition)
							{
								TriggerCondition* condition = *iterCondition;
								bool result = condition->Execute(&context);
								if (result)
									std::cout << "Passed condition: " << condition->GetText() << std::endl;
								else
									std::cout << "Failed condition: " << condition->GetText() << std::endl;
								if (!result)
								{
									passedConditions = false;
									break;
								}
							}

							if (!passedConditions)
								continue;

							std::cout << "Triggering event: " << triggerEvent->GetText() << std::endl;

							// Invoke actions.
							for (auto iterAction = context.trigger->actions_begin();
								iterAction != context.trigger->actions_end();
								++iterAction)
							{
								TriggerAction* action = *iterAction;
								std::cout << "Invoking action: " << action->GetText() << std::endl;
								action->Execute(&context);
							}
						}
					}
				}
			}
		}
	}

	// TODO: notify listeners
	//for (auto it = m_eventListeners.begin(); it != m_eventListeners.end(); ++it)
	//{
	//	EventListener* listener = *it;
	//	if (listener->
	//	listener->HandleEvent(event);
	//}

	delete event;
	event = nullptr;
}


void EventSystem::RegisterListener(EventListener* listener)
{
	// Only add if not already added to list.
	auto it = std::find(m_eventListeners.begin(), m_eventListeners.end(), listener);
	if (it == m_eventListeners.end())
		m_eventListeners.push_back(listener);
}

void EventSystem::UnregisterListener(EventListener* listener)
{
	// Only remove if exists in list.
	auto it = std::find(m_eventListeners.begin(), m_eventListeners.end(), listener);
	if (it != m_eventListeners.end())
		m_eventListeners.erase(it);
}



