#ifndef CONFIGURATOR__H
#define CONFIGURATOR__H

#define BOOST_SPIRIT_THREADSAFE //Make boost property tree thread-safe

#include "Singleton.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/any.hpp>
#include <vector>

struct Option
{
	std::string id;
	std::string data;
};

class Configurator :
public Singleton<Configurator>, public boost::property_tree::ptree
{
friend class Singleton<Configurator>;

public:
	std::vector<Option> getOptions() const;

private:
	Configurator();
};

#endif //CONFIGURATOR__H
