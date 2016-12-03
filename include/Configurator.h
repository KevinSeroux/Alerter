#ifndef CONFIGURATOR__H
#define CONFIGURATOR__H

#include "OptionTypedData.h"
#include "Singleton.h"
#include <string>
#include <map>

class OptionNotFound : public std::runtime_error
{
public:
	OptionNotFound(std::string& str) : runtime_error(str) {}
};

struct Option
{
	std::string id;
	OptionTypedData data;
};

class Configurator : public Singleton<Configurator>
{
	friend class Singleton<Configurator>;

public:
	/* \param id The option identifier
	 * \param create Set to true if the option must be created */
	OptionTypedData& operator()(const char* id, bool doCreate = false);

	const OptionTypedData& operator()(const char*) const;

private:
	Configurator();

	std::map<std::string, OptionTypedData> m_options;
};

#endif //CONFIGURATOR__H
