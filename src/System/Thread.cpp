#include <System/Thread.h>

Thread::Thread()
{

}

Thread::~Thread()
{

}

void Thread::start()
{
	m_thread = std::thread(&Thread::run, this);
}

void Thread::join()
{
	m_thread.join();
}
