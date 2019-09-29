#include "Effect.h"

Effect::Effect()
{
}

Effect::Effect(const std::string& name, Trigger* trigger) :
	m_name(name)
{
	m_triggers.push_back(trigger);
}

