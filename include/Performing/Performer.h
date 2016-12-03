#ifndef PERFORMER__H
#define PERFORMER__H

#include <Thread.h>
#include <DependencyInjector.h>
#include "Interfaces/PerformerInt.h"

namespace performing
{
	class Performer : public Thread, private DependencyInjector<PerformerInt>
	{
	public:
		Performer(PerformerInt&);
		void run();
	};
}

#endif // PERFORMER__H
