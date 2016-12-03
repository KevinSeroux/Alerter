#include "Communicating/Communicator.h"
#include <iostream>

using namespace communicating;
using namespace std::chrono_literals;

Communicator::Communicator()
{

}

void Communicator::run()
{
	std::cout << typeid(this).name() << " Hello!";

	while(true)
	{
		std::this_thread::sleep_for(1s);
	}
}
