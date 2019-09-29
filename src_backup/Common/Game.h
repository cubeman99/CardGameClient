#ifndef _COMMON_GAME_H_
#define _COMMON_GAME_H_

#include "CardInstance.h"
#include "Playerh"
#include "events/EventSystem.h"


class CardManager
{
public:
	CardManager()
	{
		m_idCounter = 1;
	}
	~CardManager()
	{
		DeleteAllCards();
		m_idCounter = 1;
	}
	
	void DeleteAllCards()
	{
		for (unsigned int i = 0; i < m_cards.size(); ++i)
			delete m_cards[i];
		m_cards.clear();
	}

	CardInstance* CreateNewCard(Card* card, Player* player)
	{
		CardInstance* cardInstance = new CardInstance(card);
		cardInstance->m_owner = player;
		cardInstance->m_id = m_idCounter;
		m_cards.push_back(cardInstance);
		++m_idCounter;
		return cardInstance;
	}

	CardInstance* CreateCardInstance(Card* card, Player* player)
	{
		CardInstance* cardInstance = new CardInstance(card);
		cardInstance->m_owner = player;
		cardInstance->m_id = m_idCounter;
		m_cards.push_back(cardInstance);
		++m_idCounter;
		return cardInstance;
	}

public:
	int m_idCounter;
	std::vector<CardInstance*> m_cards;
};


class CardDatabase
{
public:
	CardDatabase()
	{
	}

	~CardDatabase()
	{
		for (unsigned int i = 0; i < m_cards.size(); ++i)
			delete m_cards[i];
		m_cards.clear();
	}

	Card* CreateCard(const std::string& name, int power, int health, Tribe* tribe = nullptr)
	{
		Card* card = new Card();
		card->m_name = name;
		card->m_power = power;
		card->m_health = health;
		card->m_tribe = tribe;
		m_cards.push_back(card);
		return card;
	}

public:
	std::vector<Card*> m_cards;
};


// Turn Order:
// -----------------------------------------------------------
// (begin turn)
// Unflip step: unflip all flipped cards
// Resource step: choose resource (pick 2: card, morale, supply)
// Battle Step:
//   Declare Step: Decide which cards attack what, or to retreat or flip them, battle cards can be played now
//   Response Step: Opponent can select units (not being attacked) to intercept attacks, opponent can also play battle cards now
//   Combat: All combat resolves
// Play: Play spells
// (end turn)


// Holds game state information and functions for game simulation.
class Game
{
public:
	Game();
	~Game();

	inline Player* GetPlayer(int playerIndex) { return m_players + playerIndex; }

	void SummonUnit(Card* card, Player* player);

	void DamageUnit(CardInstance* unit, int damage);

	void PrintCurrentState(std::ostream& out);

private:
	int				m_turnIndex;
	Player			m_players[2];
	CardDatabase	m_cardDatabase;
	CardManager		m_cardManager;
	EventSystem		m_eventSystem;
};


#endif // _COMMON_GAME_H_