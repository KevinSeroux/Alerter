#ifndef PERFORMER__H
#define PERFORMER__H

#include <System/Thread.h>
#include <Acquiring/VideoStreamAcquirer.h>
#include "Interfaces/PerformerInt.h"
#include <vector>

// Anticipated declarations
class Configurator;

namespace performing
{
	class Performer : public Thread
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

		PerformerInt& m_perfImpl;
		acquiring::VideoStreamAcquirer& m_acqImpl;
		Configurator& m_configurator;
	};
}

#endif // PERFORMER__H
