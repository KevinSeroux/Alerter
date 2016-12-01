#ifndef VIDEO_STREAM_ACQUIRER_INT
#define VIDEO_STREAM_ACQUIRER_INT

namespace acquiring
{
    class VideoStreamAcquirerInt
    {
    public:
        virtual void getImage() = 0;
    };
}

#endif // VIDEO_STREAM_ACQUIRER_INT
