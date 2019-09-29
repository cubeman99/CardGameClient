#include "ClientApp.h"
#include <GameLib/graphics/Graphics.h>
#include <GameLib/util/Timing.h>
#include <math/MathLib.h>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace enums;


ClientApp::ClientApp() :
	m_fontSmall(NULL),
	m_fontScore(NULL),
	m_playerId(-1)
{
}

ClientApp::~ClientApp()
{
	delete m_fontScore;
	m_fontScore = nullptr;
	delete m_fontSmall;
	m_fontSmall = nullptr;
}

bool ClientApp::Connect(const std::string & address, int port)
{
	return m_network.Connect(address, port, this);
}

bool ClientApp::Receive()
{
	json message;
	bool result = m_network.Receive(&message);
	if (!result)
		return result;
	Receive(message);
	return result;
}


bool ClientApp::IsReceiving()
{
	return m_network.IsConnected();
}

void ClientApp::Receive(const json& message)
{
	m_mutex.lock();

	for (auto it = message.begin(); it != message.end(); ++it)
	{
		auto action = *it;
		std::string type = action["Type"];
		json data;

		if (type == "AcceptConnection")
		{
			data = action[type];
			int playerId = data["PlayerID"];
			printf("I joined as player %d\n", playerId);
			m_playerId = playerId;
		}
		else if (type == "FullEntity")
		{
			data = action[type];
			std::string cardId = data["CardID"];
			int entityId = data["EntityID"];
			Tags tags = Tags(data["Tags"]);
			enums::CardType type = tags.Get(GameTag::CARD_TYPE, CardType::INVALID);

			printf("FullEntity entity %d: %s\n", entityId, cardId.c_str());

			if (type != CardType::INVALID)
				m_game.CreateEntity(entityId, type, tags);
			else
				printf("ERROR: Invalid card type for entity %d\n", entityId);
		}
		else if (type == "TagChange")
		{
			data = action[type];
			int entityId = data["EntityID"];
			enums::GameTag tag = data["Tag"];
			std::string value = data["Value"].dump();
			printf("TagChange for %d: %s -> %s\n", entityId,
				enums::ValueName(tag).c_str(), value.c_str());
			Entity* entity = m_game.GetEntity(entityId);
			if (entity != nullptr)
				entity->SetTag(tag, data["Value"]);
		}
		else if (type == "Options")
		{
			json options = action[type];
			json option;
			m_game.ClearOptions();

			for (auto it2 = options.begin(); it2 != options.end(); ++it2)
			{
				option = *it2;
				enums::OptionType optionType = enums::OptionType(option["Type"]);
				json optionArgs = option["MainOption"];
				Option opt(optionType, optionArgs);
				m_game.AddOption(opt);
				printf("Option type %s with args %s\n",
					enums::ValueName(optionType).c_str(), optionArgs.dump().c_str());
			}
		}
		else if (type == "Choices")
		{
			data = action[type];
			m_game.ClearOptions();

			Choice choice(
				enums::ChoiceType(data["ChoiceType"]),
				data["SourceID"],
				data["PlayerID"],
				data["Entities"]);
			m_game.SetChoice(choice);

			Card* source = (Card*) m_game.GetEntity(choice.GetSourceID());
			std::string sourceName = source->GetName();

			printf("Choice type %s from %s with entities %s\n",
				enums::ValueName(choice.GetType()).c_str(),
				sourceName.c_str(),
				data["Entities"].dump().c_str());

		}
	}

	m_mutex.unlock();
	//m_game.PrintState();
}

float ClientApp::GetTimeStamp()
{
	// TODO: fix this.
	return (float) Time::GetTime();
}

void ClientApp::OnInitialize()
{
	// Load resources.
	m_fontScore = Font::LoadFont("assets/AlteHaasGroteskBold.ttf", 24, 32, 128);
	m_fontSmall = Font::LoadFont("assets/AlteHaasGroteskRegular.ttf", 11, 32, 128);

	m_mousedOverCard = nullptr;
	m_selectedCard = nullptr;

	m_game.Create();
}

