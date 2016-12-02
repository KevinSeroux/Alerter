#include "Configurator.h"

Configurator::Configurator() {}

OptionTypedData& Configurator::operator[](const char* id)
{
	return m_options[id];
}

const OptionTypedData& Configurator::operator[](const char* id) const
{
	auto optionIt =	m_options.find(id);

	if(optionIt == m_options.end())
	{
		std::string message = "Option ";
		message += id;
		message += " not found";
		throw OptionNotFound(message);
	}

	return optionIt->second;
}


