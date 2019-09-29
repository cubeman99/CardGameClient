#ifndef _COMMON_PLAYER_H_
#define _COMMON_PLAYER_H_

#include <iostream>
#include <string>
#include <vector>
#include "GameRules.h"
#include "CardInstance.h"

class Card;
class Player;
class Effect;
class CardInstance;
class CardList;


// Deck, Hand, Graveyard, Play-Field
class CardList
{
public:
	void AddCard(CardInstance* card)
	{
		m_cards.push_back(card);
		card->m_cardList = this;
	}

	void RemoveCard(CardInstance* card)
	{
		auto it = std::find(m_cards.begin(), m_cards.end(), card);
		if (it != m_cards.end())
		{
			m_cards.erase(it);
			card->m_cardList = nullptr;
		}
	}

public:
	std::vector<CardInstance*> m_cards;
	Player* m_owner;
};


class Hand : public CardList
{
public:
};


class Deck : public CardList
{
public:
};


class DiscardPile : public CardList
{
public:
};


class PlayField : public CardList
{
public:
};


class Player
{
public:
	Player();

	inline const std::string& GetName() const { return m_name; }

	inline Hand* GetHand() { return &m_hand; }
	inline Deck* GetDeck() { return &m_deck; }
	inline PlayField* GetPlayField() { return &m_field; }
	inline DiscardPile* GetDiscardPile() { return &m_discardPile; }

	inline int GetSupply() const { return m_supply; }
	inline int GetMorale() const { return m_morale; }

public:
	std::string m_name;

	// Play zones
	Deck m_deck;
	Hand m_hand;
	PlayField m_field;
	DiscardPile m_discardPile;

	// Resources
	int m_supply;
	int m_morale;
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


#endif // _COMMON_PLAYER_H_