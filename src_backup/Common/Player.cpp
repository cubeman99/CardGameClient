#include "Player.h"

Player::Player()
{
	m_name = "";

	m_deck.m_owner = this;
	m_hand.m_owner = this;
	m_field.m_owner = this;
	m_discardPile.m_owner = this;

	m_supply = 0;
	m_morale = 0;
}


