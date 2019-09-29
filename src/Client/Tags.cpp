#include "Tags.h"
#include <sstream>
#include <iostream>


TagValue::TagValue(json value)
{
	if (value.is_string())
	{
		std::string s = value;
		strValue = s;
	}
	else if (value.is_number_integer())
	{
		intValue = value;
	}
}


enums::Type TagHandle::Type() const
{
	return m_type;
}

std::ostream& operator <<(std::ostream& out, const TagHandle& tagHandle)
{
	if (tagHandle.m_value == nullptr)
		out << "null";
	else if (tagHandle.m_type == enums::Type::STRING)
		out << tagHandle.m_value->strValue;
	else
		out << tagHandle.m_value->intValue;
	return out;
}

std::string TagHandle::ValueName() const
{
	std::stringstream ss;
	if (m_value == nullptr)
		ss << "null";
	else if (m_type == enums::Type::STRING)
		ss << m_value->strValue;
	else if (m_type == enums::Type::ENUM)
		ss << enums::GetTagEnumValueName(m_tag, m_value->intValue);
	else
		ss << m_value->intValue;
	return ss.str();
}

TagHandle::TagHandle(Tags* tags, enums::GameTag tag, TagValue* value) :
	m_tags(tags),
	m_tag(tag),
	m_value(value),
	m_type(enums::GetTagType(tag))
{
}

void TagHandle::Create()
{
	if (m_value == nullptr)
	{
		TagValue tagValue;
		m_tags->m_map.insert(
			std::pair<enums::GameTag, TagValue>(m_tag, tagValue));
		m_value = &m_tags->m_map[m_tag];
	}
}


const Tags Tags::EMPTY = Tags();



Tags::Tags()
{
}

Tags::Tags(json data)
{
	TagValue value;

	for (auto it = data.begin(); it != data.end(); ++it)
	{
		std::string key = it.key();
		enums::GameTag tag = enums::GameTag(std::stoi(it.key()));
		
		if (it.value().is_string())
		{
			std::string s = it.value();
			value.strValue = s;
		}
		else
			value.intValue = it.value();

		m_map[tag] = value;
	}
}

Tags::~Tags()
{
}

TagHandle Tags::operator [](enums::GameTag tag)
{
	// Check if this tag doesn't exists.
	auto it = m_map.find(tag);
	if (it != m_map.end())
		return TagHandle(this, tag, &it->second);
	return TagHandle(this, tag, nullptr);
}

const TagHandle Tags::operator [](enums::GameTag tag) const
{
	return Get(tag);
}

const TagHandle Tags::Get(enums::GameTag tag) const
{
	// Check if this tag doesn't exists.
	auto it = m_map.find(tag);
	if (it != m_map.end())
		return TagHandle((Tags*) this, tag, (TagValue*) &it->second);
	return TagHandle((Tags*) this, tag, nullptr);
}

const TagHandle Tags::Get(enums::GameTag tag, const TagValue& default) const
{
	// Check if this tag doesn't exists.
	auto it = m_map.find(tag);
	if (it != m_map.end())
		return TagHandle((Tags*) this, tag, (TagValue*) &it->second);
	
	TagHandle handle((Tags*) this, tag, nullptr);
	handle.m_defaultValue = default;
	handle.m_value = &handle.m_defaultValue;
	return handle;
}

void Tags::Update(const Tags& tags)
{
	for (auto it = tags.m_map.begin(); it != tags.m_map.end(); ++it)
		m_map[it->first] = it->second;
}

json Tags::ToJSON() const
{
	json result;
	for (auto it = m_map.begin(); it != m_map.end(); ++it)
	{
		enums::Type type = enums::GetTagType(it->first);
		std::string key = std::to_string((int) it->first);

		if (type == enums::Type::STRING)
			result[key] = it->second.strValue;
		else
			result[key] = it->second.intValue;
	}
	return result;
}

std::string Tags::Dump()
{
	std::stringstream ss;
	for (auto it = m_map.begin(); it != m_map.end(); ++it)
	{
		TagHandle handle(this, it->first, &it->second);
		ss << enums::ValueName(handle.m_tag)
			<< " = " << handle.ValueName() << std::endl;
	}
	return ss.str();
}



