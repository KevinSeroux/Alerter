#ifndef COMMUNICATOR__H
#define COMMUNICATOR__H

#include <System/Thread.h>
#include "Interfaces/IOInt.h"
#include <opencv2/core.hpp>
#include <mutex>

namespace communicating
{
	class Communicator : public Thread
	{
	public:
		Communicator(IOInt&);
		void sendImage(const std::string&, const cv::Mat&);
		void send(const std::string&);

	private:
		void run();
		void handleCommand(const std::string&);
		void handleOption(const Option&);

		IOInt& m_ioImpl;
	};
}

#endif // COMMUNICATOR__H
