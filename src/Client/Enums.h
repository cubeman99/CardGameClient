#ifndef _ENUMS_H_
#define _ENUMS_H_

#include <string>
#include <map>


namespace enums {


enum class BlockType
{
	ATTACK  = 1,
	CHOICE  = 2,
	POWER   = 3,
	TRIGGER = 4,
	DEATHS  = 5,
	PLAY    = 6,
};

enum class CardType
{
	INVALID = 0,
	GAME    = 1,
	PLAYER  = 2,
	UNIT    = 3,
	SPELL   = 4,
	EFFECT  = 5,
	TOKEN   = 6,
};

enum class ChoiceType
{
	INVALID = 0,
	GENERAL = 1,
	TARGET  = 2,
};

enum class GameTag
{
	INVALID            = -1,
	POWER              = 1,
	HEALTH             = 2,
	TRIBE              = 3,
	CARD_TYPE          = 4,
	REQUIREMENT        = 5,
	CONTROLLER         = 6,
	RESOURCE_TYPE      = 7,
	MORALE             = 8,
	SUPPLY             = 9,
	BATTLE             = 10,
	NAME               = 11,
	TEXT               = 12,
	TERRITORY          = 13,
	MAX_HAND_SIZE      = 14,
	STEP               = 15,
	NEXT_STEP          = 16,
	CARD_ID            = 17,
	ENTITY_ID          = 18,
	ZONE               = 19,
	DAMAGE             = 20,
	OWNER              = 21,
	DECLARED_ATTACK    = 22,
	DECLARED_INTERCEPT = 23,
	TURN_NUMBER        = 24,
	TURN_PLAYER        = 25,
	STEP_PLAYER        = 26,
	MUDDLE             = 100,
	AFTERMATH          = 101,
	STING              = 102,
	CORRUPT            = 103,
	INSPIRE            = 104,
	EMERGE             = 105,
	SPY                = 106,
	INFORM             = 107,
	CONDUIT            = 108,
	TOXIC              = 109,
	WISDOM             = 110,
	RENEW              = 111,
	FURY               = 112,
	SWARM              = 113,
	HEROIC             = 114,
};

enum class OptionType
{
	INVALID = 0,
	DONE    = 1,
	DECLARE = 2,
	FLIP    = 3,
	PLAY    = 4,
	CHOOSE  = 5,
};

enum class Requirement
{
	INVALID           = -1,
	REQ_UNIT_TARGET   = 0,
	REQ_ALLIED_TARGET = 1,
	REQ_ENEMY_TARGET  = 2,
	REQ_              = 3,
};

enum class ResourceType
{
	INVALID = 0,
	MORALE  = 1,
	SUPPLY  = 2,
};

enum class Step
{
	INVALID  = 0,
	UNFLIP   = 1,
	RESOURCE = 2,
	DECLARE  = 3,
	RESPONSE = 4,
	COMBAT   = 5,
	PLAY     = 6,
};

enum class Tribe
{
	INVALID  = 0,
	SLUG     = 1,
	OCTOPI   = 2,
	MOLE     = 3,
	DRAKE    = 4,
	EEL      = 5,
	AARD     = 6,
	PHEASANT = 7,
};

enum class Type
{
	UNKNOWN           = 0,
	BOOL              = 1,
	NUMBER            = 2,
	COUNTER           = 3,
	ENTITY            = 4,
	PLAYER            = 5,
	TEAM              = 6,
	ENTITY_DEFINITION = 7,
	STRING            = 8,
	ENUM              = 9,
	LOCSTRING         = -2,
};

enum class Zone
{
	INVALID           = 0,
	PLAY              = 1,
	DECK              = 2,
	HAND              = 3,
	DISCARD           = 4,
	SET_ASIDE         = 5,
	REMOVED_FROM_GAME = 6,
};


template <typename T_Enum>
class EnumMap
{
public:
	static const std::string ENUM_NAME;
	static const std::map<T_Enum, std::string> VALUE_TO_STRING;
	static const std::map<std::string, T_Enum> STRING_TO_VALUE;
	static const std::map<std::string, int> STRING_TO_INT;
};

template <typename T_Enum>
const std::string EnumMap<T_Enum>::ENUM_NAME = "UNKNOWN";
template <typename T_Enum>
const std::map<T_Enum, std::string> EnumMap<T_Enum>::VALUE_TO_STRING = {};
template <typename T_Enum>
const std::map<std::string, T_Enum> EnumMap<T_Enum>::STRING_TO_VALUE = {};
template <typename T_Enum>
const std::map<std::string, int> EnumMap<T_Enum>::STRING_TO_INT = {};


// Convert an enum value to a string name.
template <typename T_Enum>
T_Enum ParseValue(std::string name)
{
	// Convert name to uppercase first
	std::transform(name.begin(), name.end(), name.begin(), ::toupper);
	return EnumMap<T_Enum>::STRING_TO_VALUE.at(name);
}

// Convert an string name to an enum value.
template <typename T_Enum>
std::string ValueName(T_Enum value)
{
	return EnumMap<T_Enum>::VALUE_TO_STRING.at(value);
}

// Return the string representation of an enum's name.
template <typename T_Enum>
std::string EnumName();

// Return the type of a tag.
Type GetTagType(GameTag tag);

std::string GetTagEnumValueName(GameTag tag, int value);



template <> class EnumMap<BlockType>
{
public:
	static const std::string ENUM_NAME;
	static const std::map<BlockType, std::string> VALUE_TO_STRING;
	static const std::map<std::string, BlockType> STRING_TO_VALUE;
	static const std::map<std::string, int> STRING_TO_INT;
};

template <> class EnumMap<CardType>
{
public:
	static const std::string ENUM_NAME;
	static const std::map<CardType, std::string> VALUE_TO_STRING;
	static const std::map<std::string, CardType> STRING_TO_VALUE;
	static const std::map<std::string, int> STRING_TO_INT;
};

template <> class EnumMap<ChoiceType>
{
public:
	static const std::string ENUM_NAME;
	static const std::map<ChoiceType, std::string> VALUE_TO_STRING;
	static const std::map<std::string, ChoiceType> STRING_TO_VALUE;
	static const std::map<std::string, int> STRING_TO_INT;
};

template <> class EnumMap<GameTag>
{
public:
	static const std::string ENUM_NAME;
	static const std::map<GameTag, std::string> VALUE_TO_STRING;
	static const std::map<std::string, GameTag> STRING_TO_VALUE;
	static const std::map<std::string, int> STRING_TO_INT;
};

template <> class EnumMap<OptionType>
{
public:
	static const std::string ENUM_NAME;
	static const std::map<OptionType, std::string> VALUE_TO_STRING;
	static const std::map<std::string, OptionType> STRING_TO_VALUE;
	static const std::map<std::string, int> STRING_TO_INT;
};

template <> class EnumMap<Requirement>
{
public:
	static const std::string ENUM_NAME;
	static const std::map<Requirement, std::string> VALUE_TO_STRING;
	static const std::map<std::string, Requirement> STRING_TO_VALUE;
	static const std::map<std::string, int> STRING_TO_INT;
};

template <> class EnumMap<ResourceType>
{
public:
	static const std::string ENUM_NAME;
	static const std::map<ResourceType, std::string> VALUE_TO_STRING;
	static const std::map<std::string, ResourceType> STRING_TO_VALUE;
	static const std::map<std::string, int> STRING_TO_INT;
};

template <> class EnumMap<Step>
{
public:
	static const std::string ENUM_NAME;
	static const std::map<Step, std::string> VALUE_TO_STRING;
	static const std::map<std::string, Step> STRING_TO_VALUE;
	static const std::map<std::string, int> STRING_TO_INT;
};

template <> class EnumMap<Tribe>
{
public:
	static const std::string ENUM_NAME;
	static const std::map<Tribe, std::string> VALUE_TO_STRING;
	static const std::map<std::string, Tribe> STRING_TO_VALUE;
	static const std::map<std::string, int> STRING_TO_INT;
};

template <> class EnumMap<Type>
{
public:
	static const std::string ENUM_NAME;
	static const std::map<Type, std::string> VALUE_TO_STRING;
	static const std::map<std::string, Type> STRING_TO_VALUE;
	static const std::map<std::string, int> STRING_TO_INT;
};

template <> class EnumMap<Zone>
{
public:
	static const std::string ENUM_NAME;
	static const std::map<Zone, std::string> VALUE_TO_STRING;
	static const std::map<std::string, Zone> STRING_TO_VALUE;
	static const std::map<std::string, int> STRING_TO_INT;
};


class TypeInfoBase
{
public:
	virtual int NameToInt(std::string name) const = 0;
	virtual std::string IntToName(int value) const = 0;
	virtual const std::string& GetEnumName() const = 0;
};

template <typename T_Enum>
class TypeInfo : public TypeInfoBase
{
public:
	TypeInfo(int x):
	{}
	TypeInfo(const std::string& name,
			std::map<std::string, int> nameToValue,
			std::map<int, std::string> valueToName) :
		m_enumName(name),
		m_nameToValue(nameToValue),
		m_valueToName(valueToName)
	{
	}

	const std::string& GetEnumName() const override
	{
		return m_enumName;
	}

	int NameToInt(std::string name) const override
	{
		std::transform(name.begin(), name.end(), name.begin(), ::toupper);
		return m_nameToValue.at(name);
	}

	std::string IntToName(int value) const override
	{
		return m_valueToName.at(value);
	}

	T_Enum NameToValue(std::string name) const
	{
		return (T_Enum) NameToInt(name);
	}

	std::string ValueToName(T_Enum value) const
	{
		return IntToName((int) value);
	}

private:
	std::string m_enumName;
	std::map<std::string, int> m_nameToValue;
	std::map<int, std::string> m_valueToName;
};

const TypeInfoBase* GetTagTypeInfo(GameTag tag);


}; // namespace enums

#endif // _ENUMS_H_