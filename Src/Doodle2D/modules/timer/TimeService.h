#ifndef _D2D_TIME_SERVICE_H_
#define _D2D_TIME_SERVICE_H_

#include "common/Types.h"

namespace d2d
{
	class TimeService
	{
	public:
		TimeService();

		void reset();
		void update();

		double now();
		float elapsed();

	private:
		float m_elapsed;
		double m_lastTime;

	}; // TimeService
}

#endif // _D2D_TIME_SERVICE_H_