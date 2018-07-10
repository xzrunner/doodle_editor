#include "TimeService.h"
#include "common/config.h"
#include "common/Log.h"

#ifdef D2D_WINDOWS
#	include <windows.h>
#endif

#include <time.h>

using namespace d2d;

TimeService::TimeService()
{
	m_elapsed = 0.0f;
	m_lastTime = 0.0f;

	srand(time(NULL));
}

void TimeService::reset()
{
	Log::info("Resetting TimeService");
	m_elapsed = 0.0f;
	m_lastTime = now();
}

void TimeService::update()
{
	double lCurrentTime = now();
	m_elapsed = (float)(lCurrentTime - m_lastTime);
	m_lastTime = lCurrentTime;
}

double TimeService::now()
{
#ifdef D2D_WINDOWS
	static __int64 freq = 0;

	if (!freq)
	{
		LARGE_INTEGER temp;
		QueryPerformanceFrequency(&temp);

		freq = (__int64) temp.QuadPart;
	}

	LARGE_INTEGER microTime;
	QueryPerformanceCounter(&microTime);

	// The 64 to 32 bit integer conversion, assuming the fraction part down
	// to microseconds takes 20 bits, should not be a problem unless the
	// system has an uptime of a few decades.
	return (double) microTime.QuadPart / (double) freq;
#else
	timespec lTimeVal;
	clock_gettime(CLOCK_MONOTONIC, &lTimeVal);
	return lTimeVal.tv_sec + (lTimeVal.tv_nsec * 1.0e-9);

// 	timeval lTimeVal;
// 	gettimeofday(&lTimeVal, NULL);
// 	return (lTimeVal.tv_sec * 1000.0) + (lTimeVal.tv_usec / 1000.0);
#endif
}

float TimeService::elapsed()
{
	return m_elapsed;
}