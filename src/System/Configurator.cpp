#include <System/Configurator.h>
#include <boost/property_tree/json_parser.hpp>

using namespace std;

Configurator::Configurator() {}

std::vector<Option> Configurator::getOptions() const
{
	std::vector<Option> list;

	for (auto it : *this)
	{
		Option opt;
		opt.id = it.first;
		opt.data = it.second.data();
		list.push_back(opt);
	}

	return list;
}