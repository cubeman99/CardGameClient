#ifndef _EVENT_H_
#define _EVENT_H_

class CardInstance;

enum class EventType
{
	// General
	ANY_EVENT,

	// Unit
	UNIT_SUMMON,
	UNIT_DEATH,
	UNIT_DAMAGED,
	UNIT_ATTACKED,

	// Player
	PLAYER_DRAW_CARD,
};


class Event
{
public:
	Event();
	Event(EventType type);
	virtual ~Event();

	EventType GetType() const { return m_type; }

protected:
	EventType m_type;
};


namespace events
{
	class UnitSummon : public Event
	{
	public:
		UnitSummon(CardInstance* unit)
		{
			m_type = EventType::UNIT_SUMMON;
			m_unit = unit;
		}

		CardInstance* GetUnit() { return m_unit; }

	public:
		CardInstance* m_unit;
	};
	
	class UnitDeath : public Event
	{
	public:
		UnitDeath(CardInstance* unit)
		{
			m_type = EventType::UNIT_DEATH;
			m_unit = unit;
		}

		CardInstance* GetUnit() { return m_unit; }

	public:
		CardInstance* m_unit;
	};
	
	class UnitAttacked : public Event
	{
	public:
		UnitAttacked(CardInstance* attackingUnit, CardInstance* attackedUnit)
		{
			m_type = EventType::UNIT_ATTACKED;
			m_attackingUnit = attackingUnit;
			m_attackedUnit = attackedUnit;
		}

		CardInstance* GetAttackedUnit() { return m_attackingUnit; }
		CardInstance* GetAttackingUnit() { return m_attackingUnit; }

	public:
		CardInstance* m_attackingUnit;
		CardInstance* m_attackedUnit;
	};
};


#endif // _EVENT_H_