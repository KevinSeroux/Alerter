#ifndef WORKER_INT__H
#define WORKER_INT__H

class WorkerInt
{
public:
	virtual void start() = 0;

private:
	virtual void run() = 0;
};

#endif // WORKER_INT__H