void ClientApp::OnQuit()
{
	m_network.Disconnect();
	//m_cardManager.DeleteAllCards();

	//delete m_players[0];
	//m_players[0] = nullptr;
	//delete m_players[1];
	//m_players[1] = nullptr;
}

void ClientApp::OnUpdate(float timeDelta)
{
	auto keyboard = GetKeyboard();
	auto mouse = GetMouse();

	// Escape: Quit the m_game.
	if (keyboard->IsKeyPressed(Keys::ESCAPE) ||
		(keyboard->IsKeyPressed(Keys::Q) &&
		keyboard->IsKeyDown(Keys::LCONTROL)))
	{
		Quit();
		return;
	}
	
	m_mutex.lock();

	if (keyboard->IsKeyPressed(Keys::ENTER))
	{
		m_network.Send({
			{"Type", "Done"}
		});	
	}

	Vector2f cardSize(150.0f, 150.0f);
	Vector2f mousePos((float) GetMouse()->GetX(), (float) GetMouse()->GetY());
	Vector2f windowSize((float) GetWindow()->GetWidth(), (float) GetWindow()->GetHeight());
	m_mousedOverCard = nullptr;

	auto cards = m_game.GetHands() + m_game.GetBoard();

	for (auto card : cards)
	{
		if (card->GetType() == CardType::UNIT ||
			card->GetType() == CardType::SPELL)
		{
			Rect2f cardRect = Rect2f(card->GetPosition() - (cardSize * 0.5f), cardSize);
			if (cardRect.Contains(mousePos))
			{
				m_mousedOverCard = card;
			}
		}
	}

	// DEBUG: F1: show moused-over card info
	if (m_mousedOverCard != nullptr &&
		keyboard->IsKeyPressed(Keys::F1))
	{
		std::cout << "Entity " << m_mousedOverCard->GetID() << " (" << m_mousedOverCard->GetCardID() << "):" << std::endl;
		std::cout << "Tags:" << std::endl;
		std::cout << m_mousedOverCard->GetTags().Dump() << std::endl;
		std::cout << "Buffs:" << std::endl;
		for (Card* buff : m_mousedOverCard->GetBuffs())
		{
			std::cout << "Buff " << buff->GetID() << " (" << buff->GetCardID() << "):" << std::endl;
			std::cout << buff->GetTags().Dump() << std::endl;
		}
	}

	if (m_targeting)
	{
		Card* selectedCard = (Card*) m_game.GetEntity(m_targetingOption.GetEntityID());

		if (GetMouse()->IsButtonPressed(MouseButtons::RIGHT))
		{
			m_targeting = false;
		}
		else if (GetMouse()->IsButtonPressed(MouseButtons::LEFT) &&
			m_mousedOverCard != nullptr && m_mousedOverCard != selectedCard)
		{
			// TODO: validate target.

			m_targets.push_back(m_mousedOverCard);

			if (m_targets.size() == m_targetingOption.GetTargets().size())
			{
				// Perform action.
				std::vector<int> targetIDs;
				for (unsigned int i = 0; i < m_targets.size(); ++i)
					targetIDs.push_back(m_targets[i]->GetID());
				std::string actionName = "Play";
				auto optionType = m_targetingOption.GetType();

				if (optionType == OptionType::PLAY)
				{
					m_network.Send({
						{"Type", "Play"},
						{"Play", {
							{"EntityID", selectedCard->GetID()},
							{"Targets", targetIDs},
						}}
					});
				}
				else if (optionType == OptionType::DECLARE)
				{
					if (m_game.GetStep() == Step::DECLARE)
					{
						m_network.Send({
							{"Type", "Attack"},
							{"Attack", {
								{"Attacker", selectedCard->GetID()},
								{"Defender", targetIDs[0]},
							}}
						});
					}
					else if (m_game.GetStep() == Step::RESPONSE)
					{
						m_network.Send({
							{"Type", "Intercept"},
							{"Intercept", {
								{"Interceptor", selectedCard->GetID()},
								{"Attacker", targetIDs[0]},
							}}
						});
					}
				}
				m_targeting = false;
			}
		}
	}
	else if (m_mousedOverCard != nullptr &&
		GetMouse()->IsButtonPressed(MouseButtons::LEFT))
	{
		Option option;
		bool foundOption = false;

		
		if (m_game.IsChoosing())
		{
			if (m_game.GetChoice().ContainsEntity(m_mousedOverCard->GetID()))
			{
					// Play the card with no targets.
					m_network.Send({
						{"Type", "Choose"},
						{"Choose", {
							{"EntityID", m_mousedOverCard->GetID()},
						}}
					});
			}
			else
			{
				std::cout << "Not a valid choice" << std::endl;
			}
		}
		else
		{
			// Find the option associated with this card.
			for (Option possibleOption : m_game.GetOptions())
			{
				if (possibleOption.GetEntityID() == m_mousedOverCard->GetID())
				{
					foundOption = true;
					option = possibleOption;
					break;
				}
			}

			if (foundOption)
			{
				if (option.GetTargets().empty())
				{
					// Play the card with no targets.
					m_network.Send({
						{"Type", "Play"},
						{"Play", {
							{"EntityID", m_mousedOverCard->GetID()},
							{"Targets", std::vector<int>()}
						}}
					});
				}
				else
				{
					std::cout << "Beggining targeting for " << option.GetTargets().size() << " targets" << std::endl;
					// Begin selecting play targets.
					m_targeting = true;
					m_targetingOption = option;
					m_targets.clear();
				}
			}
			else
			{
				std::cout << "No valid option" << std::endl;
			}
		}
	}

	m_mutex.unlock();
}

