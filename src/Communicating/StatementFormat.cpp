#include "Communicating/StatementFormat.h"
#include <boost/lexical_cast.hpp>
#include <regex>

using namespace communicating;

bool StatementFormat::stringToOption(std::string& str, Option& option)
{
	static std::regex regexPattern(R"(^(\w+)\s*=\s*([^\n]+)\n)");

	std::smatch matches;
	bool retValue = false;

	if(std::regex_search(str, matches, regexPattern))
	{
		option.id = matches[1];
		option.data = matches[2];

		str.erase(matches[0].first, matches[0].second);

		retValue = true;
	}

	return retValue;
}
