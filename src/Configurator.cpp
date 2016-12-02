#include "Configurator.h"

Configurator::Configurator() {}

OptionTypedData& Configurator::operator()(const char* id, bool doCreate)
{
	if(doCreate)
		return m_options[id];
	else
	{
		/* Cast current object to const to avoid ambiguous operator()()
		 * otherwise, infinite loop on operator()(const char*, bool) */
		const Configurator * const constThis = this;
		constThis->operator()(id);
	}
}

const OptionTypedData& Configurator::operator()(const char* id) const
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


