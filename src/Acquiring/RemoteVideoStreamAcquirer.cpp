#include "Acquiring/RemoteVideoStreamAcquirer.h"
#include <iostream>

using namespace acquiring;

void RemoteVideoStreamAcquirer::getImage()
{

}

void RemoteVideoStreamAcquirer::run()
{
    std::cout << typeid(this).name() << " Hello!" << std::endl;
}
