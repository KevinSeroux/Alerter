#ifndef LANGUAGE_INT__H
#define LANGUAGE_INT__H

#include <System/Configurator.h>
#include <string>

namespace communicating
{
	class LanguageInt
	{
	public:
		/* Parse the input and fill option. The parsed portion is removed from
		 * imput. If the method fails, it returns false, otherwise true. */
		virtual bool stringToOption(std::string& input, Option& option) = 0;

		/* Parse the input and fill cmd. The parsed portion is removed from
		* imput. If the method fails, it returns false, otherwise true. */
		virtual bool stringToCommand(std::string& input, std::string& cmd) = 0;

		virtual std::string optionsToString(const std::vector<Option>&) = 0;
	};
}

#endif // LANGUAGE_INT__H
