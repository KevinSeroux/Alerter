#include "Communicating/Communicator.h"
#include <iostream>

using namespace communicating;

Communicator::Communicator()
{

}

void Communicator::run()
{
	std::cout << typeid(this).name() << " Hello!";
	OptionCommand optCmd;

	while(true)
	{
		forEachImpl([&optCmd, this](auto impl)
		{
			if (impl->receive(optCmd))
			{
				if(optCmd.which() == COMMAND)
					handleCommand(*impl, boost::get<std::string>(optCmd));
				else if (optCmd.which() == OPTION)
					handleOption(*impl, boost::get<Option>(optCmd));
			}
		});

		//Wait
		float frameRate = Configurator::getInstance().get<float>("FrameRate");
		int framePeriod = static_cast<int>(ceil(1000.f / frameRate));
		int pause = std::max(1, framePeriod);
		std::this_thread::sleep_for(std::chrono::milliseconds(pause));
	}
}

void Communicator::handleCommand(IOInt& impl, const std::string& cmd)
{
	if (strcmp(cmd.c_str(), "show vars") == 0)
		impl.send(Configurator::getInstance().getOptions());
	else
	{
		std::string msg = std::string("Unknown command: ") + cmd;
		impl.send(msg);
	}
}

void Communicator::handleOption(IOInt& impl, const Option& opt)
{
	Configurator& c = Configurator::getInstance();

	auto it = c.find(opt.id);
	if (it == c.not_found())
	{
		std::string msg = std::string("Unknown option: ") + opt.id;
		impl.send(msg);
	}
	else
		c.put(opt.id, opt.data);
}