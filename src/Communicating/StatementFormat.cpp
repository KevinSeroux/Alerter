#include "Communicating/StatementFormat.h"
#include <boost/lexical_cast.hpp>
#include <regex>

using namespace communicating;

bool StatementFormat::stringToCommand(std::string& str, std::string& cmd)
{
	static std::regex regexPattern(R"(^([^=\r\n]+)\r{0,1}\n)");

	std::smatch matches;
	bool retValue = false;

	if (std::regex_search(str, matches, regexPattern))
	{
		cmd = matches[1];
		str.erase(matches[0].first, matches[1].second);

		retValue = true;
	}

	return retValue;
}

bool StatementFormat::stringToOption(std::string& str, Option& option)
{
	static std::regex regexPattern(R"(^(\w+)\s*=\s*([^\r\n]+)\r{0,1}\n)");

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

std::string StatementFormat::optionsToString(const std::vector<Option>& opts)
{
	std::ostringstream out;

	for (Option opt : opts)
		out << opt.id << '=' << opt.data << std::endl;

	std::string str = out.str();
	str.pop_back(); // Remove the last trailing line feed

	return str;
}