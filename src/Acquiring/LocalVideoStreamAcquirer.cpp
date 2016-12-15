#include "Acquiring/LocalVideoStreamAcquirer.h"
#include <System/Configurator.h>
#include <iostream>

using namespace acquiring;
using namespace std::chrono_literals;
using namespace cv;
using namespace std;

LocalVideoStreamAcquirer::LocalVideoStreamAcquirer() :
	m_config(Configurator::getInstance())
{
	try { handleStreamLocationChange(); }
	catch (const CannotFetchImage&) {}
}

Mat LocalVideoStreamAcquirer::fetchImage()
{
	handleStreamLocationChange();

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

void LocalVideoStreamAcquirer::handleStreamLocationChange()
{
	std::string newStreamLoc = m_config.get<std::string>("StreamLocation");
	if (m_currentStreamLoc.compare(newStreamLoc) != 0) // 0 = no change
	{
		m_currentStreamLoc = newStreamLoc;
		m_videoCapture.open(m_currentStreamLoc);
	}

	if(!m_videoCapture.isOpened())
	{
		std::string msg = "Following file not found: ";
		msg += m_currentStreamLoc;

		throw CannotFetchImage(msg);
	}
}