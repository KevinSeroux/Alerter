#ifndef IO_INT__H
#define IO_INT__H

#include "LanguageInt.h"
#include <System/Configurator.h>
#include <string>
#include <boost/variant.hpp>

namespace communicating
{
	enum { COMMAND, OPTION }; // COMMAND = 0 => std::string below
	typedef boost::variant<std::string, Option> OptionCommand;

	class IOInt
	{
	public:
		IOInt(LanguageInt& lang) : m_lang(lang) {}
		virtual ~IOInt() = 0 {}

		virtual bool receive(OptionCommand&) = 0;
		virtual void send(const std::string&) = 0;
		virtual void send(const std::vector<Option>&) = 0;

	protected:
		LanguageInt& m_lang;
	};
}

#endif // IO_INT__H
