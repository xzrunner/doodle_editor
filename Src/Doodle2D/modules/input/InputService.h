#ifndef _D2D_INPUT_SERVICE_H_
#define _D2D_INPUT_SERVICE_H_

#include "common/config.h"

#ifdef D2D_WINDOWS

#include "InputHandler.h"

namespace d2d
{
	class InputService : public InputHandler
	{
	public:
		virtual void onKeyEvent(int action, int keyCode, int unicode);
		virtual void onMouseEvent(int action, int x, int y, int buttons);

	}; // InputHandler
}

#elif defined D2D_ANDROID_NATIVE

#include "InputHandler.h"

#include "common/Context.h"
//#include "common/Sensor.h"
#include "common/Vector.h"
#include "common/Types.h"

#include <android_native_app_glue.h>

namespace d2d
{
	class InputService : public InputHandler 
	{
	public:
		InputService(android_app* pApplication/*, Sensor* pAccelerometer*/);

		status start();
		status update();
		void stop();

	private:
		virtual bool onTouchEvent(AInputEvent* pEvent);
		virtual bool onKeyboardEvent(AInputEvent* pEvent);
		virtual bool onTrackballEvent(AInputEvent* pEvent);
//		virtual bool onAccelerometerEvent(ASensorEvent* pEvent);

	private:
		android_app* m_application;

		bool m_menuKey;

//		Sensor* m_accelerometer;

	}; // InputService
}

#elif defined D2D_ANDROID_JNI

#include "InputHandler.h"

namespace d2d
{
	class InputService : public InputHandler
	{
	public:
		virtual bool onBackKeyDown();
		virtual bool onMenuKeyDown();
		virtual void onTouchesBegin(int x, int y);
		virtual void onTouchesEnd(int x, int y);

	}; // InputHandler
}

#endif

#endif // _D2D_INPUT_SERVICE_H_