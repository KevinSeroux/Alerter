#ifndef SOCKET_SRV__H
#define SOCKET_SRV__H

#include "Interfaces/IOInt.h"

namespace communicating
{
	// Anticipated declarations to avoid cyclic inclusions
	class LanguageInt;

    class SocketSrv : public IOInt
    {
	public:
		SocketSrv(LanguageInt&);
        void receive();
        void send();
    };
}

#endif // SOCKET_SRV__H
