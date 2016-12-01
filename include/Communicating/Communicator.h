#ifndef COMMUNICATOR__H
#define COMMUNICATOR__H

#include <Thread.h>
#include <DependencyInjector.h>
#include "Interfaces/IOInt.h"
#include <mutex>

namespace communicating
{
    class Communicator : public Thread, public DependencyInjector<IOInt>
    {
    public:
        Communicator();

    private:
        void run();
    };
}

#endif // COMMUNICATOR__H
