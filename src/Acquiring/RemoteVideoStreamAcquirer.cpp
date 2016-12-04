#include "Acquiring/RemoteVideoStreamAcquirer.h"
#include <Configurator.h>
#include <iostream>

using namespace acquiring;
using namespace std::chrono_literals;

RemoteVideoStreamAcquirer::RemoteVideoStreamAcquirer()
{
	Configurator::getInstance().put("StreamLocation", "undefined");
	Configurator::getInstance().put("FrameRate", 23.976f);
}

void RemoteVideoStreamAcquirer::getImage()
{

}

void RemoteVideoStreamAcquirer::run()
{
	std::cout << typeid(this).name() << " Hello!" << std::endl;

	while(true)
	{
		//Do things

		//Wait
		int framePause = 1000.f /
			Configurator::getInstance().get<float>("FrameRate");
		std::cout << "Waiting " << framePause << " ms." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(framePause));
	}
}
