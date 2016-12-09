#include "Acquiring/LocalVideoStreamAcquirer.h"
#include <System/Configurator.h>
#include <iostream>

using namespace acquiring;
using namespace std::chrono_literals;
using namespace cv;
using namespace std;

LocalVideoStreamAcquirer::LocalVideoStreamAcquirer(int device) :
	m_videoCapture(device)
{
	if(!m_videoCapture.isOpened())
		throw DeviceNotFound("Cannot open the device");

	setUpSharedVars();
}

LocalVideoStreamAcquirer::LocalVideoStreamAcquirer(const char* file) :
	m_videoCapture(file)
{
	if(!m_videoCapture.isOpened())
		throw FileNotFound("Cannot open the file");

	setUpSharedVars();
}

void LocalVideoStreamAcquirer::setUpSharedVars()
{
	Configurator::getInstance().put("StreamLocation", "undefined");
	Configurator::getInstance().put("FrameRate", 23.976f);
}

Mat LocalVideoStreamAcquirer::getImage()
{
	Mat image;

	// Wait while the queue is empty
	while (queueSize() == 0)
	{
		unique_lock<mutex> lck(m_getImageMutex);
		m_getImageCondVar.wait(lck);
	}

	{ // Critical section
		unique_lock<mutex> lck(m_queueMutex);
		image = m_imageQueue.front();
		m_imageQueue.pop_front();
	}

	return image;
}

void LocalVideoStreamAcquirer::run()
{
	Configurator& c = Configurator::getInstance();

	std::cout << typeid(this).name() << " Hello!" << std::endl;

	while (true)
	{
		//Change the buffer capacity each time the persistant images
		size_t queueSizeMax = c.get<size_t>("CountPersistantImages");
		{ // Critical section
			unique_lock<mutex> lck(m_queueMutex);
			m_imageQueue.set_capacity(queueSizeMax);
		}

		Mat frame;
		m_videoCapture >> frame;

		// Play again when it's finished
		if (frame.empty())
		{
			m_videoCapture.set(CV_CAP_PROP_POS_AVI_RATIO, 0);
			continue;
		}

		{ // Critical section
			unique_lock<mutex> lck(m_queueMutex);
			m_imageQueue.push_back(frame);
		}
		
		// One image added, wake up the consumer (getImage())
		m_getImageCondVar.notify_one();

		float frameRate = c.get<float>("FrameRate");
		int framePeriod = static_cast<int>(ceil(1000.f / frameRate));
		framePeriod = std::max(1, framePeriod);
		std::this_thread::sleep_for(std::chrono::milliseconds(framePeriod));
	}
}

size_t LocalVideoStreamAcquirer::queueSize()
{
	unique_lock<mutex> lck(m_queueMutex);
	return m_imageQueue.size();
}