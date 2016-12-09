#ifndef REMOTE_VIDEO_STREAM_ACQUIRER
#define REMOTE_VIDEO_STREAM_ACQUIRER

#include "Interfaces/VideoStreamAcquirerInt.h"
#include <System/Thread.h>

namespace acquiring
{
	class RemoteVideoStreamAcquirer :
	public VideoStreamAcquirerInt, public Thread
	{
	public:
		RemoteVideoStreamAcquirer();
		cv::Mat getImage();

	private:
		void run();
	};
}

#endif // REMOTE_VIDEO_STREAM_ACQUIRER
