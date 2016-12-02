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

class Configurator : public Singleton<Configurator>
{
	friend class Singleton<Configurator>;

public:
	OptionTypedData& operator[](const char*);
	const OptionTypedData& operator[](const char*) const;

private:
	Configurator();

	std::map<std::string, OptionTypedData> m_options;
};

#endif //CONFIGURATOR__H
