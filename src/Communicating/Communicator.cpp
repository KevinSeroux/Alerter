#include "Communicating/Communicator.h"
#include <iostream>

using namespace communicating;

Communicator::Communicator()
{

}

void Communicator::run()
{
	std::cout << typeid(this).name() << " Hello!";

	Configurator& c = Configurator::getInstance();
	Option opt;
	while(true)
	{
		//Do things
		forEach([&opt, &c](auto impl)
		{
			if(impl->receive(opt))
			{
				auto it = c.find(opt.id);
				if(it == c.not_found())
				{
					std::cerr << "Remote client tried to change an " <<
						"unregistered value: \"" << opt.id << "\"."
						<< std::endl;
				}
				else
					c.put(opt.id, opt.data);
			}
		});

		//Wait		
		int framePause = 1000.f / c.get<float>("FrameRate");
		std::this_thread::sleep_for(std::chrono::milliseconds(framePause));
	}
}
