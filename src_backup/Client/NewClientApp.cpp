#include "NewClientApp.h"
#include <GameLib/graphics/Graphics.h>
#include <GameLib/util/Timing.h>
#include <math/MathLib.h>
#include <sstream>


NewClientApp::NewClientApp() :
	m_fontSmall(NULL),
	m_fontScore(NULL)
{
}

NewClientApp::~NewClientApp()
{
	delete m_fontScore;
	delete m_fontSmall;
}

float NewClientApp::GetTimeStamp()
{
	// TODO: fix this.
	return (float) Time::GetTime();
}

void NewClientApp::OnInitialize()
{
	// Load resources.
	m_fontScore = Font::LoadFont("assets/AlteHaasGroteskBold.ttf", 24, 32, 128);
	m_fontSmall = Font::LoadFont("assets/AlteHaasGroteskRegular.ttf", 11, 32, 128);

	m_selectedCard = nullptr;
	m_mousedOverCard = nullptr;

	// Initialize players
	m_players[0] = new Player();
	m_players[1] = new Player();

	m_tribeSlug = new Tribe("Slug");

	//Card* card;

	Card* cardBreweryServant = m_cardDatabase.CreateCard("Brewery Servant", 1, 2, m_tribeSlug);

	//m_players[0]->m_hand.AddCard(m_cardManager.CreateNewCard(cardBreweryServant, m_players[0]));

	m_players[0]->m_field.AddCard(m_cardManager.CreateNewCard(cardBreweryServant, m_players[0]));
	m_players[0]->m_field.AddCard(m_cardManager.CreateNewCard(cardBreweryServant, m_players[0]));
	m_players[0]->m_field.AddCard(m_cardManager.CreateNewCard(cardBreweryServant, m_players[0]));

	m_players[1]->m_field.AddCard(m_cardManager.CreateNewCard(cardBreweryServant, m_players[1]));
	m_players[1]->m_field.AddCard(m_cardManager.CreateNewCard(cardBreweryServant, m_players[1]));
	m_players[1]->m_field.AddCard(m_cardManager.CreateNewCard(cardBreweryServant, m_players[1]));

	Card* tokenTentacles = m_cardDatabase.CreateCard("Brewery Servant", 1, 2, m_tribeSlug);

	//Trigger(
	//	new events::Aftermath(),
	//	new actions::Summon(1, tokenTentacles)
	//);
}

void NewClientApp::OnQuit()
{
	m_cardManager.DeleteAllCards();

	delete m_players[0];
	m_players[0] = nullptr;
	delete m_players[1];
	m_players[1] = nullptr;

	delete m_tribeSlug;
	m_tribeSlug = nullptr;
}

void NewClientApp::OnUpdate(float timeDelta)
{
	auto keyboard = GetKeyboard();
	auto mouse = GetMouse();

	// Escape: Quit the game.
	if (keyboard->IsKeyPressed(Keys::ESCAPE))
	{
		Quit();
		return;
	}
	
	if (keyboard->IsKeyPressed(Keys::ENTER))
	{
		ResolveCombat();
	}
	
	if (keyboard->IsKeyPressed(Keys::A))
	{
		if (m_attackMoves.size() > 0)
			ResolveNextAttack();
	}

	if (keyboard->IsKeyPressed(Keys::U))
	{
		UnflipAllCards(m_players[0]);
	}

	Vector2f cardSize(150.0f, 150.0f);
	Vector2f mousePos((float) GetMouse()->GetX(), (float) GetMouse()->GetY());
	//Vector2f windowSize((float) GetWindow()->GetWidth(), (float) GetWindow()->GetHeight());
	m_mousedOverCard = nullptr;

	for (unsigned int i = 0; i < m_cardManager.m_cards.size(); ++i)
	{
		CardInstance* card = m_cardManager.m_cards[i];
		if (card->m_selectable)
		{
			Rect2f cardRect = Rect2f(card->m_position - (cardSize * 0.5f), cardSize);
			if (cardRect.Contains(mousePos))
			{
				m_mousedOverCard = card;
			}
		}
	}

	if (m_selectedCard != nullptr)
	{
		if (GetMouse()->IsButtonPressed(MouseButtons::RIGHT))
		{
			m_selectedCard = nullptr;
		}
		else if (GetMouse()->IsButtonPressed(MouseButtons::LEFT) &&
			m_mousedOverCard != nullptr && m_mousedOverCard != m_selectedCard)
		{
			DeclareAttack(m_selectedCard, m_mousedOverCard);
			m_selectedCard = nullptr;
		}
	}
	else if (m_mousedOverCard != nullptr && GetMouse()->IsButtonPressed(MouseButtons::LEFT))
	{
		if (keyboard->IsKeyDown(Keys::LCONTROL))
		{
			FlipCard(m_mousedOverCard);
		}
		else if (m_mousedOverCard->CanAttack())
		{
			m_selectedCard = m_mousedOverCard;
			UndeclareAttack(m_selectedCard);
		}
	}
}

