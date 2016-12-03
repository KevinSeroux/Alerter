#include "Acquiring/RemoteVideoStreamAcquirer.h"
#include <Configurator.h>
#include <iostream>

using namespace acquiring;
using namespace std::chrono_literals;

RemoteVideoStreamAcquirer::RemoteVideoStreamAcquirer()
{
	Configurator::getInstance()("StreamLocation", true) = "undefined";
}

void RemoteVideoStreamAcquirer::getImage()
{

}

void RemoteVideoStreamAcquirer::run()
{
	std::cout << typeid(this).name() << " Hello!" << std::endl;

	while(true)
	{
		std::this_thread::sleep_for(1s);
	}
}
