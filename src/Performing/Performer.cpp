#include "Performing/Performer.h"
#include <iostream>

using namespace performing;

Performer::Performer(PerformerInt& impl)
{
	addImpl(impl);
}

void Performer::run()
{
    std::cout << typeid(this).name() << " Hello!" << std::endl;
}
