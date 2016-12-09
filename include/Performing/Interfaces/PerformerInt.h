#ifndef PERFORMER_INT__H
#define PERFORMER_INT__H

#include <opencv2/core.hpp>

namespace performing
{
	class PerformerInt
	{
	public:
		virtual cv::Mat BGR2Gray(const cv::Mat&) const = 0;
		virtual cv::Mat diff(const cv::Mat&, const cv::Mat&) const = 0;
		virtual cv::Mat or(const cv::Mat&, const cv::Mat&) const = 0;
		virtual cv::Mat threshold(const cv::Mat&, uint8_t) const = 0;
		virtual cv::Mat dilate(const cv::Mat&) const = 0;
		virtual std::vector<cv::Rect> boundingBoxes(const cv::Mat&) const = 0;
		virtual std::vector<cv::Rect> detectBodies(const cv::Mat&, float)
			const = 0;
		virtual void displayFrame(const char*, const cv::Mat&) const = 0;
		virtual void drawRectangle(cv::Mat&, cv::Rect&, cv::Scalar&, int)
			const = 0;
	};
}

#endif // PERFORMER_INT__H
