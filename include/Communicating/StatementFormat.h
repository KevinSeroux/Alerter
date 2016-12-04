#ifndef STATEMENT_FORMAT__H
#define STATEMENT_FORMAT__H

#include "Interfaces/LanguageInt.h"
#include <string>

namespace communicating
{
	class StatementFormat : public LanguageInt
	{
	public:
		bool stringToOption(std::string&, Option&);
	};
}

#endif // STATEMENT_FORMAT__H
