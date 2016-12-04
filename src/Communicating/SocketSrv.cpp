#include "Communicating/SocketSrv.h"
#include <Configurator.h>

using namespace communicating;

SocketSrv::SocketSrv(LanguageInt& lang) : IOInt(lang)
{
	m_socketSrvImpl.start();
}

SocketSrv::~SocketSrv()
{
	m_socketSrvImpl.join();
}

bool SocketSrv::receive(Option& option)
{
	std::string str;
	bool isParseDone = false;
	if(m_socketSrvImpl.receive(str))
	{
		// In fact, there is only one language implementation
		forEach([&isParseDone, &str, &option](auto lang) {
			isParseDone = lang->stringToOption(str, option);
		});
    }

	return isParseDone;
}

void SocketSrv::send(const std::string& data)
{
	m_socketSrvImpl.send(data);
}
