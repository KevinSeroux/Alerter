#include "Acquiring/RemoteVideoStreamAcquirer.h"
#include <Configurator.h>
#include <iostream>

using namespace acquiring;

RemoteVideoStreamAcquirer::RemoteVideoStreamAcquirer()
{
	std::string str("undefined");
	Configurator::getInstance()["StreamLocation"] = str;
}

void RemoteVideoStreamAcquirer::getImage()
{

}

void RemoteVideoStreamAcquirer::run()
{
    std::cout << typeid(this).name() << " Hello!" << std::endl;
}
