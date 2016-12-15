#ifndef COMMUNICATOR__H
#define COMMUNICATOR__H

#include <System/Thread.h>
#include "Interfaces/IOInt.h"
#include <mutex>

namespace communicating
{
	class Communicator : public Thread
	{
	public:
		Communicator(IOInt&);
		void handleCommand(const std::string&);
		void handleOption(const Option&);

	private:
		void run();

		IOInt& m_ioImpl;
	};
}

#endif // COMMUNICATOR__H
