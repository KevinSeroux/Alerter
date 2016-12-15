#ifndef STATEMENT_FORMAT__H
#define STATEMENT_FORMAT__H

#include "Interfaces/LanguageInt.h"
#include <string>

namespace communicating
{
	class StatementFormat : public LanguageInt
	{
	public:
		bool stringToCommand(std::string&, std::string&);
		bool stringToOption(std::string&, Option&);
		std::string optionsToString(const std::vector<Option>&);
	};
}

#endif // STATEMENT_FORMAT__H
