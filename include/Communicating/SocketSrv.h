#ifndef SOCKET_SRV__H
#define SOCKET_SRV__H

#include "Interfaces/IOInt.h"
#include "BoostSocketSrv.h"
#include <boost/asio.hpp>

namespace communicating
{
	// Anticipated declarations to avoid cyclic inclusions
	class LanguageInt;

	class SocketSrv : public IOInt
	{
	public:
		SocketSrv(LanguageInt&);
		~SocketSrv();
		bool receive(OptionCommand&);
		void send(const std::string&);
		void send(const std::vector<Option>&);

	private:
		BoostSocketSrv m_socketSrvImpl;
	};
}

#endif // SOCKET_SRV__H
