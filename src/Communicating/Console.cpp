#include "Communicating/Console.h"

using namespace communicating;

Console::Console(LanguageInt& impl) : IOInt(impl)
{

}

bool Console::receive(Option&)
{
	return false;
}

void Console::send(const std::string&)
{

}
