#ifndef IO_INT__H
#define IO_INT__H

#include <DependencyInjector.h>
#include "LanguageInt.h"

namespace communicating
{
    class IOInt : private DependencyInjector<LanguageInt>
    {
    public:
		IOInt(LanguageInt&);
		virtual ~IOInt() = 0;

        virtual void receive() = 0;
        virtual void send() = 0;
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
