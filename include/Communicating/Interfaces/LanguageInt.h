#ifndef LANGUAGE_INT__H
#define LANGUAGE_INT__H

#include <OptionTypedData.h>
#include <Configurator.h>
#include <string>

namespace communicating
{
    class LanguageInt
    {
    public:
		/* Parse the input and fill option. The parsed portion is removed from
		 * imput. If the method fails, it returns false, otherwise true. */
        virtual bool translateObject(std::string& input, Option& option) = 0;
    };
}

#endif // LANGUAGE_INT__H
