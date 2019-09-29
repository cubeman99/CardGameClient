#ifndef _COMMON_TRIGGER_H_
#define _COMMON_TRIGGER_H_

#include "TriggerAction.h"
#include "TriggerCondition.h"
#include "TriggerEvent.h"
#include "TriggerMacros.h"
#include <vector>
#include <string>


class Trigger
{
public:
	Trigger(TriggerEvent* event, TriggerAction* action)
	{
		m_events.push_back(event);
		m_actions.push_back(action);
	}

	Trigger(TriggerEvent* event, TriggerCondition* condition, TriggerAction* action)
	{
		m_events.push_back(event);
		m_conditions.push_back(condition);
		m_actions.push_back(action);
	}
	
	inline std::vector<TriggerEvent*>::iterator events_begin() { return m_events.begin(); }
	inline std::vector<TriggerEvent*>::iterator events_end() { return m_events.end(); }
	
	inline std::vector<TriggerCondition*>::iterator conditions_begin() { return m_conditions.begin(); }
	inline std::vector<TriggerCondition*>::iterator conditions_end() { return m_conditions.end(); }
		
	inline std::vector<TriggerAction*>::iterator actions_begin() { return m_actions.begin(); }
	inline std::vector<TriggerAction*>::iterator actions_end() { return m_actions.end(); }

	//const InputState& GetInputState() const {return m_inputState;}
	//float GetTimeStamp() const { return m_timeStamp; }
	//float GetDeltaTime() const { return m_deltaTime; }
	//int GetMoveNumber() const { return m_moveNumber; }

private:
	std::vector<TriggerEvent*> m_events;
	std::vector<TriggerCondition*> m_conditions;
	std::vector<TriggerAction*> m_actions;
};

class Card;
class CardInstance;
class Game;
class Player;
class Effect;

struct EventResponseContext
{
	CardInstance* dyingUnit;
	CardInstance* attackingUnit;
	CardInstance* interceptingUnit;
	CardInstance* discardedCard;
};

struct Context
{
	Game* game;
	Player* player;
	Player* opponent;
	CardInstance* card;
	Effect* effect;
	Trigger* trigger;
	Event* event;

	//struct
	//{
	//	CardInstance* dyingUnit;

	//} eventResponse;
};

namespace events
{
	DECLARE_EVENT(Aftermath, events::UnitDeath, "Aftermath");
	DECLARE_EVENT(AttackedByUnit, events::UnitAttacked, "Attacked by another unit");
};

namespace conditions
{
	DECLARE_CONDITION(UnitIsAlive, "$1 is alive", CardInstance*,unit);
	DECLARE_CONDITION(UnitIsDead, "$1 is dead", CardInstance*,unit);
};

namespace actions
{
	// General
	DECLARE_ACTION(DoNothing, "Do nothing");
	// TODO: If then else

	// Unit
	DECLARE_ACTION(Summon, "Summon $1 $2", int,count, Card*,card);
	DECLARE_ACTION(DamageAUnit, "Deal $1 damage to $2", int,damage, CardInstance*,unit);
	DECLARE_ACTION(TargetUnit, "Target a unit");
	DECLARE_ACTION(TargetEnemyUnit, "Target an enemy unit");
	DECLARE_ACTION(TargetFriendlyUnit, "Target a friendly unit");
};

namespace functions
{
	namespace unit
	{
		// Event Response
		DECLARE_FUNCTION(CardInstance*, AttackedUnit,		"Attacked unit");
		DECLARE_FUNCTION(CardInstance*, AttackingUnit,		"Attacking unit");
		DECLARE_FUNCTION(CardInstance*, DyingUnit,			"Dying unit");
		DECLARE_FUNCTION(CardInstance*, InterceptingUnit,	"Intercepting unit");
		DECLARE_FUNCTION(CardInstance*, SummonedUnit,		"Summoned unit");
	};

	namespace card
	{
	};

	namespace player
	{
	};

	namespace integer
	{
		// Math
		DECLARE_FUNCTION(int, Min, "Min($1, $2)", int,a, int,b);
		DECLARE_FUNCTION(int, Max, "Max($1, $2)", int,a, int,b);
	};
	
	namespace boolean
	{
		DECLARE_FUNCTION(bool, UnitIsInPlay, "Number of $1 units in play", CardInstance*,unit);
	};
};


#endif // _COMMON_TRIGGER_H_