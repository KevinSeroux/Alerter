#include <Acquiring/VideoStreamAcquirer.h>
#include <System/Configurator.h>
#include <iostream>

using namespace acquiring;
using namespace cv;
using namespace std;

VideoStreamAcquirer::VideoStreamAcquirer()
{
	Configurator::getInstance().put("StreamLocation", "undefined");
	Configurator::getInstance().put("FrameRate", 24);
}

Mat VideoStreamAcquirer::getImage()
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

void VideoStreamAcquirer::run()
{
	Configurator& c = Configurator::getInstance();

	cout << typeid(this).name() << " Hello!" << endl;

	while (true)
	{
		//Change the buffer capacity each time the persistant images
		size_t queueSizeMax = c.get<size_t>("CountPersistantImages");
		{ // Critical section
			unique_lock<mutex> lck(m_queueMutex);
			m_imageQueue.set_capacity(queueSizeMax);
		}

		Mat frame = fetchImage();

		{ // Critical section
			unique_lock<mutex> lck(m_queueMutex);
			m_imageQueue.push_back(frame);
		}

		// One image added, wake up the consumer (getImage())
		m_getImageCondVar.notify_one();

		float frameRate = c.get<float>("FrameRate");
		int framePeriod = static_cast<int>(ceil(1000.f / frameRate));
		framePeriod = max(1, framePeriod);
		this_thread::sleep_for(chrono::milliseconds(framePeriod));
	}
}

size_t VideoStreamAcquirer::queueSize()
{
	unique_lock<mutex> lck(m_queueMutex);
	return m_imageQueue.size();
}