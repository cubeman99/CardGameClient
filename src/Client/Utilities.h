#ifndef _CARD_GAME_UTILITIES_H_
#define _CARD_GAME_UTILITIES_H_

#include "Tags.h"
#include <vector>

class Card;


class CardList
{
public:
	typedef std::vector<Card*>::iterator iterator;

public:
	CardList();
	CardList(const CardList& copy);

	inline iterator begin() { return m_cards.begin(); }
	inline iterator end() { return m_cards.end(); }

	inline int size() { return (int) m_cards.size(); }

	inline Card* operator [](int index) { return m_cards[index]; }

	inline void push_back(Card* entity) { m_cards.push_back(entity); }
	CardList operator +(const CardList& other);

private:
	std::vector<Card*> m_cards;
};



#endif // _CARD_GAME_UTILITIES_H_