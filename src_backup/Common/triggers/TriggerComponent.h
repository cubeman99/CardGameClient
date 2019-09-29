#ifndef _COMMON_TRIGGER_COMPONENT_H_
#define _COMMON_TRIGGER_COMPONENT_H_

#include <string>
#include <GameLib/math/MathLib.h>
#include <vector>

struct Context;

class TriggerComponent
{
public:
	TriggerComponent();

	inline const std::string& GetCatagory() const { return m_catagory; }
	inline const std::string& GetName() const { return m_name; }
	inline const std::string& GetInfo() const { return m_info; }
	std::string GetText() const;

protected:
	inline Context* GetContext() { return context; }

	std::string m_catagory;
	std::string m_name;
	std::string m_info;
	std::string m_text;
	std::vector<TriggerComponent*> m_components;

	Context* context;
};


#endif // _COMMON_TRIGGER_EVENT_H_