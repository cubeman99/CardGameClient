#ifndef _CARD_DATABASE_H_
#define _CARD_DATABASE_H_

#include "Tags.h"


class CardData
{
public:
	CardData(const std::string& cardId, json data);

	const Tags& GetTags() const { return m_tags; }
	const std::string& GetID() const { return m_cardId; }

private:
	Tags m_tags;
	std::string m_cardId;
};

class CardDatabase
{
public:
	CardDatabase();
	~CardDatabase();

	bool Initialize();

	const CardData* operator [](std::string cardId) const;
	const CardData* GetCard(std::string cardId) const;
	inline bool IsInitialized() const { return m_isInitialized; }

private:
	std::map<std::string, CardData*> m_cards;
	bool m_isInitialized;
};


#endif _CARD_DATABASE_H_