void ClientApp::DrawTextInBox(Graphics& g, Font* font, std::string text, const Rect2f& box, const Color& color)
{
	using namespace std;
	std::vector<std::string> tokens;
    std::istringstream iss(text);
	std::copy(std::istream_iterator<std::string>(iss),
		std::istream_iterator<std::string>(),
		std::back_inserter(tokens));

	Vector2f cursor = box.GetTopLeft();
	unsigned int tokenIndex = 0;
	while (tokenIndex < tokens.size())
	{
		std::stringstream ss;
		std::string str;

		unsigned int i;
		for (i = tokenIndex; i < tokens.size(); ++i)
		{
			ss << tokens[i];
			ss << " ";
			Rect2f tokenBox = g.MeasureString(font, ss.str());
			if (tokenBox.GetRight() > box.GetWidth())
			{
				i -= 1;
				break;
			}
			str = ss.str();
		}
		tokenIndex = i + 1;
		
		g.DrawString(font, str, cursor, color);
		cursor.y += 20;
	}
}


Vector2f Round(const Vector2f& v)
{
	return Vector2f(
		Math::Floor(v.x + 0.5f),
		Math::Floor(v.y + 0.5f));
}

void ClientApp::DrawCard(Graphics& g, Card* card, const Vector2f& position)
{
	float ratio = 1.0f;
	float width = 150;
	Vector2f cardSize(width, width * ratio);
	std::stringstream str;
	bool playable = false;

	card->SetPosition(position); // DEBUG:

	for (auto option : m_game.GetOptions())
	{
		if (option.GetEntityID() == card->GetID())
		{
			playable = true;
		}
	}

	// Draw card outline.
	Color outlineColor = Color::WHITE;
	if (playable)
		outlineColor = Color::GREEN;
	if (card == m_mousedOverCard)
		outlineColor = Color::YELLOW;
	if (m_game.IsChoosing() &&
		m_game.GetChoice().ContainsEntity(card->GetID()))
	{
		outlineColor = Color::GREEN;
	}

	// Check if this card is a valid target when targeting.
	if (m_targeting)
	{
		outlineColor = Color::WHITE;
		
		if (card->GetID() == m_targetingOption.GetEntityID())
			outlineColor = Color::GREEN;

		auto validTargets = m_targetingOption.GetTargets()[m_targets.size()];
		if (std::find(validTargets.begin(), validTargets.end(),
			card->GetID()) != validTargets.end())
		{
			outlineColor = Color::MAGENTA;
		}
	}

	g.DrawRect(position - (cardSize * 0.5f), cardSize, outlineColor);

	// Draw name.
	g.DrawString(m_fontSmall, card->GetName(),
		Round(position - Vector2f(0.0f, cardSize.y) * 0.45f),
		Color::YELLOW, Align::TOP_CENTER);

	// Draw buff names.
	int buffIndex = 0;
	for (auto buff : card->GetBuffs())
	{
		g.DrawString(m_fontSmall, buff->GetCardID(),
			Round(position + Vector2f(-cardSize.x * 0.5f, cardSize.y * 0.5f + 10 + buffIndex * 16)),
			Color::GREEN, Align::TOP_LEFT);
		buffIndex += 1;
	}

	// Draw text.
	//g.DrawString(m_fontSmall, card->GetText(),
		//position, Color::WHITE, Align::CENTERED);

	Rect2f box = Rect2f(
		position - Vector2f(cardSize.x * 0.45f, cardSize.y * 0.3f),
		cardSize * Vector2f(0.9f, 0.8f));
	DrawTextInBox(g, m_fontSmall, card->GetText(), box, Color::WHITE);

	// Draw tribe.
	//if (card->GetTribe() != nullptr)
	//{
	//	g.DrawString(m_fontSmall, card->GetTribe()->m_name,
	//		position - Vector2f(0.0f, cardSize.y * 0.5f - 18),
	//		Color::WHITE, Align::TOP_CENTER);
	//}

	// Draw ID.
	g.DrawString(m_fontSmall, std::to_string(card->GetID()),
		position + Vector2f(0.0f, cardSize.y * 0.5f - 18),
		Color::GRAY, Align::TOP_CENTER);

	// Draw ID.
	//if (card->IsFlipped())
	//{
	//	g.DrawString(m_fontSmall, "Flipped",
	//		position, Color::YELLOW, Align::CENTERED);
	//}
	
	if (card->GetType() != CardType::SPELL)
	{
		float radius = 20.0f;
		Vector2f healthPos = position + Vector2f(-cardSize.x, cardSize.y) * 0.5f + Vector2f(radius, -radius) * 0.7f;
		Vector2f powerPos  = position + Vector2f(cardSize.x, cardSize.y) * 0.5f + Vector2f(-radius, -radius) * 0.7f;
	
		// Draw power.
		str.str("");
		str << card->GetPower();
		Color powerColor = Color::WHITE;
		if (card->GetTagBuffAmount(GameTag::POWER) > 0)
			powerColor = Color::GREEN;
		g.FillCircle(healthPos, radius, Color::BLACK);
		g.DrawCircle(healthPos, radius, Color::WHITE);
		g.DrawString(m_fontScore, str.str(),
			healthPos, powerColor, Align::CENTERED);

		// Draw health.
		str.str("");
		str << card->GetHealth();
		Color healthColor = Color::WHITE;
		if (card->GetDamage() > 0)
			healthColor = Color::RED;
		else if (card->GetTagBuffAmount(GameTag::HEALTH) > 0)
			healthColor = Color::GREEN;
		g.FillCircle(powerPos, radius, Color::BLACK);
		g.DrawCircle(powerPos, radius, Color::WHITE);
		g.DrawString(m_fontScore, str.str(),
			powerPos, healthColor, Align::CENTERED);
	}
}

