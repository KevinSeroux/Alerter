#include "Performing/Performer.h"
#include <System/Configurator.h>
#include <iostream>
#include <thread>

using namespace performing;
using namespace acquiring;
using namespace std::chrono_literals;
using namespace cv;
using namespace std;

Performer::Performer(PerformerInt& impl, VideoStreamAcquirer& acq)
{
	addImpl(impl);
	m_acq = &acq;

	m_configurator = &Configurator::getInstance();
	m_configurator->put("CountPersistantImages", 12);
	m_configurator->put("MotionThreshold", 75);
	m_configurator->put("BodyDetectionPass", true);
	m_configurator->put("BodyDetectionSensitivity", 1);
	m_configurator->put("Debug", true);
}

void Performer::run()
{
	std::cout << typeid(this).name() << " Hello!" << std::endl;

	while(true)
	{
		auto startTime = chrono::system_clock::now().time_since_epoch() /
			chrono::milliseconds(1);

		Mat RGBFrame;
		vector<Mat> persistantFrames = getPersistantFrames(RGBFrame);
		vector<Rect> changesLocation = findMotion(persistantFrames);

		for (auto c : changesLocation)
		{
			implDo([&RGBFrame, &c](auto impl) {
				impl->drawRectangle(RGBFrame, c, Scalar(255, 0, 0), 3);
			});
		}

		if (m_configurator->get<bool>("Debug"))
			displayFrame("Frame", RGBFrame);

		if (m_configurator->get<bool>("BodyDetectionPass"))
		{
			for(Rect zone : changesLocation)
			{
				Mat subFrame = RGBFrame(zone);
				vector<Rect> humansLoc = findBodies(subFrame);
			}
		}

		auto endTime = chrono::system_clock::now().time_since_epoch() /
			chrono::milliseconds(1);

		if (m_configurator->get<bool>("Debug"))
			cout << "Performing time: " << endTime - startTime << "ms" << endl;
	}
}

vector<Rect> Performer::findMotion(vector<Mat>& persistantFrames)
{
	bool isDebug = m_configurator->get<bool>("Debug");

	Mat diffFrame = computeDiffFrame(persistantFrames);
	if (isDebug) displayFrame("Diff frame", diffFrame);
	Mat improvedDiffFrame = improveDiffFrame(diffFrame);
	if (isDebug) displayFrame("Improved diff frame", improvedDiffFrame);

	vector<Rect> boundingBoxes;
	implDo([&boundingBoxes, &improvedDiffFrame](auto impl) {
		boundingBoxes = impl->boundingBoxes(improvedDiffFrame);
	});

	return boundingBoxes;
}

vector<Rect> Performer::findBodies(Mat& frame)
{
	vector<Rect> foundLocations;
	float sensitivity = m_configurator->get<float>("BodyDetectionSensitivity");

	implDo([&foundLocations, &frame, &sensitivity](auto impl) {
		foundLocations = impl->detectBodies(frame, sensitivity);
	});

	for (auto loc : foundLocations)
	{
		cout << "Human detected!" << endl;
		implDo([&frame, &loc](auto impl) {
			impl->drawRectangle(frame, loc, Scalar(0, 255, 0), 6);
		});

		if (m_configurator->get<bool>("Debug"))
			displayFrame("Body detection", frame);
	}

	return foundLocations;
}

vector<Mat> Performer::getPersistantFrames(Mat& RGBFrame)
{
	size_t countOfPersistantImages =
		m_configurator->get<size_t>("CountPersistantImages");

	vector<Mat> frames(countOfPersistantImages);

	for (size_t i = 0; i < countOfPersistantImages; ++i)
	{
		Mat frame = m_acq->getImage();

		// We need a copy, because the body detector need a colored frame
		if ((i + 1) == countOfPersistantImages)
			frame.copyTo(RGBFrame);

		implDo([&frame](auto impl) { frame = impl->BGR2Gray(frame); });
		frames[i] = frame;
	}

	return frames;
}

Mat Performer::computeDiffFrame(const vector<Mat>& frames)
{
	const Mat& lastFrame = frames.back();
	Mat diffFrame = Mat::zeros(lastFrame.size(), lastFrame.type());
	for (const Mat& f : frames)
	{
		Mat currentDiffFrame;
		implDo([&f, &currentDiffFrame, &lastFrame](auto impl) {
			currentDiffFrame = impl->diff(f, lastFrame);
		});
		
		implDo([&f, &diffFrame, &currentDiffFrame](auto impl) {
			diffFrame = impl->or(diffFrame, currentDiffFrame);
		});
	}

	return diffFrame;
}

Mat Performer::improveDiffFrame(const Mat& diffFrame)
{
	Mat thresholdFrame;
	uint8_t thresholdFactor = m_configurator->get<uint8_t>("MotionThreshold");
	implDo([&thresholdFrame, &diffFrame, &thresholdFactor](auto impl) {
		thresholdFrame = impl->threshold(diffFrame, thresholdFactor);
	});

	Mat dilatedFrame;
	implDo([&dilatedFrame, &thresholdFrame](auto impl) {
		dilatedFrame = impl->dilate(thresholdFrame);
	});

	return dilatedFrame;
}

void Performer::displayFrame(const char* description, const Mat& frame)
{
	implDo([&description, &frame](auto impl) {
		impl->displayFrame(description, frame);
	});
}