void NewClientApp::FlipCard(CardInstance* card)
{
	card->m_flipped = true;

	card->m_unflippedPower = card->m_power;
	card->m_unflippedHealth = card->m_health;
	card->m_unflippedMaxHealth = card->m_maxHealth;
	card->m_unflippedDefaultHealth = card->m_defaultHealth;
	card->m_unflippedDefaultPower = card->m_defaultPower;

	card->m_power = 0;
	card->m_defaultPower = 0;

	card->m_health = 1;
	card->m_maxHealth = 1;
	card->m_defaultHealth = 1;
}

void NewClientApp::UnflipCard(CardInstance* card)
{
	card->m_flipped = false;
	
	card->m_health = card->m_unflippedHealth;
	card->m_power = card->m_unflippedPower;
	card->m_maxHealth = card->m_unflippedMaxHealth;
	card->m_defaultHealth = card->m_unflippedDefaultHealth;
	card->m_defaultPower = card->m_unflippedDefaultPower;

	card->m_owner->m_supply += 1;
}

void NewClientApp::DeclareAttack(const AttackMove& attack)
{
	m_attackMoves.push_back(new AttackMove(attack));
}

void NewClientApp::DeclareAttack(CardInstance* subject, CardInstance* target)
{
	AttackMove* attack = new AttackMove();
	attack->m_subject = subject;
	attack->m_target = target;
	m_attackMoves.push_back(attack);
}

void NewClientApp::UndeclareAttack(AttackMove* attack)
{
	for (auto it = m_attackMoves.begin(); it != m_attackMoves.end(); ++it)
	{
		if (*it == attack)
		{
			m_attackMoves.erase(it);
			return;
		}
	}
}

void NewClientApp::UndeclareAttack(CardInstance* card)
{
	for (auto it = m_attackMoves.begin(); it != m_attackMoves.end(); ++it)
	{
		if ((*it)->m_subject == card)
		{
			m_attackMoves.erase(it);
			return;
		}
	}
}

AttackMove* NewClientApp::GetAttack(CardInstance* card)
{
	for (unsigned int i = 0; i < m_attackMoves.size(); ++i)
	{
		if (m_attackMoves[i]->m_subject == card)
			return m_attackMoves[i];
	}
	return nullptr;
}

void NewClientApp::UnflipAllCards(Player* player)
{
	PlayField* field = player->GetPlayField();

	for (unsigned int i = 0; i < field->m_cards.size(); ++i)
	{
		CardInstance* card = field->m_cards[i];

		if (card->IsFlipped())
		{
			UnflipCard(card);
		}
	}
}

void NewClientApp::ResolveCombat()
{
	// Resolve each attack.
	while (m_attackMoves.size() > 0)
	{
		ResolveNextAttack();
	}
}

void NewClientApp::ResolveNextAttack()
{
	AttackMove* attack = m_attackMoves[0];
	m_attackMoves.erase(m_attackMoves.begin());

	ResolveAttack(attack);

	delete attack;
}

void NewClientApp::ResolveAttack(AttackMove* attack)
{
	attack->m_subject->m_health -= attack->m_target->m_power;
	attack->m_target->m_health -= attack->m_subject->m_power;

	if (attack->m_subject->m_health <= 0)
		ResolveDeath(attack->m_subject);
	if (attack->m_target->m_health <= 0)
		ResolveDeath(attack->m_target);
}

