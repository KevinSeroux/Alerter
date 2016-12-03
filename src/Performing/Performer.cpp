#include "Performing/Performer.h"
#include <iostream>
#include <thread>

using namespace performing;
using namespace std::chrono_literals;

Performer::Performer(PerformerInt& impl)
{
	addImpl(impl);
}

void Performer::run()
{
	std::cout << typeid(this).name() << " Hello!" << std::endl;

	while(true)
	{
		std::this_thread::sleep_for(1s);
	}
}
