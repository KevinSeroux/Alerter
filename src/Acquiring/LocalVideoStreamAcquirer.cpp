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
	if (!m_videoCapture.isOpened())
	{
		string msg = "Cannot open the device " + to_string(device);
		throw DeviceNotFound(msg);
	}
}

LocalVideoStreamAcquirer::LocalVideoStreamAcquirer(const char* file) :
	m_videoCapture(file)
{
	if (!m_videoCapture.isOpened())
	{
		string msg = "Cannot open the file " + string(file);
		throw FileNotFound(msg);
	}
}

Mat LocalVideoStreamAcquirer::fetchImage()
{
	Mat frame;
	m_videoCapture >> frame;

	// Play again when it's finished
	if (frame.empty())
	{
		m_videoCapture.set(CV_CAP_PROP_POS_AVI_RATIO, 0);
		m_videoCapture >> frame;
	}

	return frame;
}