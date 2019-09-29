#include "Trigger.h"
#include <iostream>
#include "Game.h"
#include "events/Event.h"
#include "CardInstance.h"


namespace events
{
	DEFINE_EVENT(Aftermath, events::UnitDeath)
	{
		// Return true if the dying unit is me.
		return (event->GetUnit() == context->card);
	}

	DEFINE_EVENT(AttackedByUnit, events::UnitAttacked)
	{
		// Return true if the attacked unit is me.
		return (event->GetAttackedUnit() == context->card);
	}
};

namespace conditions
{
	DEFINE_CONDITION(UnitIsAlive, CardInstance*,unit)
	{
		return unit->IsAlive();
	}
	DEFINE_CONDITION(UnitIsDead, CardInstance*,unit)
	{
		return unit->IsDead();
	}

};

namespace actions
{
	DEFINE_ACTION(DoNothing)
	{
		// Actually do nothing.
		std::cout << "(doing nothing)" << std::endl;
		return 0;
	}

	DEFINE_ACTION(Summon, int,count, Card*,card)
	{
		//std::cout << "Summoning " << count << " " << card->m_name << std::endl;
		for (int i = 0; i < count; ++i)
			context->game->SummonUnit(card, context->player);
		return 0;
	}

	DEFINE_ACTION(DamageAUnit, int,damage, CardInstance*,unit)
	{
		context->game->DamageUnit(unit, damage);
		return 0;
	}

	
	DEFINE_ACTION(TargetUnit)
	{
		
		return 0;
	}

	DEFINE_ACTION(TargetEnemyUnit)
	{
		return 0;
	}

	DEFINE_ACTION(TargetFriendlyUnit)
	{
		return 0;
	}
};

namespace functions
{
	namespace unit
	{

		DEFINE_FUNCTION(CardInstance*, AttackedUnit)
		{
			return nullptr;
		}

		DEFINE_FUNCTION(CardInstance*, AttackingUnit)
		{
			//if (context->event->GetType() == EventType::UNIT_DEATH)
				//return ((events::UnitDeath*) context->event)->GetUnit();
			//else if (context->event->GetType() == EventType::UNIT_DAMAGED)
				//return ((events::UnitDeath*) context->event)->GetUnit();
			return nullptr;
		}
		
		DEFINE_FUNCTION(CardInstance*, DyingUnit)
		{
			if (context->event->GetType() == EventType::UNIT_DEATH)
				return ((events::UnitDeath*) context->event)->GetUnit();
			return nullptr;
		}

		DEFINE_FUNCTION(CardInstance*, InterceptingUnit)
		{
			return nullptr;
		}
		
		DEFINE_FUNCTION(CardInstance*, SummonedUnit)
		{
			if (context->event->GetType() == EventType::UNIT_SUMMON)
				return ((events::UnitSummon*) context->event)->GetUnit();
			return nullptr;
		}

	};

	namespace card
	{
	};

	namespace player
	{
	};

	namespace integer
	{
		DEFINE_FUNCTION(int, Max, int,a, int,b)
		{
			return Math::Max(a, b);
		}

		DEFINE_FUNCTION(int, Min, int,a, int,b)
		{
			return Math::Min(a, b);
		}
	};
	
	namespace boolean
	{
	};
};