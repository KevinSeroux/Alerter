#ifndef CONSOLE__H
#define CONSOLE__H

#include "Interfaces/IOInt.h"
#include <Configurator.h>
#include <string>

namespace communicating
{
	// Anticipated declaration to avoid cyclic inclusions
	class LanguageInt;

    class Console : public IOInt
    {
	public:
		Console(LanguageInt&);
        bool receive(Option&);
        void send(const std::string&);
    };
}

#endif // CONSOLE__H
