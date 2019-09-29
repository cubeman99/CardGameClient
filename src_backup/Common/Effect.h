#ifndef _COMMON_EFFECT_H_
#define _COMMON_EFFECT_H_

#include "triggers/Trigger.h"
#include "events/EventListener.h"

class Effect
{
public:
	Effect();
	Effect(const std::string& name, Trigger* trigger);

	inline const std::string& GetName() const { return m_name; }
	
	inline std::vector<Trigger*>::iterator triggers_begin() { return m_triggers.begin(); }
	inline std::vector<Trigger*>::iterator triggers_end() { return m_triggers.end(); }

private:
	std::vector<Trigger*> m_triggers;
	std::string m_name;
};


#endif // _COMMON_EFFECT_H_