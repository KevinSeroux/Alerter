#include "Acquiring/RemoteVideoStreamAcquirer.h"
#include <Configurator.h>
#include <iostream>

using namespace acquiring;

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
}
