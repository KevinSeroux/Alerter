#ifndef REMOTE_VIDEO_STREAM_ACQUIRER
#define REMOTE_VIDEO_STREAM_ACQUIRER

#include "VideoStreamAcquirer.h"
#include <System/Thread.h>

namespace acquiring
{
	class RemoteVideoStreamAcquirer : public VideoStreamAcquirer
	{
	private:
		cv::Mat fetchImage();
	};
}

#endif // REMOTE_VIDEO_STREAM_ACQUIRER
