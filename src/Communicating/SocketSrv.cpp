#include "Communicating/SocketSrv.h"
#include <System/Configurator.h>
#include <regex>

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

bool SocketSrv::receive(OptionCommand& optCmd)
{
	std::string str;
	bool isParseDone = false;

	if(m_socketSrvImpl.receive(str))
	{
		std::string cmd;
		Option opt;

		isParseDone = m_lang.stringToOption(str, opt);
		if (isParseDone)
			optCmd = opt;
		else
		{
			isParseDone = m_lang.stringToCommand(str, cmd);
			if (isParseDone)
				optCmd = cmd;
		}
    }

	return isParseDone;
}

void SocketSrv::send(const std::string& data)
{
	const std::string msg = std::string("> ") + data + "\r\n";
	m_socketSrvImpl.send(msg);
}

void SocketSrv::send(const std::vector<Option>& opts)
{
	static std::regex regExp(R"(\n)"); //Regex to append the "> "

	std::string str = "> ";
	str += m_lang.optionsToString(opts);
	str = std::regex_replace(str, regExp, "\r\n> ");
	str += "\r\n";

	m_socketSrvImpl.send(str);
}
