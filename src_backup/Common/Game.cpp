#include "Game.h"

Game::Game() :
	m_eventSystem(this),
	m_turnIndex(0)
{
	m_players[0].m_name = "Player 1";
	m_players[1].m_name = "Player 2";
}

Game::~Game()
{

}

void Game::SummonUnit(Card* card, Player* player)
{
	// Create the card instance.
	CardInstance* unit = m_cardManager.CreateCardInstance(card, player);

	// Add the card to the player's field.
	unit->m_cardList = &player->m_field;
	player->m_field.AddCard(unit);
	
	// Trigger a summon event.
	m_eventSystem.TriggerAnEvent(new events::UnitSummon(unit));
}

void Game::DamageUnit(CardInstance* unit, int damage)
{
	// Damage the unit's health.
	unit->m_health -= damage;

	// Trigger a damage event.
	if (damage > 0)
	{
		m_eventSystem.TriggerAnEvent(new Event(EventType::UNIT_DAMAGED));
	}

	if (unit->m_health <= 0)
	{
		// Trigger a death event.
		m_eventSystem.TriggerAnEvent(new events::UnitDeath(unit));

		// Move the unit to the discard pile.
		unit->m_cardList->RemoveCard(unit);
		unit->m_owner->m_discardPile.AddCard(unit);
	}
}

void Game::PrintCurrentState(std::ostream& out)
{
	out << "Turn " << (m_turnIndex + 1) << ":" << std::endl;

	for (unsigned int i = 0; i < 2; ++i)
	{
		Player* player = m_players + i;

		out << "  Player: " << player->GetName() << std::endl;

		out << "    Field: ";
		for (auto it = player->m_field.m_cards.begin();
			it != player->m_field.m_cards.end(); ++it)
		{
			CardInstance* card = *it;
			out << card->GetPower() << "/" << card->GetHealth() << " " << card->GetName() << ", ";
		}
		out << std::endl;

		out << "    Hand: ";
		out << std::endl;

	}
}
