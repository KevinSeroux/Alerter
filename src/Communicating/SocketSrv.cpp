#include "Communicating/SocketSrv.h"
#include <System/Configurator.h>

using namespace communicating;

SocketSrv::SocketSrv(LanguageInt& lang) : IOInt(lang)
{
	m_socketSrvImpl.start();
}

SocketSrv::~SocketSrv()
{
	m_socketSrvImpl.exit();
	m_socketSrvImpl.join();
}

bool SocketSrv::receive(Option& option)
{
	std::string str;
	bool isParseDone = false;
	if(m_socketSrvImpl.receive(str))
	{
		implDo([&isParseDone, &str, &option](auto lang) {
			isParseDone = lang->stringToOption(str, option);
		});
    }

	return isParseDone;
}

void SocketSrv::send(const std::string& data)
{
	m_socketSrvImpl.send(data);
}
