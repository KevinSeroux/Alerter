#ifndef STATEMENT_FORMAT__H
#define STATEMENT_FORMAT__H

#include "Interfaces/LanguageInt.h"
#include <string>

namespace communicating
{
	class StatementFormat : public LanguageInt
	{
		bool translateObject(std::string&, Option&);
	};
}

#endif // STATEMENT_FORMAT__H
