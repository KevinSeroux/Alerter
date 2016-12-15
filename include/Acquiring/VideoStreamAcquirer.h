#ifndef VIDEO_STREAM_ACQUIRER
#define VIDEO_STREAM_ACQUIRER

#include <System/Thread.h>
#include <boost/circular_buffer.hpp>
#include <opencv2/core.hpp>
#include <mutex>

namespace acquiring
{
	class CannotFetchImage : public std::runtime_error {
	public:
		CannotFetchImage(const std::string msg) : runtime_error(msg) {}
	};

	class VideoStreamAcquirer : public Thread
	{
	public:
		cv::Mat getImage();

	protected:
		VideoStreamAcquirer();
		virtual cv::Mat fetchImage() = 0;

	private:
		void run();
		size_t queueSize();

		boost::circular_buffer<cv::Mat> m_imageQueue;
		std::mutex m_queueMutex, m_getImageMutex;
		std::condition_variable m_getImageCondVar;
	};
}

#endif // VIDEO_STREAM_ACQUIRER
