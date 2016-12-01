#ifndef REMOTE_VIDEO_STREAM_ACQUIRER
#define REMOTE_VIDEO_STREAM_ACQUIRER

#include "Interfaces/VideoStreamAcquirerInt.h"
#include "Thread.h"

namespace acquiring
{
    class RemoteVideoStreamAcquirer : public VideoStreamAcquirerInt, public Thread
    {
    public:
        void getImage();

    private:
        void run();
    };
}

#endif // REMOTE_VIDEO_STREAM_ACQUIRER
