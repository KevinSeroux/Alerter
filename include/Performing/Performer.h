#ifndef PERFORMER__H
#define PERFORMER__H

#include <System/Thread.h>
#include <System/DependencyInjector.h>
#include <Acquiring/VideoStreamAcquirer.h>
#include "Interfaces/PerformerInt.h"
#include <vector>

// Anticipated declarations
class Configurator;

namespace performing
{
	class Performer : public Thread, private DependencyInjector<PerformerInt>
	{
	public:
		Performer(PerformerInt&, acquiring::VideoStreamAcquirer&);
		void run();

	private:
		std::vector<cv::Rect> findMotion(std::vector<cv::Mat>&);
		std::vector<cv::Rect> findBodies(cv::Mat&);
		std::vector<cv::Mat> getPersistantFrames(cv::Mat&);
		cv::Mat computeDiffFrame(const std::vector<cv::Mat>&);
		cv::Mat improveDiffFrame(const cv::Mat&);
		void displayFrame(const char*, const cv::Mat&);

		acquiring::VideoStreamAcquirer* m_acq;
		Configurator* m_configurator;
	};
}

#endif // PERFORMER__H
