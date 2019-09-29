#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <vector>
#include "Tags.h"
#include "Utilities.h"
#include "CardDatabase.h"
#include <GameLib/math/MathLib.h>
#include <GameLib/math/Vector2f.h>

class Game;
class Player;


class Entity
{
public:
	friend class Game;

public:
	Entity(int id);
	Entity(int id, const Tags& tags);
	virtual ~Entity();

	// Getters
	inline int GetID() const { return m_id; }
	inline Game& GetGame() { return *m_game; }
	inline const Game& GetGame() const { return *m_game; }

	// Tag getters
	inline enums::CardType GetType() const { return m_tags.Get(enums::GameTag::CARD_TYPE, enums::CardType::INVALID); }
	inline enums::Zone GetZone() const { return m_tags.Get(enums::GameTag::ZONE, enums::Zone::INVALID); }
	inline Player* GetController() const;
	
	// Return all effects applied to this entity.
	CardList GetBuffs();

	// Return the amount by which a tag is adjusted by the entity's buffs. This
	// can be both positive (buff) or negative (debuff). This only applies to
	// integer tags.
	int GetTagBuffAmount(enums::GameTag tag);

	// Tags
	inline Tags& GetTags() { return m_tags; }
	inline const Tags& GetTags() const { return m_tags; }
	inline TagHandle GetTag(enums::GameTag tag) { return m_tags[tag]; }
	inline const TagHandle GetTag(enums::GameTag tag) const { return m_tags[tag]; }
	inline TagHandle GetTag(enums::GameTag tag, const TagValue& defaultValue) { return m_tags.Get(tag, defaultValue); }
	inline const TagHandle GetTag(enums::GameTag tag, const TagValue& defaultValue) const { return m_tags.Get(tag, defaultValue); }
	inline void SetTag(enums::GameTag tag, TagValue value) { m_tags[tag] = value; }

protected:
	inline Entity* GetTagEntity(enums::GameTag tag) const;


	Tags	m_tags;
	int		m_id;
	Game*	m_game;
};


class Option
{
public:
	Option();
	Option(enums::OptionType type, const json& args);

	inline enums::OptionType GetType() const { return m_type; }
	inline int GetEntityID() const { return m_entityId; }
	inline const std::vector<std::vector<int>>& GetTargets() const { return m_targets; }

private:
	enums::OptionType m_type;
	int m_entityId;
	std::vector<std::vector<int>> m_targets;
};


class Choice
{
public:
	Choice();
	Choice(enums::ChoiceType type, int sourceId, int playerId, const std::vector<int>& entities);

	inline enums::ChoiceType GetType() const { return m_type; }
	inline int GetSourceID() const { return m_sourceId; }
	inline int GetPlayerID() const { return m_playerId; }
	inline const std::vector<int>& GetEntities() const { return m_entities; }

	bool ContainsEntity(int entityId) const;

private:
	enums::ChoiceType m_type;
	int m_sourceId;
	int m_playerId;
	std::vector<int> m_entities;
};


class Game : public Entity
{
public:
	Game();
	~Game() override;

	void Create();
	Entity* CreateEntity(int id, enums::CardType type, const Tags& tags);
	void ClearEntities();
	void AddOption(const Option& option);
	void SetChoice(const Choice& choice);
	void ClearOptions();

	inline enums::Step GetStep() const { return m_tags.Get(enums::GameTag::STEP, enums::Step::INVALID); }
	inline Player* GetStepPlayer() const { return (Player*) GetTagEntity(enums::GameTag::TURN_PLAYER); }
	inline Player* GetTurnPlayer() const { return (Player*) GetTagEntity(enums::GameTag::STEP_PLAYER); }
	inline int GetTurnNumber() const { return m_tags.Get(enums::GameTag::TURN_NUMBER, 0); }
	
	Entity* GetEntity(int id);
	const Entity* GetEntity(int id) const;

	inline bool IsChoosing() const { return m_choosing; }
	inline const Choice& GetChoice() const { return m_choice; }

	Player* GetPlayer(int playerEntityId);
	Player* GetOpponent(int playerEntityId);


	std::vector<Entity*>& GetEntities() { return m_entities; }
	const std::vector<Entity*>& GetEntities() const { return m_entities; }
	std::vector<Player*>& GetPlayers() { return m_players; }
	const std::vector<Player*>& GetPlayers() const { return m_players; }
	std::vector<Option>& GetOptions() { return m_options; }
	const std::vector<Option>& GetOptions() const { return m_options; }
	const CardDatabase& GetCardDatabase() const { return m_cardDatabase; }

	CardList GetHands() const;
	CardList GetBoard() const;

	void PrintState();

private:
	std::vector<Entity*> m_entities;
	std::vector<Player*> m_players;
	std::vector<Option> m_options;
	Choice m_choice;
	bool m_choosing;
	CardDatabase m_cardDatabase;
};


class Player : public Entity
{
public:
	Player(int id, const Tags& tags);

	inline std::string GetName() const { return m_tags.Get(enums::GameTag::NAME, "UNKNOWN"); }
	inline int GetMorale() const { return m_tags.Get(enums::GameTag::MORALE, 0); }
	inline int GetSupply() const { return m_tags.Get(enums::GameTag::SUPPLY, 0); }
	inline int GetTerritory() const { return m_tags.Get(enums::GameTag::TERRITORY, 0); }
	
	CardList GetHand() const;
	CardList GetField() const;

private:

};


class Card : public Entity
{
public:
	Card(int id, enums::CardType type, const Tags& tags);

	inline std::string GetName() const { return m_tags.Get(enums::GameTag::NAME, "UNKNOWN"); }
	inline std::string GetText() const { return m_tags.Get(enums::GameTag::TEXT, ""); }
	inline std::string GetCardID() const { return m_tags.Get(enums::GameTag::CARD_ID, "UNKNOWN"); }
	inline int GetPower() const { return m_tags.Get(enums::GameTag::POWER, 0); }
	inline int GetMaxHealth() const { return m_tags.Get(enums::GameTag::HEALTH, 0); }
	inline int GetDamage() const { return m_tags.Get(enums::GameTag::DAMAGE, 0); }
	inline int GetHealth() const { return GetMaxHealth() - GetDamage(); }
	inline int GetMorale() const { return m_tags.Get(enums::GameTag::MORALE, 0); }
	inline int GetSupply() const { return m_tags.Get(enums::GameTag::SUPPLY, 0); }
	inline enums::Tribe GetTribe() const { m_tags.Get(enums::GameTag::TRIBE, enums::Tribe::INVALID); }

	Card* GetOwner() const;

	inline const Vector2f& GetPosition() const { return m_position; }
	inline void SetPosition(const Vector2f& position) { m_position = position; }

private:
	Vector2f m_position;
};


#endif // _ENTITY_H_