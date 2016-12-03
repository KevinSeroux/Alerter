#ifndef OPENCV_PERFORMER__H
#define OPENCV_PERFORMER__H

#include "Interfaces/PerformerInt.h"

namespace performing
{
	class OpenCVPerformer : public PerformerInt
	{
	public:
		void performImage();
	};
}

#endif // OPENCV_PERFORMER__H
