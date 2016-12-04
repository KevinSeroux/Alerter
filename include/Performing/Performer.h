#ifndef PERFORMER__H
#define PERFORMER__H

#include <System/Thread.h>
#include <System/DependencyInjector.h>
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
