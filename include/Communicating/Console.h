#ifndef CONSOLE__H
#define CONSOLE__H

#include "Interfaces/IOInt.h"

namespace communicating
{
	// Anticipated declaration to avoid cyclic inclusions
	class LanguageInt;

    class Console : public IOInt
    {
	public:
		Console(LanguageInt&);
        void receive();
        void send();
    };
}

#endif // CONSOLE__H