void ClientApp::DrawField(Graphics& g, Player* player, const Vector2f& center)
{
	CardList field = player->GetField();
	float numUnitsInPlay = (float) field.size();
	Vector2f pos;

	for (int i = 0; i < field.size(); ++i)
	{
		Card* card = field[i];

		float percent = ((float) i - ((numUnitsInPlay - 1) * 0.5f));
		pos.x = center.x + percent * 200;
		pos.y = center.y;

		DrawCard(g, card, pos);
	}
}

void ClientApp::DrawHand(Graphics& g, Player* player, const Vector2f& center)
{
	CardList hand = player->GetHand();
	float numUnitsInPlay = (float) hand.size();
	Vector2f pos;

	for (int i = 0; i < hand.size(); ++i)
	{
		Card* card = hand[i];

		float percent = ((float) i - ((numUnitsInPlay - 1) * 0.5f));
		pos.x = center.x + percent * 200;
		pos.y = center.y;

		DrawCard(g, card, pos);
	}
}
void ClientApp::OnRender()
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
	//	windowSize.x * 0.5f, windowSize.y * 0.5f,
	//	Color::WHITE, Align::CENTER);
	
	
	g.DrawString(m_fontScore, std::to_string(this->GetCurrentFPS()),
		windowSize.x * 0.5f, windowSize.y * 0.5f,
		Color::WHITE, Align::CENTER);

	m_mutex.lock();
	
	if (m_game.GetStepPlayer() != nullptr)
	{
		ss << "Turn " << m_game.GetTurnNumber() << ": " << m_game.GetStepPlayer()->GetName() << "'s " << ValueName(m_game.GetStep()) << " Step";
		g.DrawString(m_fontScore, ss.str(),
			windowSize.x * 0.5f, 10,
			Color::GREEN, Align::TOP_CENTER);
	}

	Vector2f pos(10, 10);
	for (auto option : m_game.GetOptions())
	{
		g.DrawString(m_fontSmall, enums::ValueName(option.GetType()),
			pos, Color::GREEN, Align::TOP_LEFT);
		pos.y += 24;
	}
	auto players = m_game.GetPlayers();

	Player* player = m_game.GetPlayer(m_playerId);
	Player* opponent = m_game.GetOpponent(m_playerId);

	if (players.size() >= 2)
	{
		// Draw fields
		DrawField(g, player, Vector2f(windowSize.x * 0.5f, windowSize.y * 0.5f + 100));
		DrawField(g, opponent, Vector2f(windowSize.x * 0.5f, windowSize.y * 0.5f - 100));
		
		// Draw hands
		DrawHand(g, player, Vector2f(windowSize.x * 0.5f, windowSize.y - 100));
		DrawHand(g, opponent, Vector2f(windowSize.x * 0.5f, 100));
	}



	// Draw attack moves.
	for (auto unit : m_game.GetBoard())
	{
		Card* attackTarget = (Card*) m_game.GetEntity(
			unit->GetTag(GameTag::DECLARED_ATTACK, -1));

		if (attackTarget  != nullptr)
		{
			g.DrawArrow(unit->GetPosition(),
				attackTarget->GetPosition(), Color::RED);
			//g.FillCircle(attackTarget->GetPosition(), 20.0f, Color::BLACK);
			//g.DrawCircle(attackTarget->GetPosition(), 20.0f, Color::WHITE);
		}

		//ss.str("");
		//ss << (i + 1);
		//g.DrawString(m_fontSmall, ss.str(),
		//	move->m_subject->m_position,
		//	Color::WHITE, Align::CENTERED);
	}

	if (m_targeting)
	{
		Card* card = (Card*) m_game.GetEntity(m_targetingOption.GetEntityID());

		g.DrawArrow(card->GetPosition(), mousePos, Color::MAGENTA);
	}
//
//	if (m_selectedCard != nullptr)
//	{
//		g.DrawArrow(m_selectedCard->m_position, mousePos, Color::RED);
//	}
//
//	// Draw resources
//	ss.str("");
//	ss << "Supply: " << m_players[0]->m_supply;
//	g.DrawString(m_fontSmall, ss.str(), Vector2f(10, windowSize.y - 10 - 24), Color::WHITE, Align::BOTTOM_LEFT);
//	ss.str("");
//	ss << "Morale: " << m_players[0]->m_morale;
//	g.DrawString(m_fontSmall, ss.str(), Vector2f(10, windowSize.y - 10), Color::WHITE, Align::BOTTOM_LEFT);
//	
//	ss.str("");
//	ss << "Supply: " << m_players[1]->m_supply;
//	g.DrawString(m_fontSmall, ss.str(), Vector2f(10, 10), Color::WHITE, Align::TOP_LEFT);
//	ss.str("");
//	ss << "Morale: " << m_players[1]->m_morale;
//	g.DrawString(m_fontSmall, ss.str(), Vector2f(10, 10 + 24), Color::WHITE, Align::TOP_LEFT);

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
	m_mutex.unlock();
}

