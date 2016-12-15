#ifndef IO_INT__H
#define IO_INT__H

#include <System/DependencyInjector.h>
#include "LanguageInt.h"
#include <System/Configurator.h>
#include <string>
#include <boost/variant.hpp>

namespace communicating
{
	enum { COMMAND, OPTION }; // COMMAND = 0 => std::string bellow
	typedef boost::variant<std::string, Option> OptionCommand;

	class IOInt : protected DependencyInjector<LanguageInt>
	{
	public:
		IOInt(LanguageInt&);
		virtual ~IOInt() = 0;

		virtual bool receive(OptionCommand&) = 0;
		virtual void send(const std::string&) = 0;
		virtual void send(const std::vector<Option>&) = 0;
	};

	inline IOInt::IOInt(LanguageInt& lang)
	{
		addImpl(lang);
	}

	inline IOInt::~IOInt()
	{

	}
}

#endif // IO_INT__H
