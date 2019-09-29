#ifndef _COMMON_CARD_INSTANCE_H_
#define _COMMON_CARD_INSTANCE_H_

#include <iostream>
#include <string>
#include <vector>
#include "GameRules.h"
#include <GameLib/math/Vector2f.h>
#include "Effect.h"
#include "Card.h"

class Player;
class Effect;
class CardInstance;
class CardList;


class CardInstance
{
public:
	CardInstance(Card* card) :
		m_card(card)
	{
		m_health = card->m_health;
		m_maxHealth = card->m_health;
		m_power = card->m_power;
		m_defaultHealth = card->m_health;
		m_defaultPower = card->m_power;
		m_flipped = false;
		m_id = 1;
		m_owner = nullptr;

		m_attackedBy = nullptr;
		m_attackTarget = nullptr;

		m_selectable = true;

		if (card->m_cardTextEffect != nullptr)
			m_effects.push_back(card->m_cardTextEffect);
	}
	~CardInstance()
	{
		for (unsigned int i = 0; i < m_effects.size(); ++i)
		{
			delete m_effects[i];
		}
		m_effects.clear();
	}

	void Unflip()
	{
		m_flipped = 0;
	}
	void AddEffect(Effect* effect)
	{
		m_effects.push_back(effect);
	}
	inline const std::string GetName() const { return m_card->m_name; }
	inline int GetHealth() const { return m_health; }
	inline int GetPower() const { return m_power; }
	inline const Tribe* GetTribe() const { return m_card->m_tribe; }
	inline bool IsFlipped() const { return m_flipped; }
	inline bool CanAttack() const { return !m_flipped; }

	inline bool IsDead() const { return (m_health <= 0); }
	inline bool IsAlive() const { return (m_health > 0); }

	inline std::vector<Effect*>::iterator effects_begin() { return m_effects.begin(); }
	inline std::vector<Effect*>::iterator effects_end() { return m_effects.end(); }

public:
	Card* m_card;
	int m_health;
	int m_maxHealth;
	int m_power;
	int m_defaultHealth;
	int m_defaultPower;
	bool m_flipped;
	int m_id;
	std::vector<Effect*> m_effects;

	int m_unflippedHealth;
	int m_unflippedPower;
	int m_unflippedMaxHealth;
	int m_unflippedDefaultPower;
	int m_unflippedDefaultHealth;

	Player* m_owner;
	CardList* m_cardList;
	bool m_selectable;
	Vector2f m_position;
	CardInstance* m_attackTarget;
	CardInstance* m_attackedBy;
};


#endif // _COMMON_CARD_INSTANCE_H_