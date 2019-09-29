#include "Enums.h"
#include <algorithm>
#include <map>

namespace enums {


template <> std::string EnumName<BlockType>()
{
	return "BlockType";
}

template <> std::string EnumName<CardType>()
{
	return "CardType";
}

template <> std::string EnumName<ChoiceType>()
{
	return "ChoiceType";
}

template <> std::string EnumName<GameTag>()
{
	return "GameTag";
}

template <> std::string EnumName<OptionType>()
{
	return "OptionType";
}

template <> std::string EnumName<Requirement>()
{
	return "Requirement";
}

template <> std::string EnumName<ResourceType>()
{
	return "ResourceType";
}

template <> std::string EnumName<Step>()
{
	return "Step";
}

template <> std::string EnumName<Tribe>()
{
	return "Tribe";
}

template <> std::string EnumName<Type>()
{
	return "Type";
}

template <> std::string EnumName<Zone>()
{
	return "Zone";
}



const std::string EnumMap<BlockType>::ENUM_NAME = "BlockType";

const std::map<BlockType, std::string> EnumMap<BlockType>::VALUE_TO_STRING =
{
	{BlockType::ATTACK,  "ATTACK"},
	{BlockType::CHOICE,  "CHOICE"},
	{BlockType::POWER,   "POWER"},
	{BlockType::TRIGGER, "TRIGGER"},
	{BlockType::DEATHS,  "DEATHS"},
	{BlockType::PLAY,    "PLAY"},
};
const std::map<std::string, BlockType> EnumMap<BlockType>::STRING_TO_VALUE =
{
	{"ATTACK",  BlockType::ATTACK},
	{"CHOICE",  BlockType::CHOICE},
	{"POWER",   BlockType::POWER},
	{"TRIGGER", BlockType::TRIGGER},
	{"DEATHS",  BlockType::DEATHS},
	{"PLAY",    BlockType::PLAY},
};
const std::map<std::string, int> EnumMap<BlockType>::STRING_TO_INT =
{
	{"ATTACK",  1},
	{"CHOICE",  2},
	{"POWER",   3},
	{"TRIGGER", 4},
	{"DEATHS",  5},
	{"PLAY",    6},
};

const std::string EnumMap<CardType>::ENUM_NAME = "CardType";

const std::map<CardType, std::string> EnumMap<CardType>::VALUE_TO_STRING =
{
	{CardType::INVALID, "INVALID"},
	{CardType::GAME,    "GAME"},
	{CardType::PLAYER,  "PLAYER"},
	{CardType::UNIT,    "UNIT"},
	{CardType::SPELL,   "SPELL"},
	{CardType::EFFECT,  "EFFECT"},
	{CardType::TOKEN,   "TOKEN"},
};
const std::map<std::string, CardType> EnumMap<CardType>::STRING_TO_VALUE =
{
	{"INVALID", CardType::INVALID},
	{"GAME",    CardType::GAME},
	{"PLAYER",  CardType::PLAYER},
	{"UNIT",    CardType::UNIT},
	{"SPELL",   CardType::SPELL},
	{"EFFECT",  CardType::EFFECT},
	{"TOKEN",   CardType::TOKEN},
};
const std::map<std::string, int> EnumMap<CardType>::STRING_TO_INT =
{
	{"INVALID", 0},
	{"GAME",    1},
	{"PLAYER",  2},
	{"UNIT",    3},
	{"SPELL",   4},
	{"EFFECT",  5},
	{"TOKEN",   6},
};

const std::string EnumMap<ChoiceType>::ENUM_NAME = "ChoiceType";

const std::map<ChoiceType, std::string> EnumMap<ChoiceType>::VALUE_TO_STRING =
{
	{ChoiceType::INVALID, "INVALID"},
	{ChoiceType::GENERAL, "GENERAL"},
	{ChoiceType::TARGET,  "TARGET"},
};
const std::map<std::string, ChoiceType> EnumMap<ChoiceType>::STRING_TO_VALUE =
{
	{"INVALID", ChoiceType::INVALID},
	{"GENERAL", ChoiceType::GENERAL},
	{"TARGET",  ChoiceType::TARGET},
};
const std::map<std::string, int> EnumMap<ChoiceType>::STRING_TO_INT =
{
	{"INVALID", 0},
	{"GENERAL", 1},
	{"TARGET",  2},
};

const std::string EnumMap<GameTag>::ENUM_NAME = "GameTag";

const std::map<GameTag, std::string> EnumMap<GameTag>::VALUE_TO_STRING =
{
	{GameTag::INVALID,            "INVALID"},
	{GameTag::POWER,              "POWER"},
	{GameTag::HEALTH,             "HEALTH"},
	{GameTag::TRIBE,              "TRIBE"},
	{GameTag::CARD_TYPE,          "CARD_TYPE"},
	{GameTag::REQUIREMENT,        "REQUIREMENT"},
	{GameTag::CONTROLLER,         "CONTROLLER"},
	{GameTag::RESOURCE_TYPE,      "RESOURCE_TYPE"},
	{GameTag::MORALE,             "MORALE"},
	{GameTag::SUPPLY,             "SUPPLY"},
	{GameTag::BATTLE,             "BATTLE"},
	{GameTag::NAME,               "NAME"},
	{GameTag::TEXT,               "TEXT"},
	{GameTag::TERRITORY,          "TERRITORY"},
	{GameTag::MAX_HAND_SIZE,      "MAX_HAND_SIZE"},
	{GameTag::STEP,               "STEP"},
	{GameTag::NEXT_STEP,          "NEXT_STEP"},
	{GameTag::CARD_ID,            "CARD_ID"},
	{GameTag::ENTITY_ID,          "ENTITY_ID"},
	{GameTag::ZONE,               "ZONE"},
	{GameTag::DAMAGE,             "DAMAGE"},
	{GameTag::OWNER,              "OWNER"},
	{GameTag::DECLARED_ATTACK,    "DECLARED_ATTACK"},
	{GameTag::DECLARED_INTERCEPT, "DECLARED_INTERCEPT"},
	{GameTag::TURN_NUMBER,        "TURN_NUMBER"},
	{GameTag::TURN_PLAYER,        "TURN_PLAYER"},
	{GameTag::STEP_PLAYER,        "STEP_PLAYER"},
	{GameTag::MUDDLE,             "MUDDLE"},
	{GameTag::AFTERMATH,          "AFTERMATH"},
	{GameTag::STING,              "STING"},
	{GameTag::CORRUPT,            "CORRUPT"},
	{GameTag::INSPIRE,            "INSPIRE"},
	{GameTag::EMERGE,             "EMERGE"},
	{GameTag::SPY,                "SPY"},
	{GameTag::INFORM,             "INFORM"},
	{GameTag::CONDUIT,            "CONDUIT"},
	{GameTag::TOXIC,              "TOXIC"},
	{GameTag::WISDOM,             "WISDOM"},
	{GameTag::RENEW,              "RENEW"},
	{GameTag::FURY,               "FURY"},
	{GameTag::SWARM,              "SWARM"},
	{GameTag::HEROIC,             "HEROIC"},
};
const std::map<std::string, GameTag> EnumMap<GameTag>::STRING_TO_VALUE =
{
	{"INVALID",            GameTag::INVALID},
	{"POWER",              GameTag::POWER},
	{"HEALTH",             GameTag::HEALTH},
	{"TRIBE",              GameTag::TRIBE},
	{"CARD_TYPE",          GameTag::CARD_TYPE},
	{"REQUIREMENT",        GameTag::REQUIREMENT},
	{"CONTROLLER",         GameTag::CONTROLLER},
	{"RESOURCE_TYPE",      GameTag::RESOURCE_TYPE},
	{"MORALE",             GameTag::MORALE},
	{"SUPPLY",             GameTag::SUPPLY},
	{"BATTLE",             GameTag::BATTLE},
	{"NAME",               GameTag::NAME},
	{"TEXT",               GameTag::TEXT},
	{"TERRITORY",          GameTag::TERRITORY},
	{"MAX_HAND_SIZE",      GameTag::MAX_HAND_SIZE},
	{"STEP",               GameTag::STEP},
	{"NEXT_STEP",          GameTag::NEXT_STEP},
	{"CARD_ID",            GameTag::CARD_ID},
	{"ENTITY_ID",          GameTag::ENTITY_ID},
	{"ZONE",               GameTag::ZONE},
	{"DAMAGE",             GameTag::DAMAGE},
	{"OWNER",              GameTag::OWNER},
	{"DECLARED_ATTACK",    GameTag::DECLARED_ATTACK},
	{"DECLARED_INTERCEPT", GameTag::DECLARED_INTERCEPT},
	{"TURN_NUMBER",        GameTag::TURN_NUMBER},
	{"TURN_PLAYER",        GameTag::TURN_PLAYER},
	{"STEP_PLAYER",        GameTag::STEP_PLAYER},
	{"MUDDLE",             GameTag::MUDDLE},
	{"AFTERMATH",          GameTag::AFTERMATH},
	{"STING",              GameTag::STING},
	{"CORRUPT",            GameTag::CORRUPT},
	{"INSPIRE",            GameTag::INSPIRE},
	{"EMERGE",             GameTag::EMERGE},
	{"SPY",                GameTag::SPY},
	{"INFORM",             GameTag::INFORM},
	{"CONDUIT",            GameTag::CONDUIT},
	{"TOXIC",              GameTag::TOXIC},
	{"WISDOM",             GameTag::WISDOM},
	{"RENEW",              GameTag::RENEW},
	{"FURY",               GameTag::FURY},
	{"SWARM",              GameTag::SWARM},
	{"HEROIC",             GameTag::HEROIC},
};
const std::map<std::string, int> EnumMap<GameTag>::STRING_TO_INT =
{
	{"INVALID",            -1},
	{"POWER",              1},
	{"HEALTH",             2},
	{"TRIBE",              3},
	{"CARD_TYPE",          4},
	{"REQUIREMENT",        5},
	{"CONTROLLER",         6},
	{"RESOURCE_TYPE",      7},
	{"MORALE",             8},
	{"SUPPLY",             9},
	{"BATTLE",             10},
	{"NAME",               11},
	{"TEXT",               12},
	{"TERRITORY",          13},
	{"MAX_HAND_SIZE",      14},
	{"STEP",               15},
	{"NEXT_STEP",          16},
	{"CARD_ID",            17},
	{"ENTITY_ID",          18},
	{"ZONE",               19},
	{"DAMAGE",             20},
	{"OWNER",              21},
	{"DECLARED_ATTACK",    22},
	{"DECLARED_INTERCEPT", 23},
	{"TURN_NUMBER",        24},
	{"TURN_PLAYER",        25},
	{"STEP_PLAYER",        26},
	{"MUDDLE",             100},
	{"AFTERMATH",          101},
	{"STING",              102},
	{"CORRUPT",            103},
	{"INSPIRE",            104},
	{"EMERGE",             105},
	{"SPY",                106},
	{"INFORM",             107},
	{"CONDUIT",            108},
	{"TOXIC",              109},
	{"WISDOM",             110},
	{"RENEW",              111},
	{"FURY",               112},
	{"SWARM",              113},
	{"HEROIC",             114},
};

const std::string EnumMap<OptionType>::ENUM_NAME = "OptionType";

const std::map<OptionType, std::string> EnumMap<OptionType>::VALUE_TO_STRING =
{
	{OptionType::INVALID, "INVALID"},
	{OptionType::DONE,    "DONE"},
	{OptionType::DECLARE, "DECLARE"},
	{OptionType::FLIP,    "FLIP"},
	{OptionType::PLAY,    "PLAY"},
	{OptionType::CHOOSE,  "CHOOSE"},
};
const std::map<std::string, OptionType> EnumMap<OptionType>::STRING_TO_VALUE =
{
	{"INVALID", OptionType::INVALID},
	{"DONE",    OptionType::DONE},
	{"DECLARE", OptionType::DECLARE},
	{"FLIP",    OptionType::FLIP},
	{"PLAY",    OptionType::PLAY},
	{"CHOOSE",  OptionType::CHOOSE},
};
const std::map<std::string, int> EnumMap<OptionType>::STRING_TO_INT =
{
	{"INVALID", 0},
	{"DONE",    1},
	{"DECLARE", 2},
	{"FLIP",    3},
	{"PLAY",    4},
	{"CHOOSE",  5},
};

const std::string EnumMap<Requirement>::ENUM_NAME = "Requirement";

const std::map<Requirement, std::string> EnumMap<Requirement>::VALUE_TO_STRING =
{
	{Requirement::INVALID,           "INVALID"},
	{Requirement::REQ_UNIT_TARGET,   "REQ_UNIT_TARGET"},
	{Requirement::REQ_ALLIED_TARGET, "REQ_ALLIED_TARGET"},
	{Requirement::REQ_ENEMY_TARGET,  "REQ_ENEMY_TARGET"},
	{Requirement::REQ_,              "REQ_"},
};
const std::map<std::string, Requirement> EnumMap<Requirement>::STRING_TO_VALUE =
{
	{"INVALID",           Requirement::INVALID},
	{"REQ_UNIT_TARGET",   Requirement::REQ_UNIT_TARGET},
	{"REQ_ALLIED_TARGET", Requirement::REQ_ALLIED_TARGET},
	{"REQ_ENEMY_TARGET",  Requirement::REQ_ENEMY_TARGET},
	{"REQ_",              Requirement::REQ_},
};
const std::map<std::string, int> EnumMap<Requirement>::STRING_TO_INT =
{
	{"INVALID",           -1},
	{"REQ_UNIT_TARGET",   0},
	{"REQ_ALLIED_TARGET", 1},
	{"REQ_ENEMY_TARGET",  2},
	{"REQ_",              3},
};

const std::string EnumMap<ResourceType>::ENUM_NAME = "ResourceType";

const std::map<ResourceType, std::string> EnumMap<ResourceType>::VALUE_TO_STRING =
{
	{ResourceType::INVALID, "INVALID"},
	{ResourceType::MORALE,  "MORALE"},
	{ResourceType::SUPPLY,  "SUPPLY"},
};
const std::map<std::string, ResourceType> EnumMap<ResourceType>::STRING_TO_VALUE =
{
	{"INVALID", ResourceType::INVALID},
	{"MORALE",  ResourceType::MORALE},
	{"SUPPLY",  ResourceType::SUPPLY},
};
const std::map<std::string, int> EnumMap<ResourceType>::STRING_TO_INT =
{
	{"INVALID", 0},
	{"MORALE",  1},
	{"SUPPLY",  2},
};

const std::string EnumMap<Step>::ENUM_NAME = "Step";

const std::map<Step, std::string> EnumMap<Step>::VALUE_TO_STRING =
{
	{Step::INVALID,  "INVALID"},
	{Step::UNFLIP,   "UNFLIP"},
	{Step::RESOURCE, "RESOURCE"},
	{Step::DECLARE,  "DECLARE"},
	{Step::RESPONSE, "RESPONSE"},
	{Step::COMBAT,   "COMBAT"},
	{Step::PLAY,     "PLAY"},
};
const std::map<std::string, Step> EnumMap<Step>::STRING_TO_VALUE =
{
	{"INVALID",  Step::INVALID},
	{"UNFLIP",   Step::UNFLIP},
	{"RESOURCE", Step::RESOURCE},
	{"DECLARE",  Step::DECLARE},
	{"RESPONSE", Step::RESPONSE},
	{"COMBAT",   Step::COMBAT},
	{"PLAY",     Step::PLAY},
};
const std::map<std::string, int> EnumMap<Step>::STRING_TO_INT =
{
	{"INVALID",  0},
	{"UNFLIP",   1},
	{"RESOURCE", 2},
	{"DECLARE",  3},
	{"RESPONSE", 4},
	{"COMBAT",   5},
	{"PLAY",     6},
};

const std::string EnumMap<Tribe>::ENUM_NAME = "Tribe";

const std::map<Tribe, std::string> EnumMap<Tribe>::VALUE_TO_STRING =
{
	{Tribe::INVALID,  "INVALID"},
	{Tribe::SLUG,     "SLUG"},
	{Tribe::OCTOPI,   "OCTOPI"},
	{Tribe::MOLE,     "MOLE"},
	{Tribe::DRAKE,    "DRAKE"},
	{Tribe::EEL,      "EEL"},
	{Tribe::AARD,     "AARD"},
	{Tribe::PHEASANT, "PHEASANT"},
};
const std::map<std::string, Tribe> EnumMap<Tribe>::STRING_TO_VALUE =
{
	{"INVALID",  Tribe::INVALID},
	{"SLUG",     Tribe::SLUG},
	{"OCTOPI",   Tribe::OCTOPI},
	{"MOLE",     Tribe::MOLE},
	{"DRAKE",    Tribe::DRAKE},
	{"EEL",      Tribe::EEL},
	{"AARD",     Tribe::AARD},
	{"PHEASANT", Tribe::PHEASANT},
};
const std::map<std::string, int> EnumMap<Tribe>::STRING_TO_INT =
{
	{"INVALID",  0},
	{"SLUG",     1},
	{"OCTOPI",   2},
	{"MOLE",     3},
	{"DRAKE",    4},
	{"EEL",      5},
	{"AARD",     6},
	{"PHEASANT", 7},
};

const std::string EnumMap<Type>::ENUM_NAME = "Type";

const std::map<Type, std::string> EnumMap<Type>::VALUE_TO_STRING =
{
	{Type::UNKNOWN,           "UNKNOWN"},
	{Type::BOOL,              "BOOL"},
	{Type::NUMBER,            "NUMBER"},
	{Type::COUNTER,           "COUNTER"},
	{Type::ENTITY,            "ENTITY"},
	{Type::PLAYER,            "PLAYER"},
	{Type::TEAM,              "TEAM"},
	{Type::ENTITY_DEFINITION, "ENTITY_DEFINITION"},
	{Type::STRING,            "STRING"},
	{Type::ENUM,              "ENUM"},
	{Type::LOCSTRING,         "LOCSTRING"},
};
const std::map<std::string, Type> EnumMap<Type>::STRING_TO_VALUE =
{
	{"UNKNOWN",           Type::UNKNOWN},
	{"BOOL",              Type::BOOL},
	{"NUMBER",            Type::NUMBER},
	{"COUNTER",           Type::COUNTER},
	{"ENTITY",            Type::ENTITY},
	{"PLAYER",            Type::PLAYER},
	{"TEAM",              Type::TEAM},
	{"ENTITY_DEFINITION", Type::ENTITY_DEFINITION},
	{"STRING",            Type::STRING},
	{"ENUM",              Type::ENUM},
	{"LOCSTRING",         Type::LOCSTRING},
};
const std::map<std::string, int> EnumMap<Type>::STRING_TO_INT =
{
	{"UNKNOWN",           0},
	{"BOOL",              1},
	{"NUMBER",            2},
	{"COUNTER",           3},
	{"ENTITY",            4},
	{"PLAYER",            5},
	{"TEAM",              6},
	{"ENTITY_DEFINITION", 7},
	{"STRING",            8},
	{"ENUM",              9},
	{"LOCSTRING",         -2},
};

const std::string EnumMap<Zone>::ENUM_NAME = "Zone";

const std::map<Zone, std::string> EnumMap<Zone>::VALUE_TO_STRING =
{
	{Zone::INVALID,           "INVALID"},
	{Zone::PLAY,              "PLAY"},
	{Zone::DECK,              "DECK"},
	{Zone::HAND,              "HAND"},
	{Zone::DISCARD,           "DISCARD"},
	{Zone::SET_ASIDE,         "SET_ASIDE"},
	{Zone::REMOVED_FROM_GAME, "REMOVED_FROM_GAME"},
};
const std::map<std::string, Zone> EnumMap<Zone>::STRING_TO_VALUE =
{
	{"INVALID",           Zone::INVALID},
	{"PLAY",              Zone::PLAY},
	{"DECK",              Zone::DECK},
	{"HAND",              Zone::HAND},
	{"DISCARD",           Zone::DISCARD},
	{"SET_ASIDE",         Zone::SET_ASIDE},
	{"REMOVED_FROM_GAME", Zone::REMOVED_FROM_GAME},
};
const std::map<std::string, int> EnumMap<Zone>::STRING_TO_INT =
{
	{"INVALID",           0},
	{"PLAY",              1},
	{"DECK",              2},
	{"HAND",              3},
	{"DISCARD",           4},
	{"SET_ASIDE",         5},
	{"REMOVED_FROM_GAME", 6},
};


Type GetTagType(GameTag tag)
{
	switch (tag)
	{
	case GameTag::TRIBE:              return Type::ENUM;
	case GameTag::CARD_TYPE:          return Type::ENUM;
	case GameTag::CONTROLLER:         return Type::PLAYER;
	case GameTag::NAME:               return Type::STRING;
	case GameTag::TEXT:               return Type::STRING;
	case GameTag::STEP:               return Type::ENUM;
	case GameTag::CARD_ID:            return Type::STRING;
	case GameTag::ZONE:               return Type::ENUM;
	case GameTag::DECLARED_ATTACK:    return Type::ENTITY;
	case GameTag::DECLARED_INTERCEPT: return Type::ENTITY;
	default: return Type::NUMBER;
	}
}

std::string GetTagEnumValueName(GameTag tag, int value)
{
	switch (tag)
	{
	case GameTag::TRIBE:              return ValueName(Tribe(value));
	case GameTag::CARD_TYPE:          return ValueName(CardType(value));
	case GameTag::STEP:               return ValueName(Step(value));
	case GameTag::ZONE:               return ValueName(Zone(value));
	default: return "UNKNOWN";
	}
}



const TypeInfo<BlockType> TYPE_INFO_BLOCKTYPE = TypeInfo<BlockType>(
	"BlockType",
	{
		{"ATTACK", 1},
		{"CHOICE", 2},
		{"POWER", 3},
		{"TRIGGER", 4},
		{"DEATHS", 5},
		{"PLAY", 6},
	},{
		{1, "ATTACK"},
		{2, "CHOICE"},
		{3, "POWER"},
		{4, "TRIGGER"},
		{5, "DEATHS"},
		{6, "PLAY"},
	}
);

const TypeInfo<CardType> TYPE_INFO_CARDTYPE = TypeInfo<CardType>(
	"CardType",
	{
		{"INVALID", 0},
		{"GAME", 1},
		{"PLAYER", 2},
		{"UNIT", 3},
		{"SPELL", 4},
		{"EFFECT", 5},
		{"TOKEN", 6},
	},{
		{0, "INVALID"},
		{1, "GAME"},
		{2, "PLAYER"},
		{3, "UNIT"},
		{4, "SPELL"},
		{5, "EFFECT"},
		{6, "TOKEN"},
	}
);

const TypeInfo<ChoiceType> TYPE_INFO_CHOICETYPE = TypeInfo<ChoiceType>(
	"ChoiceType",
	{
		{"INVALID", 0},
		{"GENERAL", 1},
		{"TARGET", 2},
	},{
		{0, "INVALID"},
		{1, "GENERAL"},
		{2, "TARGET"},
	}
);

const TypeInfo<GameTag> TYPE_INFO_GAMETAG = TypeInfo<GameTag>(
	"GameTag",
	{
		{"INVALID",  -1},
		{"POWER",   1},
		{"HEALTH",   2},
		{"TRIBE",   3},
		{"CARD_TYPE",   4},
		{"REQUIREMENT",   5},
		{"CONTROLLER",   6},
		{"RESOURCE_TYPE",   7},
		{"MORALE",   8},
		{"SUPPLY",   9},
		{"BATTLE",  10},
		{"NAME",  11},
		{"TEXT",  12},
		{"TERRITORY",  13},
		{"MAX_HAND_SIZE",  14},
		{"STEP",  15},
		{"NEXT_STEP",  16},
		{"CARD_ID",  17},
		{"ENTITY_ID",  18},
		{"ZONE",  19},
		{"DAMAGE",  20},
		{"OWNER",  21},
		{"DECLARED_ATTACK",  22},
		{"DECLARED_INTERCEPT",  23},
		{"TURN_NUMBER",  24},
		{"TURN_PLAYER",  25},
		{"STEP_PLAYER",  26},
		{"MUDDLE", 100},
		{"AFTERMATH", 101},
		{"STING", 102},
		{"CORRUPT", 103},
		{"INSPIRE", 104},
		{"EMERGE", 105},
		{"SPY", 106},
		{"INFORM", 107},
		{"CONDUIT", 108},
		{"TOXIC", 109},
		{"WISDOM", 110},
		{"RENEW", 111},
		{"FURY", 112},
		{"SWARM", 113},
		{"HEROIC", 114},
	},{
		{-1,  "INVALID"},
		{1,   "POWER"},
		{2,   "HEALTH"},
		{3,   "TRIBE"},
		{4,   "CARD_TYPE"},
		{5,   "REQUIREMENT"},
		{6,   "CONTROLLER"},
		{7,   "RESOURCE_TYPE"},
		{8,   "MORALE"},
		{9,   "SUPPLY"},
		{10,  "BATTLE"},
		{11,  "NAME"},
		{12,  "TEXT"},
		{13,  "TERRITORY"},
		{14,  "MAX_HAND_SIZE"},
		{15,  "STEP"},
		{16,  "NEXT_STEP"},
		{17,  "CARD_ID"},
		{18,  "ENTITY_ID"},
		{19,  "ZONE"},
		{20,  "DAMAGE"},
		{21,  "OWNER"},
		{22,  "DECLARED_ATTACK"},
		{23,  "DECLARED_INTERCEPT"},
		{24,  "TURN_NUMBER"},
		{25,  "TURN_PLAYER"},
		{26,  "STEP_PLAYER"},
		{100, "MUDDLE"},
		{101, "AFTERMATH"},
		{102, "STING"},
		{103, "CORRUPT"},
		{104, "INSPIRE"},
		{105, "EMERGE"},
		{106, "SPY"},
		{107, "INFORM"},
		{108, "CONDUIT"},
		{109, "TOXIC"},
		{110, "WISDOM"},
		{111, "RENEW"},
		{112, "FURY"},
		{113, "SWARM"},
		{114, "HEROIC"},
	}
);

const TypeInfo<OptionType> TYPE_INFO_OPTIONTYPE = TypeInfo<OptionType>(
	"OptionType",
	{
		{"INVALID", 0},
		{"DONE", 1},
		{"DECLARE", 2},
		{"FLIP", 3},
		{"PLAY", 4},
		{"CHOOSE", 5},
	},{
		{0, "INVALID"},
		{1, "DONE"},
		{2, "DECLARE"},
		{3, "FLIP"},
		{4, "PLAY"},
		{5, "CHOOSE"},
	}
);

const TypeInfo<Requirement> TYPE_INFO_REQUIREMENT = TypeInfo<Requirement>(
	"Requirement",
	{
		{"INVALID", -1},
		{"REQ_UNIT_TARGET",  0},
		{"REQ_ALLIED_TARGET",  1},
		{"REQ_ENEMY_TARGET",  2},
		{"REQ_",  3},
	},{
		{-1, "INVALID"},
		{0,  "REQ_UNIT_TARGET"},
		{1,  "REQ_ALLIED_TARGET"},
		{2,  "REQ_ENEMY_TARGET"},
		{3,  "REQ_"},
	}
);

const TypeInfo<ResourceType> TYPE_INFO_RESOURCETYPE = TypeInfo<ResourceType>(
	"ResourceType",
	{
		{"INVALID", 0},
		{"MORALE", 1},
		{"SUPPLY", 2},
	},{
		{0, "INVALID"},
		{1, "MORALE"},
		{2, "SUPPLY"},
	}
);

const TypeInfo<Step> TYPE_INFO_STEP = TypeInfo<Step>(
	"Step",
	{
		{"INVALID", 0},
		{"UNFLIP", 1},
		{"RESOURCE", 2},
		{"DECLARE", 3},
		{"RESPONSE", 4},
		{"COMBAT", 5},
		{"PLAY", 6},
	},{
		{0, "INVALID"},
		{1, "UNFLIP"},
		{2, "RESOURCE"},
		{3, "DECLARE"},
		{4, "RESPONSE"},
		{5, "COMBAT"},
		{6, "PLAY"},
	}
);

const TypeInfo<Tribe> TYPE_INFO_TRIBE = TypeInfo<Tribe>(
	"Tribe",
	{
		{"INVALID", 0},
		{"SLUG", 1},
		{"OCTOPI", 2},
		{"MOLE", 3},
		{"DRAKE", 4},
		{"EEL", 5},
		{"AARD", 6},
		{"PHEASANT", 7},
	},{
		{0, "INVALID"},
		{1, "SLUG"},
		{2, "OCTOPI"},
		{3, "MOLE"},
		{4, "DRAKE"},
		{5, "EEL"},
		{6, "AARD"},
		{7, "PHEASANT"},
	}
);

const TypeInfo<Type> TYPE_INFO_TYPE = TypeInfo<Type>(
	"Type",
	{
		{"UNKNOWN",  0},
		{"BOOL",  1},
		{"NUMBER",  2},
		{"COUNTER",  3},
		{"ENTITY",  4},
		{"PLAYER",  5},
		{"TEAM",  6},
		{"ENTITY_DEFINITION",  7},
		{"STRING",  8},
		{"ENUM",  9},
		{"LOCSTRING", -2},
	},{
		{0,  "UNKNOWN"},
		{1,  "BOOL"},
		{2,  "NUMBER"},
		{3,  "COUNTER"},
		{4,  "ENTITY"},
		{5,  "PLAYER"},
		{6,  "TEAM"},
		{7,  "ENTITY_DEFINITION"},
		{8,  "STRING"},
		{9,  "ENUM"},
		{-2, "LOCSTRING"},
	}
);

const TypeInfo<Zone> TYPE_INFO_ZONE = TypeInfo<Zone>(
	"Zone",
	{
		{"INVALID", 0},
		{"PLAY", 1},
		{"DECK", 2},
		{"HAND", 3},
		{"DISCARD", 4},
		{"SET_ASIDE", 5},
		{"REMOVED_FROM_GAME", 6},
	},{
		{0, "INVALID"},
		{1, "PLAY"},
		{2, "DECK"},
		{3, "HAND"},
		{4, "DISCARD"},
		{5, "SET_ASIDE"},
		{6, "REMOVED_FROM_GAME"},
	}
);



const TypeInfoBase* GetTagTypeInfo(GameTag tag)
{
	switch (tag)
	{
	case GameTag::TRIBE:     return &TYPE_INFO_TRIBE;
	case GameTag::CARD_TYPE: return &TYPE_INFO_CARDTYPE;
	case GameTag::STEP:      return &TYPE_INFO_STEP;
	case GameTag::ZONE:      return &TYPE_INFO_ZONE;
	default: return nullptr;
	}
}

}; // namespace enums
