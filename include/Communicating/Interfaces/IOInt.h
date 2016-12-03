#ifndef IO_INT__H
#define IO_INT__H

#include <DependencyInjector.h>
#include "LanguageInt.h"
#include <Configurator.h>
#include <string>

namespace communicating
{
    class IOInt : protected DependencyInjector<LanguageInt>
    {
    public:
		IOInt(LanguageInt&);
		virtual ~IOInt() = 0;

        virtual bool receive(Option&) = 0;
        virtual void send(const std::string&) = 0;
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
