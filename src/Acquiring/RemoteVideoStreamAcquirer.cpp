#include "Acquiring/RemoteVideoStreamAcquirer.h"
#include <System/Configurator.h>
#include <iostream>

using namespace acquiring;
using namespace std::chrono_literals;
using namespace cv;

RemoteVideoStreamAcquirer::RemoteVideoStreamAcquirer()
{
	Configurator::getInstance().put("StreamLocation", "undefined");
	Configurator::getInstance().put("FrameRate", 23.976f);
}

Mat RemoteVideoStreamAcquirer::getImage()
{
	return Mat();
}

void RemoteVideoStreamAcquirer::run()
{
	std::cout << typeid(this).name() << " Hello!" << std::endl;

	while(true)
	{
		//Do things

		//Wait
		float frameRate = Configurator::getInstance().get<float>("FrameRate");
		int framePeriod = static_cast<int>(ceil(1000.f / frameRate));
		int pause = std::max(1, framePeriod);
		std::cout << "Waiting " << pause << " ms." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(pause));
	}
}
