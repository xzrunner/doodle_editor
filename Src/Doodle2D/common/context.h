#ifndef _D2D_CONTEXT_H_
#define _D2D_CONTEXT_H_

#include "config.h"

#ifdef D2D_ANDROID_NATIVE
class android_app;
#endif

namespace d2d
{
	class GraphicsService;
	class InputService;
	class PhysicsService;
	class SoundService;
	class TimeService;

	struct Context
	{
		InputService* m_inputService;
		GraphicsService* m_graphicsService;
		PhysicsService* m_physicsService;
		SoundService* m_soundService;
		TimeService* m_timeService;

		// todo
#ifdef D2D_ANDROID_NATIVE
		android_app* m_pApplication;
#endif
	}; // Context
}

#endif // _D2D_CONTEXT_H_