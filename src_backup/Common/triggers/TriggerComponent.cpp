#include "TriggerComponent.h"
#include <sstream>

TriggerComponent::TriggerComponent()
{

}

std::string TriggerComponent::GetText() const
{
	std::string text = m_text;
	std::stringstream stringStream;

	for (unsigned int i = 0; i < m_components.size(); ++i)
	{
		stringStream.str("");
		stringStream << "$" << (i + 1);
		std::string key = stringStream.str();
		std::string componentText = m_components[i]->GetText();

		size_t start_pos = 0;
		while ((start_pos = text.find(key, start_pos)) != std::string::npos)
		{
			text.replace(start_pos, key.length(), componentText);
			start_pos += componentText.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
		}
	}

	return text;
}
