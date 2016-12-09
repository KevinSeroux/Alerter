#include <System/Configurator.h>
#include <boost/property_tree/json_parser.hpp>

using namespace std;

Configurator::Configurator() {}

string Configurator::toJSON() const
{
	ostringstream oss;
	boost::property_tree::write_json(oss, *this);

	return oss.str();
}