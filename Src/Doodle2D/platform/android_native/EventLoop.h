#include "common/config.h"

#ifdef D2D_ANDROID_NATIVE

#ifndef _D2D_EVENT_LOOP_H_
#define _D2D_EVENT_LOOP_H_

#include "ActivityHandler.h"
#include "modules/input/InputHandler.h"
#include "common/Types.h"

#include <android_native_app_glue.h>

namespace d2d
{
	class EventLoop
	{
	public:
		EventLoop(android_app* pApplication);

		void run(ActivityHandler* pActivityHandler, InputHandler* pInputHandler);

	protected:
		void activate();
		void deactivate();

		void processAppEvent(int32_t pCommand);
		int32_t processInputEvent(AInputEvent* pEvent);
//		void processSensorEvent();

	private:
		static void callback_event(android_app* pApplication, int32_t pCommand);
		static int32_t callback_input(android_app* pApplication, AInputEvent* pEvent);
//		static void callback_sensor(android_app* pApplication, android_poll_source* pSource);

	private:
		bool m_enabled;
		bool m_quit;

		android_app* m_application;

		ActivityHandler* m_activityHandler;
		InputHandler* m_inputHandler;

		ASensorManager* m_sensorManager;
		ASensorEventQueue* m_sensorEventQueue;
		android_poll_source m_sensorPollSource;

//		friend class Sensor;

	}; // EventLoop
}

#endif // _D2D_EVENT_LOOP_H_
#endif // D2D_ANDROID_NATIVE
