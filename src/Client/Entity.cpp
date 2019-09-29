#include "Entity.h"

using namespace enums;



Entity::Entity(int id) :
	m_id(id),
	m_game(nullptr)
{
}

Entity::Entity(int id, const Tags& tags) :
	m_id(id),
	m_tags(tags)
{
}

Entity::~Entity()
{
}

Player* Entity::GetController() const
{
	return (Player*) GetTagEntity(GameTag::CONTROLLER);
}

Entity* Entity::GetTagEntity(enums::GameTag tag) const
{
	return m_game->GetEntity(m_tags.Get(tag, -1));

}

CardList Entity::GetBuffs()
{
	CardList buffs;
	for (Entity* entity : m_game->GetEntities())
	{
		if (entity->GetType() == CardType::EFFECT &&
			entity->GetZone() == GetZone() &&
			(int) entity->GetTag(GameTag::OWNER, -1) == m_id)
		{
			buffs.push_back((Card*) entity);
		}
	}
	return buffs;
}

int Entity::GetTagBuffAmount(enums::GameTag tag)
{
	int amount = 0;
	for (Card* buff : GetBuffs())
		amount += (int) buff->GetTag(tag, 0);
	return amount;
}


Option::Option()
{
}

Option::Option(enums::OptionType type, const json& args) :
	m_type(type),
	m_entityId(-1)
{
	if (!args.is_null())
	{
		if (args.find("ID") != args.end())
			m_entityId = args["ID"];
		if (args.find("Targets") != args.end())
		{
			unsigned int count = args["Targets"].size();
			for (unsigned int i = 0; i < count; ++i)
			{
				std::vector<int> validTargets = args["Targets"][i];
				m_targets.push_back(validTargets);
			}
		}
	}
}


Choice::Choice()
{
}

Choice::Choice(enums::ChoiceType type, int sourceId, int playerId,
		const std::vector<int>& entities) :
	m_type(type),
	m_sourceId(sourceId),
	m_playerId(playerId),
	m_entities(entities)
{
}

bool Choice::ContainsEntity(int entityId) const
{
	return std::find(m_entities.begin(), m_entities.end(),
		entityId) != m_entities.end();
}


Game::Game() :
	Entity(1),
	m_choosing(false)
{	
	m_game = this;
}

Game::~Game()
{
	ClearEntities();
}

void Game::Create()
{
	m_cardDatabase.Initialize();
	ClearEntities();
	m_entities.push_back(this);
}

Entity* Game::CreateEntity(int id, enums::CardType type, const Tags& tags)
{
	Entity* entity = nullptr;
	std::string cardId = tags.Get(enums::GameTag::CARD_ID, "");
	
	if (type == enums::CardType::PLAYER)
	{
		Player* player = new Player(id, tags);
		m_players.push_back(player);
		entity = player;
		std::cout << "PLAYER: " << m_players.size() << " players" << std::endl;
	}
	else if (type == enums::CardType::SPELL ||
		type == enums::CardType::UNIT ||
		type == enums::CardType::EFFECT)
	{
		const CardData* cardData = m_cardDatabase[cardId];
		if (cardData != nullptr)
		{
			entity = new Card(id, type, cardData->GetTags());
			entity->m_tags.Update(tags);
		}
		else
		{
			entity = new Card(id, type, tags);
		}
	}
	else if (type == enums::CardType::GAME)
	{
		this->m_id = id;
		this->m_tags.Update(tags);
		return this;
	}

	entity->m_game = this;
	m_entities.push_back(entity);
	return entity;
}

void Game::ClearEntities()
{
	Entity* entity;
	for (unsigned int i = 0; i < m_entities.size(); ++i)
	{
		entity = m_entities[i];
		if (entity != this)
			delete entity;
	}

	m_entities.clear();
	m_players.clear();
}

void Game::AddOption(const Option& option)
{
	m_choosing = false;
	m_options.push_back(option);
}

void Game::SetChoice(const Choice& choice)
{
	m_options.clear();
	m_choosing = true;
	m_choice = choice;
}

void Game::ClearOptions()
{
	m_options.clear();
	m_choosing = false;
}

const Entity* Game::GetEntity(int id) const
{
	for (unsigned int i = 0; i < m_entities.size(); ++i)
	{
		const Entity* entity = m_entities[i];
		if (entity->GetID() == id)
			return entity;
	}
	return nullptr;
}

Entity* Game::GetEntity(int id)
{
	for (unsigned int i = 0; i < m_entities.size(); ++i)
	{
		Entity* entity = m_entities[i];
		if (entity->GetID() == id)
			return entity;
	}
	return nullptr;
}

Player* Game::GetPlayer(int playerEntityId)
{
	for (Player* player : m_players)
	{
		if (player->GetID() == playerEntityId)
			return player;
	}
	return nullptr;
}

Player* Game::GetOpponent(int playerEntityId)
{
	for (Player* player : m_players)
	{
		if (player->GetID() != playerEntityId)
			return player;
	}
	return nullptr;
}

void Game::PrintState()
{
	std::cout << "GAME STATE: " << m_players.size() << " players" << std::endl;

	//for (auto player : GetPlayers())
	//{
	//	std::cout << "========================================================" << std::endl;
	//	std::cout << "Field of " << player->GetName() << std::endl;

	//	for (auto entity : player->Field())
	//	{
	//		std::cout << "Entity " << entity->GetID() << std::endl;
	//		std::cout << entity->GetTags().Dump();
	//		std::cout << std::endl;
	//	}
	//}

	std::cout << "========================================================" << std::endl;
	//for (auto entity : m_entities)
	for (unsigned int i = 0; i < m_entities.size(); ++i)
	{
		Entity* entity = m_entities[i];
		std::cout << "Entity " << entity->GetID() << std::endl;
		std::cout << entity->GetTags().Dump();
		std::cout << std::endl;
	}

	//for (unsigned int i = 0; i < m_entities.size(); ++i)
	//{
	//	Entity* entity = m_entities[i];
	//	std::cout << std::endl;
	//	std::cout << "Entity " << entity->GetID() << std::endl;
	//	std::cout << entity->GetTags().Dump();
	//}
}

CardList Game::GetHands() const
{
	CardList result;
	for (Entity* entity : m_entities)
	{
		if (entity->GetZone() == Zone::HAND &&
			(entity->GetType() == CardType::UNIT ||
			entity->GetType() == CardType::SPELL))
			result.push_back((Card*) entity);
	}
	return result;
}

CardList Game::GetBoard() const
{
	CardList result;
	for (Entity* entity : m_entities)
	{
		if (entity->GetZone() == Zone::PLAY &&
			entity->GetType() == CardType::UNIT)
			result.push_back((Card*) entity);
	}
	return result;
}



Player::Player(int id, const Tags& tags) :
	Entity(id, tags)
{
}

CardList Player::GetHand() const
{
	CardList result;
	for (Card* entity : GetGame().GetHands())
	{
		if (entity->GetController() == this)
			result.push_back(entity);
	}
	return result;
}

CardList Player::GetField() const
{
	CardList result;
	for (Card* entity : GetGame().GetBoard())
	{
		if (entity->GetController() == this)
			result.push_back(entity);
	}
	return result;
}


Card::Card(int id, enums::CardType type, const Tags& tags) :
	Entity(id, tags)
{
	std::string cardId = GetCardID();
	// TODO: Load tags from card database.
}

Card* Card::GetOwner() const
{
	return (Card*) GetTagEntity(GameTag::OWNER);
}

