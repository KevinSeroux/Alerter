#ifndef LOCAL_VIDEO_STREAM_ACQUIRER
#define LOCAL_VIDEO_STREAM_ACQUIRER

#include "Interfaces/VideoStreamAcquirerInt.h"
#include <System/Thread.h>
#include <opencv2/highgui.hpp>
#include <boost/circular_buffer.hpp>
#include <mutex>
#include <condition_variable>

namespace acquiring
{
	class FileNotFound : public std::runtime_error {
	public:
		FileNotFound(const char* msg) : runtime_error(msg) {}
	};

	class DeviceNotFound : public std::runtime_error {
	public:
		DeviceNotFound(const char* msg) : runtime_error(msg) {}
	};

	class LocalVideoStreamAcquirer :
		public VideoStreamAcquirerInt, public Thread
	{
	public:
		LocalVideoStreamAcquirer(int dev = 0);
		LocalVideoStreamAcquirer(const char*);
		cv::Mat getImage();

	private:
		void setUpSharedVars();
		void run();
		size_t queueSize();

		cv::VideoCapture m_videoCapture;
		boost::circular_buffer<cv::Mat> m_imageQueue;
		std::mutex m_queueMutex, m_getImageMutex;
		std::condition_variable m_getImageCondVar;
	};
}

#endif // FILE_VIDEO_STREAM_ACQUIRER