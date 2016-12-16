#include "Communicating/Communicator.h"
#include <opencv2/core.hpp>
#include <iostream>

using namespace communicating;

Communicator::Communicator(IOInt& impl) : m_ioImpl(impl)
{

}

void Communicator::run()
{
	std::cout << typeid(this).name() << " Hello!";
	OptionCommand optCmd;

	while(true)
	{
		if (m_ioImpl.receive(optCmd))
		{
			if(optCmd.which() == COMMAND)
				handleCommand(boost::get<std::string>(optCmd));
			else if (optCmd.which() == OPTION)
				handleOption(boost::get<Option>(optCmd));
		}

		//Wait
		float frameRate = Configurator::getInstance().get<float>("FrameRate");
		int framePeriod = static_cast<int>(ceil(1000.f / frameRate));
		int pause = std::max(1, framePeriod);
		std::this_thread::sleep_for(std::chrono::milliseconds(pause));
	}
}

void Communicator::handleCommand(const std::string& cmd)
{
	if (strcmp(cmd.c_str(), "show vars") == 0)
		m_ioImpl.send(Configurator::getInstance().getOptions());
	else
	{
		std::string msg = std::string("Unknown command: ") + cmd;
		m_ioImpl.send(msg);
	}
}

void Communicator::handleOption(const Option& opt)
{
	Configurator& c = Configurator::getInstance();

	auto it = c.find(opt.id);
	if (it == c.not_found())
	{
		std::string msg = std::string("Unknown option: ") + opt.id;
		m_ioImpl.send(msg);
	}
	else
		c.put(opt.id, opt.data);
}

void Communicator::sendImage(const std::string& desc, const cv::Mat& img)
{
	std::ostringstream oss;

	// To have all the data on one row (continuous)
	//cv::Mat transferrableMat = img.reshape(0, 1);
	oss << "img " << desc << ' '
		<< img.type() << ' '
		<< img.dims << ' '
		<< img.cols << 'x' << img.rows << ' '
		<< img.data << '\0';

	std::string msg = oss.str();
	m_ioImpl.send(msg);
}

void Communicator::send(const std::string& msg)
{
	m_ioImpl.send(msg);
}