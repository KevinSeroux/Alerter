#ifndef LOCAL_VIDEO_STREAM_ACQUIRER__H
#define LOCAL_VIDEO_STREAM_ACQUIRER__H

#include "VideoStreamAcquirer.h"
#include <System/Thread.h>
#include <System/Configurator.h>
#include <opencv2/highgui.hpp>
#include <boost/circular_buffer.hpp>
#include <mutex>
#include <condition_variable>

namespace acquiring
{
	class LocalVideoStreamAcquirer : public VideoStreamAcquirer
	{
	public:
		LocalVideoStreamAcquirer();

	private:
		cv::Mat fetchImage();
		void handleStreamLocationChange();

		Configurator& m_config;
		std::string m_currentStreamLoc;
		cv::VideoCapture m_videoCapture;
	};
}

#endif // FILE_VIDEO_STREAM_ACQUIRER__H