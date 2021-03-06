#ifndef THREAD_H
#define THREAD_H

#include "Interfaces/WorkerInt.h"
#include <thread>

class Thread : public WorkerInt
{
public:
	Thread();
	virtual ~Thread();

	void start();
	void join();

protected:
	virtual void run() = 0;

private:
	std::thread m_thread;
};

#endif // THREAD_H
