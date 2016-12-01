#include "Communicating/Communicator.h"
#include <iostream>

using namespace communicating;

Communicator::Communicator()
{

}

void Communicator::run()
{
    std::cout << typeid(this).name() << " Hello!";
}
