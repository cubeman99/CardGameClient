#include "CardDatabase.h"
#include <fstream>

using namespace enums;


CardData::CardData(const std::string& cardId, json data) :
	m_cardId(cardId)
{
	for (auto it = data.begin(); it != data.end(); ++it)
	{
		// Parse the tag name.
		std::string tagName = it.key();
		GameTag tag = enums::ParseValue<GameTag>(tagName);
		Type tagType = GetTagType(tag);

		TagValue value;

		// Parse the value
		if (tagType == enums::Type::ENUM)
		{
			auto typeInfo = GetTagTypeInfo(tag);
			value.intValue = typeInfo->NameToInt(it.value());
		}
		
		if (it.value().is_string())
		{
			std::string s = it.value();
			value.strValue = s;
		}
		else
			value.intValue = it.value();

		m_tags[tag] = value;
	}

	m_tags[GameTag::CARD_ID] = cardId;
}


CardDatabase::CardDatabase() :
	m_isInitialized(false)
{
}

CardDatabase::~CardDatabase()
{
	for (auto it = m_cards.begin(); it != m_cards.end(); ++it)
		delete it->second;
	m_cards.clear();
}

bool CardDatabase::Initialize()
{
	if (m_isInitialized)
		return true;

	const std::string path = "C:/Workspace/python/cardgame/card_details.json";

	std::ifstream file(path);
	if (!file.is_open())
	{
		printf("Error opening card data json file\n");
		return false;
	}

	json data;
	file >> data;
	file.close();

	// Load all cards from the json data.
	for (auto item = data.begin(); item != data.end(); ++item)
	{
		CardData* cardData = new CardData(item.key(), item.value());
		m_cards[item.key()] = cardData;
	}

	return true;
}

const CardData* CardDatabase::GetCard(std::string cardId) const
{
	auto it = m_cards.find(cardId);
	if (it == m_cards.end())
		return nullptr;
	return it->second;
}

const CardData* CardDatabase::operator [](std::string cardId) const
{
	return GetCard(cardId);
}

