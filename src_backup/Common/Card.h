#ifndef _COMMON_CARD_H_
#define _COMMON_CARD_H_

#include <iostream>
#include <string>
#include <vector>
#include "GameRules.h"
#include <GameLib/math/Vector2f.h>
#include "Effect.h"


using namespace std;

class Card;
class Player;
class Effect;
class CardInstance;
class CardList;

class LogSystem
{
public:
	LogSystem();

private:

};


// Buffs
//class Effect
//{
//public:
//
//public:
//	int m_health;
//	int m_attack;
//};

class Tribe
{
public:
	Tribe(const std::string& name) :
		m_name(name)
	{
	}

	inline const std::string& GetName() const { return m_name; }

public:
	std::string m_name;
};

class Card
{
public:
	Card() :
		m_health(1),
		m_power(1),
		m_tribe(nullptr),
		m_cardTextEffect(nullptr)
	{
	}

	int m_health;
	int m_power;
	std::string m_name;
	Tribe* m_tribe;
	Effect* m_cardTextEffect;
};

inline std::ostream& operator <<(std::ostream& out, Card* card)
{
	out << "(" << card->m_power << "/" << card->m_health << " " << card->m_name << ")";
	return out;
}


#endif // _COMMON_CARD_H_
