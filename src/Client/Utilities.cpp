#include "Utilities.h"


CardList::CardList()
{
}

CardList::CardList(const CardList& copy) :
	m_cards(copy.m_cards)
{
}

CardList CardList::operator+(const CardList & other)
{
	CardList result(*this);
	result.m_cards.insert(result.m_cards.end(),
		other.m_cards.begin(), other.m_cards.end());
	return result;
}
