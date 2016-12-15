#ifndef OPENCV_PERFORMER__H
#define OPENCV_PERFORMER__H

#include "Interfaces/PerformerInt.h"
#include <opencv2/highgui.hpp>
#include <opencv2/gpu/gpu.hpp>
#include <vector>

namespace performing
{
	class OpenCVPerformer : public PerformerInt
	{
	public:
		OpenCVPerformer();
		cv::Mat BGR2Gray(const cv::Mat&) const;
		cv::Mat diff(const cv::Mat&, const cv::Mat&) const;
		cv::Mat or (const cv::Mat&, const cv::Mat&) const;
		cv::Mat threshold(const cv::Mat&, uint8_t) const;
		cv::Mat dilate(const cv::Mat&) const;
		std::vector<cv::Rect> boundingBoxes(const cv::Mat&) const;
		std::vector<cv::Rect> detectBodies(const cv::Mat&, float)	const;
		void drawRectangle(cv::Mat&, cv::Rect&, cv::Scalar&, int) const;
		void displayFrame(const char*, const cv::Mat&) const;

	private:
		cv::HOGDescriptor m_peopleDescriptor;
	};
}

#endif // OPENCV_PERFORMER__H
