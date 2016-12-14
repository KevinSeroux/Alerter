#ifndef LOCAL_VIDEO_STREAM_ACQUIRER
#define LOCAL_VIDEO_STREAM_ACQUIRER

#include "VideoStreamAcquirer.h"
#include <System/Thread.h>
#include <opencv2/highgui.hpp>
#include <boost/circular_buffer.hpp>
#include <mutex>
#include <condition_variable>

namespace acquiring
{
	class FileNotFound : public std::runtime_error {
	public:
		FileNotFound(const std::string msg) : runtime_error(msg) {}
	};

	class DeviceNotFound : public std::runtime_error {
	public:
		DeviceNotFound(const std::string msg) : runtime_error(msg) {}
	};

	class LocalVideoStreamAcquirer : public VideoStreamAcquirer
	{
	public:
		LocalVideoStreamAcquirer(int dev = 0);
		LocalVideoStreamAcquirer(const char*);

	private:
		cv::Mat fetchImage();

		cv::VideoCapture m_videoCapture;
	};
}

#endif // FILE_VIDEO_STREAM_ACQUIRER