void NewClientApp::ResolveDeath(CardInstance* unit)
{
	// TODO: trigger aftermath

	// Remove the unit from play, and add it to the discard pile.
	unit->m_cardList->RemoveCard(unit);
	unit->m_owner->GetDiscardPile()->AddCard(unit);
	unit->m_selectable = false;
	// Dismiss attacks declared on or by this unit.
	for (unsigned int i = 0; i < m_attackMoves.size(); ++i)
	{
		AttackMove* attack = m_attackMoves[i];
		if (attack->m_subject == unit || attack->m_target == unit)
		{
			delete attack;
			m_attackMoves.erase(m_attackMoves.begin() + (i--));
		}
	}
}

void NewClientApp::DrawCard(Graphics& g, CardInstance* card, const Vector2f& position)
{
	float ratio = 1.0f;
	float width = 150;
	Vector2f cardSize(width, width * ratio);
	std::stringstream str;

	// Draw card outline.
	Color outlineColor = Color::WHITE;
	if (card == m_mousedOverCard)
		outlineColor = Color::YELLOW;
	g.DrawRect(position - (cardSize * 0.5f), cardSize, outlineColor);

	// Draw name.
	g.DrawString(m_fontSmall, card->GetName(),
		position - Vector2f(0.0f, cardSize.y) * 0.5f,
		Color::YELLOW, Align::TOP_CENTER);

	// Draw tribe.
	if (card->GetTribe() != nullptr)
	{
		g.DrawString(m_fontSmall, card->GetTribe()->m_name,
			position - Vector2f(0.0f, cardSize.y * 0.5f - 18),
			Color::WHITE, Align::TOP_CENTER);
	}

	// Draw ID.
	if (card->GetTribe() != nullptr)
	{
		str.str("");
		str << "" << card->m_id;
		g.DrawString(m_fontSmall, str.str(),
			position + Vector2f(0.0f, cardSize.y * 0.5f - 18),
			Color::GRAY, Align::TOP_CENTER);
	}

	// Draw ID.
	if (card->IsFlipped())
	{
		g.DrawString(m_fontSmall, "Flipped",
			position, Color::YELLOW, Align::CENTERED);
	}
	
	float radius = 20.0f;
	Vector2f healthPos = position + Vector2f(-cardSize.x, cardSize.y) * 0.5f + Vector2f(radius, -radius) * 0.7f;
	Vector2f powerPos  = position + Vector2f(cardSize.x, cardSize.y) * 0.5f + Vector2f(-radius, -radius) * 0.7f;
	
	// Draw power.
	str.str("");
	str << card->GetPower();
	Color powerColor = Color::WHITE;
	if (card->GetPower() < card->m_defaultPower)
		powerColor = Color::RED;
	else if (card->GetPower() > card->m_defaultPower)
		powerColor = Color::GREEN;
	g.FillCircle(healthPos, radius, Color::BLACK);
	g.DrawCircle(healthPos, radius, Color::WHITE);
	g.DrawString(m_fontScore, str.str(),
		healthPos, powerColor, Align::CENTERED);

	// Draw health.
	str.str("");
	str << card->GetHealth();
	Color healthColor = Color::WHITE;
	if (card->GetHealth() < card->m_defaultHealth)
		healthColor = Color::RED;
	else if (card->GetHealth() > card->m_defaultHealth)
		healthColor = Color::GREEN;
	g.FillCircle(powerPos, radius, Color::BLACK);
	g.DrawCircle(powerPos, radius, Color::WHITE);
	g.DrawString(m_fontScore, str.str(),
		powerPos, healthColor, Align::CENTERED);
}

void NewClientApp::DrawField(Graphics& g, Player* player, const Vector2f& center)
{
	PlayField* field = player->GetPlayField();
	float numUnitsInPlay = (float) field->m_cards.size();

	for (unsigned int i = 0; i < field->m_cards.size(); ++i)
	{
		CardInstance* card = field->m_cards[i];

		float percent = ((float) i - ((numUnitsInPlay - 1) * 0.5f));
		card->m_position.x = center.x + percent * 200;
		card->m_position.y = center.y;

		DrawCard(g, card, card->m_position);
	}
}

void NewClientApp::DrawHand(Graphics& g, Player* player, const Vector2f& center)
{
	Hand* hand = player->GetHand();
	float numCardsInHand = (float) hand->m_cards.size();

	for (unsigned int i = 0; i < hand->m_cards.size(); ++i)
	{
		CardInstance* card = hand->m_cards[i];

		float percent = ((float) i - ((numCardsInHand - 1) * 0.5f));
		card->m_position.x = center.x + percent * 200;
		card->m_position.y = center.y;

		DrawCard(g, card, card->m_position);
	}
}

