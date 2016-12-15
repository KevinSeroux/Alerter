#include "Performing/OpenCVPerformer.h"
#include <System/Configurator.h>

using namespace performing;
using namespace cv;

OpenCVPerformer::OpenCVPerformer()
{
	vector<float> peopleSVMDetector = HOGDescriptor::getDefaultPeopleDetector();
	m_peopleDescriptor.setSVMDetector(peopleSVMDetector);
}

Mat OpenCVPerformer::BGR2Gray(const Mat& source) const
{
	Mat ret;
	cvtColor(source, ret, CV_BGR2GRAY);

	return ret;
}

Mat OpenCVPerformer::diff(const Mat& src1, const Mat& src2) const
{
	Mat ret;
	absdiff(src1, src2, ret);

	return ret;
}

Mat OpenCVPerformer::or(const Mat& src1, const Mat& src2) const
{
	Mat ret;
	bitwise_or(src1, src2, ret);

	return ret;
}

Mat OpenCVPerformer::threshold(const Mat& src, uint8_t thresholdFactor) const
{
	Mat ret;
	cv::threshold(src, ret, thresholdFactor, 255, THRESH_BINARY);

	return ret;
}

Mat OpenCVPerformer::dilate(const Mat& src) const
{
	Mat ret, kernel;

	kernel = getStructuringElement(MORPH_RECT, Size(5, 5));
	cv::dilate(src, ret, kernel, Point(-1, -1), 2);

	return ret;
}

vector<Rect> OpenCVPerformer::boundingBoxes(const Mat& src) const
{
	vector<vector<Point>> shapes;
	findContours(src, shapes, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	vector<Rect> bounds;

	for (auto s : shapes)
	{
		if (contourArea(s) >= 1000)
		{
			Rect bound = boundingRect(s);
			bounds.push_back(bound);
		}
	}

	return bounds;
}

vector<Rect> OpenCVPerformer::detectBodies(const cv::Mat& frame,
	float sensitivity) const
{
	vector<Rect> foundLocations;
	m_peopleDescriptor.detectMultiScale(frame, foundLocations, sensitivity,
		Size(8, 8), Size(32, 64), 1.05, 2);

	return foundLocations;
}

void OpenCVPerformer::drawRectangle(cv::Mat& frame, Rect& rect, Scalar& color,
	int thickness) const
{
	cv::rectangle(frame, rect, color, thickness);
}

void OpenCVPerformer::displayFrame(const char* desc, const Mat& src) const
{
	Mat resizedFrame;

	float ratio = (float)src.cols / src.rows;
	resize(src, resizedFrame, Size(static_cast<int>(300 * ratio), 300));
	imshow(desc, resizedFrame);
	waitKey(1); // To update the windows
}
