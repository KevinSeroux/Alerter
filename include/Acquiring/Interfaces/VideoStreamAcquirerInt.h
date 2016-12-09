#ifndef VIDEO_STREAM_ACQUIRER_INT
#define VIDEO_STREAM_ACQUIRER_INT

#include <opencv2/core.hpp>

namespace acquiring
{
	class VideoStreamAcquirerInt
	{
	public:
		virtual cv::Mat getImage() = 0;
	};
}

#endif // VIDEO_STREAM_ACQUIRER_INT