void NewClientApp::OnRender()
{
	Vector2f mousePos((float) GetMouse()->GetX(), (float) GetMouse()->GetY());
	Vector2f windowSize((float) GetWindow()->GetWidth(), (float) GetWindow()->GetHeight());

	// Set up a graphics drawer.
	Graphics g(GetWindow());
	g.SetViewport(Viewport(0, 0, GetWindow()->GetWidth(),
		GetWindow()->GetHeight()), false, true);
	g.SetProjection(Matrix4f::CreateOrthographic(0.0f,
		windowSize.x, windowSize.y, 0.0f, 1.0f, -1.0f));
	g.ResetTransform();

	g.Clear(Color::BLACK);
	
	std::stringstream ss;

	//g.DrawString(m_fontScore, "Hello World!",
		//windowSize.x * 0.5f, windowSize.y * 0.5f,
		//Color::WHITE, Align::CENTER);

	// Draw hands
	//Hand* hand = m_players[0]->GetHand();
	//for (unsigned int i = 0; i < hand->m_cards.size(); ++i)
	//{
	//	hand->m_cards[i]->m_position = Vector2f(200 + i * 200, 400);
	//	DrawCard(g, hand->m_cards[i], hand->m_cards[i]->m_position);
	//}

	// Draw field
	DrawField(g, m_players[0], Vector2f(windowSize.x * 0.5f, windowSize.y * 0.5f + 100));
	DrawField(g, m_players[1], Vector2f(windowSize.x * 0.5f, windowSize.y * 0.5f - 100));

	// Draw attack moves.
	for (unsigned int i = 0; i < m_attackMoves.size(); ++i)
	{
		auto move = m_attackMoves[i];
		g.DrawArrow(move->m_subject->m_position,
			move->m_target->m_position, Color::RED);
		g.FillCircle(move->m_subject->m_position, 20.0f, Color::BLACK);
		g.DrawCircle(move->m_subject->m_position, 20.0f, Color::WHITE);

		ss.str("");
		ss << (i + 1);
		g.DrawString(m_fontSmall, ss.str(),
			move->m_subject->m_position,
			Color::WHITE, Align::CENTERED);
	}

	if (m_selectedCard != nullptr)
	{
		g.DrawArrow(m_selectedCard->m_position, mousePos, Color::RED);
	}

	// Draw resources
	ss.str("");
	ss << "Supply: " << m_players[0]->m_supply;
	g.DrawString(m_fontSmall, ss.str(), Vector2f(10, windowSize.y - 10 - 24), Color::WHITE, Align::BOTTOM_LEFT);
	ss.str("");
	ss << "Morale: " << m_players[0]->m_morale;
	g.DrawString(m_fontSmall, ss.str(), Vector2f(10, windowSize.y - 10), Color::WHITE, Align::BOTTOM_LEFT);
	
	ss.str("");
	ss << "Supply: " << m_players[1]->m_supply;
	g.DrawString(m_fontSmall, ss.str(), Vector2f(10, 10), Color::WHITE, Align::TOP_LEFT);
	ss.str("");
	ss << "Morale: " << m_players[1]->m_morale;
	g.DrawString(m_fontSmall, ss.str(), Vector2f(10, 10 + 24), Color::WHITE, Align::TOP_LEFT);

	//Tribe tribe;
	//tribe.m_name = "Slug";

	//Card card;
	//card.m_power = 1;
	//card.m_health = 2;
	//card.m_name = "Brewery Servant";
	//card.m_tribe = &tribe;

	//CardInstance cardInstance(&card);
	//cardInstance.m_position = windowSize * 0.5f;

	//DrawCard(g, &cardInstance, cardInstance.m_position);

	//m_players[0].m_hand

	// Draw the ground.
	//g.FillRect(groundRect, m_colorScheme.groundColor);

	// Draw the net.
	//g.FillRect(netRect, m_colorScheme.netColor);

	// Draw the ball.
	//g.FillCircle(ball.GetPosition(), ball.GetRadius(), m_colorScheme.ballColor);
}

