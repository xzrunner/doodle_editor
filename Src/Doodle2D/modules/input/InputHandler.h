#ifndef _D2D_INPUT_HANDLER_H_
#define _D2D_INPUT_HANDLER_H_

#include "EventList.h"

#include "common/config.h"

#ifdef D2D_ANDROID_NATIVE
#include <android/input.h>
#include <android/sensor.h>
#endif

namespace d2d
{
	class InputHandler
	{
	public:
		virtual ~InputHandler() {}

#ifdef D2D_WINDOWS
		virtual void onMouseEvent(int action, int x, int y, int buttons) = 0;
#elif defined D2D_ANDROID_NATIVE
		virtual bool onTouchEvent(AInputEvent* pEvent) = 0;
		virtual bool onKeyboardEvent(AInputEvent* pEvent) = 0;
		virtual bool onTrackballEvent(AInputEvent* pEvent) = 0;
		//		virtual bool onAccelerometerEvent(ASensorEvent* pEvent) = 0;
#else
		virtual bool onBackKeyDown() = 0;
		virtual bool onMenuKeyDown() = 0;
		virtual void onTouchesBegin(int x, int y) = 0;
		virtual void onTouchesEnd(int x, int y) = 0;
#endif

		EventList& getEventList() { 
			return m_eventList; 
		}

	protected:
		EventList m_eventList;

	}; // InputHandler
}

#endif // _D2D_INPUT_HANDLER_H_