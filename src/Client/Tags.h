#ifndef _CARD_GAME_TAGS_H_
#define _CARD_GAME_TAGS_H_

#include <3rdParty/json/json.h>
#include <iostream>
#include <map>
#include <string>
#include "Enums.h"


struct TagValue
{
	std::string strValue;
	int intValue;

	TagValue() {}
	TagValue(json value);
	TagValue(const char* value) : strValue(value) {}
	TagValue(const std::string& value) : strValue(value) {}
	TagValue(int value) : intValue(value) {}
	TagValue(enums::CardType value) : intValue((int) value) {}
	TagValue(enums::Zone value) : intValue((int) value) {}
	TagValue(enums::Tribe value) : intValue((int) value) {}
	TagValue(enums::Step value) : intValue((int) value) {}
	
	inline operator int() const { return intValue; }
	inline operator std::string() const { return strValue; }
	inline operator enums::Zone() const { return enums::Zone(intValue); }
	inline operator enums::CardType() const { return enums::CardType(intValue); }
	inline operator enums::Tribe() const { return enums::Tribe(intValue); }
	inline operator enums::Step() const { return enums::Step(intValue); }
};


class TagHandle
{
public:
	friend class Tags;
	friend std::ostream& operator <<(std::ostream& out, const TagHandle& tagHandle);

public:
	TagHandle(const TagHandle& copy) 
	{
		m_defaultValue = copy.m_defaultValue;
		m_type = copy.m_type;
		m_tag = copy.m_tag;
		m_value = copy.m_value;
		if (copy.m_value == &copy.m_defaultValue)
			m_value = &m_defaultValue;
		m_tags = copy.m_tags;
	}

	enums::Type Type() const;

	operator TagValue() const { return *m_value; }
	inline operator int() const { return m_value->intValue; }
	inline operator std::string() const { return m_value->strValue; }
	inline operator enums::Zone() const { return enums::Zone(m_value->intValue); }
	inline operator enums::CardType() const { return enums::CardType(m_value->intValue); }
	inline operator enums::Tribe() const { return enums::Tribe(m_value->intValue); }
	inline operator enums::Step() const { return enums::Step(m_value->intValue); }

	inline void operator =(const TagValue& value) { Create(); *m_value = value; }
	inline void Set(const TagValue& value) { Create(); *m_value = value; }
	inline const TagValue& Get() { return *m_value; }
	
	std::string ValueName() const;

private:
	TagHandle(Tags* tags, enums::GameTag tag, TagValue* value);
	void operator =(const TagHandle& copy) {}

	void Create();

	TagValue m_defaultValue;
	TagValue* m_value;
	Tags* m_tags;
	enums::GameTag m_tag;
	enums::Type m_type;
};

std::ostream& operator <<(std::ostream& out, const TagHandle& tagHandle);


class Tags
{
public:
	friend class TagHandle;

public:
	static const Tags EMPTY;

public:
	Tags();
	Tags(json data);
	~Tags();

	TagHandle operator [](enums::GameTag tag);
	const TagHandle operator [](enums::GameTag tag) const;
	const TagHandle Get(enums::GameTag tag) const;
	const TagHandle Get(enums::GameTag tag, const TagValue& default) const;

	void Update(const Tags& tags);

	json ToJSON() const;
	std::string Dump();

private:
	std::map<enums::GameTag, TagValue> m_map;
};


#endif // _CARD_GAME_TAGS_H_