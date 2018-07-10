#include "InputService.h"

#include "common/Log.h"
#include "modules/graphics/Camera.h"

//#define VIEW_DEBUG

#ifdef D2D_WINDOWS

using namespace d2d;

#include "esUtil.h"

void InputService::onKeyEvent(int action, int keyCode, int unicode)
{
	switch (action)
	{
	case ES_KEY_DOWN:
		switch (keyCode)
		{
		case VK_ESCAPE:
			m_eventList.push(Event(e_key_back_down, Vector()));
			break;
		}
		break;
	}
}

void InputService::onMouseEvent(int action, int x, int y, int buttons)
{
#ifdef VIEW_DEBUG
 	static bool isDrag = false;
 	static Vector lastPos;
#endif

	switch (buttons)
	{
	case ES_MOUSE_LBUTTON:
		switch(action)
		{
		case ES_MOUSE_DOWN:
			m_eventList.push(Event(e_touch_down, Vector(x, y)));

#ifdef VIEW_DEBUG
 			isDrag = true;
 			lastPos.set((float)x, (float)y);
#endif

			break;
		case ES_MOUSE_UP:
			m_eventList.push(Event(e_touch_up, Vector(x, y)));

#ifdef VIEW_DEBUG
			isDrag = false;
#endif

			break;
		case ES_MOUSE_MOVE:
			m_eventList.push(Event(e_touch_move, Vector(x, y)));

#ifdef VIEW_DEBUG
 			if (isDrag)
 			{
 				Camera::translate(x - lastPos.x, lastPos.y - y);
 				lastPos.set((float)x, (float)y);
 			}
#endif
			break;
		}
		break;
	}

#ifdef VIEW_DEBUG
  	if (action == ES_MOUSE_WHEEL)
  	{
 		if (x > 0) 
			Camera::zoomIn();
 		else 
			Camera::zoomOut();
  	}
#endif
}

#elif defined D2D_ANDROID_NATIVE

#include <android_native_app_glue.h>
#include <cmath>

using namespace d2d;

InputService::InputService(android_app* pApplication/*,Sensor* pAccelerometer*/)
{
	m_application = pApplication;

	m_menuKey = false;
//	m_accelerometer = pAccelerometer;
}

status InputService::start()
{
	return STATUS_OK;
}

status InputService::update()
{
// 	// Activates or not sensors if search button is pressed.
// 	if (m_menuKey) 
// 	{
// // 		if (m_accelerometer->toggle() != STATUS_OK)
// // 		{
// // 			return STATUS_KO;
// // 		}
// 	}
// 
// 	// Clears previous state.
// 	m_menuKey = false;
// 	return STATUS_OK;

	if (m_menuKey) {
		return STATUS_EXIT;
	}
	return STATUS_OK;
}

void InputService::stop()
{
//	m_accelerometer->disable();
}

bool InputService::onTouchEvent(AInputEvent* pEvent)
{
//  // #ifdef VIEW_DEBUG
// 	//////////////////////////////////////////////////////////////////////////
// 	static bool isDrag = false;
// 	static Vector lastPos;
// 
// 	switch (AMotionEvent_getAction(pEvent))
// 	{
// 	case AMOTION_EVENT_ACTION_DOWN:
// 		isDrag = true;
// 		lastPos.set(AMotionEvent_getX(pEvent, 0), AMotionEvent_getY(pEvent, 0));
// 		break;
// 	case AMOTION_EVENT_ACTION_UP:
// 		isDrag = false;
// 		break;
// 	case AMOTION_EVENT_ACTION_MOVE:
// 		if (isDrag)
// 		{
// 			Camera::translate(AMotionEvent_getX(pEvent, 0) - lastPos.x, lastPos.y - AMotionEvent_getY(pEvent, 0));
// 			lastPos.set(AMotionEvent_getX(pEvent, 0), AMotionEvent_getY(pEvent, 0));
// 		}
// 		break;
// 	}
//	// #endif
// 	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	for (size_t i = 0, n = AMotionEvent_getPointerCount(pEvent); i < n; ++i)
	{
		size_t pointerId = AMotionEvent_getPointerId(pEvent, i);
		size_t action = AMotionEvent_getAction(pEvent) & AMOTION_EVENT_ACTION_MASK;
		size_t pointerIndex = i;

		if (action == AMOTION_EVENT_ACTION_POINTER_DOWN || action == AMOTION_EVENT_ACTION_POINTER_UP) {
			pointerIndex = (AMotionEvent_getAction(pEvent) & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK) >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
			pointerId = AMotionEvent_getPointerId(pEvent, pointerIndex);
		}

		const float x = AMotionEvent_getX(pEvent, pointerIndex),
			y = AMotionEvent_getY(pEvent, pointerIndex);

		switch (action)
		{
		case AMOTION_EVENT_ACTION_DOWN:
		case AMOTION_EVENT_ACTION_POINTER_DOWN:
			m_eventList.push(Event(e_touch_down, Vector(x, y)));
			break;
		case AMOTION_EVENT_ACTION_UP:
		case AMOTION_EVENT_ACTION_POINTER_UP:
			m_eventList.push(Event(e_touch_up, Vector(x, y)));
			break;
		case AMOTION_EVENT_ACTION_MOVE:
			m_eventList.push(Event(e_touch_move, Vector(x, y)));
			break;
		}
	}

	//////////////////////////////////////////////////////////////////////////

	return true;
}

bool InputService::onKeyboardEvent(AInputEvent* pEvent)
{
	const float ORTHOGONAL_MOVE = 1.0f;

	if (AKeyEvent_getAction(pEvent) == AKEY_EVENT_ACTION_DOWN) 
	{
		switch (AKeyEvent_getKeyCode(pEvent)) 
		{
			case AKEYCODE_BACK:
//				m_eventList.push(Event(e_key_back_down, Vector()));
				return false;
		}
	} 
	else 
	{
		switch (AKeyEvent_getKeyCode(pEvent)) 
		{
			case AKEYCODE_MENU:
				m_menuKey = true;
				break;
			case AKEYCODE_BACK:
//				m_eventList.push(Event(e_key_back_down, Vector()));
				return false;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	if (AKeyEvent_getAction(pEvent) == AKEY_EVENT_ACTION_DOWN)
	{
		switch (AKeyEvent_getKeyCode(pEvent)) 
		{
		case AKEYCODE_DPAD_LEFT:
			m_eventList.push(Event(e_key_down, Vector(-1, 0)));
			break;
		case AKEYCODE_DPAD_RIGHT:
			m_eventList.push(Event(e_key_down, Vector( 1, 0)));
			break;
		case AKEYCODE_DPAD_DOWN:
			m_eventList.push(Event(e_key_down, Vector(0, -1)));
			break;
		case AKEYCODE_DPAD_UP:
			m_eventList.push(Event(e_key_down, Vector(0,  1)));
			break;
		}
	}
	else if (AKeyEvent_getAction(pEvent) == AKEY_EVENT_ACTION_UP)
	{
		switch (AKeyEvent_getKeyCode(pEvent)) 
		{
		case AKEYCODE_DPAD_LEFT:
			m_eventList.push(Event(e_key_up, Vector(-1, 0)));
			break;
		case AKEYCODE_DPAD_RIGHT:
			m_eventList.push(Event(e_key_up, Vector( 1, 0)));
			break;
		case AKEYCODE_DPAD_DOWN:
			m_eventList.push(Event(e_key_up, Vector(0, -1)));
			break;
		case AKEYCODE_DPAD_UP:
			m_eventList.push(Event(e_key_up, Vector(0,  1)));
			break;
		}
	}
	//////////////////////////////////////////////////////////////////////////

	return true;
}

bool InputService::onTrackballEvent(AInputEvent* pEvent)
{
	//const float ORTHOGONAL_MOVE = 1.0f;
	//const float DIAGONAL_MOVE   = 0.707f;
	//const float THRESHOLD       = (1/100.0f);

	//if (AMotionEvent_getAction(pEvent) == AMOTION_EVENT_ACTION_MOVE) 
	//{
	//	float lDirectionX = AMotionEvent_getX(pEvent, 0);
	//	float lDirectionY = AMotionEvent_getY(pEvent, 0);
	//	float lHorizontal, lVertical;
	//	if (lDirectionX < -THRESHOLD) 
	//	{
	//		if (lDirectionY < -THRESHOLD) 
	//		{
	//			lHorizontal = -DIAGONAL_MOVE;
	//			lVertical   = DIAGONAL_MOVE;
	//		} 
	//		else if (lDirectionY > THRESHOLD) 
	//		{
	//			lHorizontal = -DIAGONAL_MOVE;
	//			lVertical   = -DIAGONAL_MOVE;
	//		} 
	//		else 
	//		{
	//			lHorizontal = -ORTHOGONAL_MOVE;
	//			lVertical   = 0.0f;
	//		}
	//	} 
	//	else if (lDirectionX > THRESHOLD) 
	//	{
	//		if (lDirectionY < -THRESHOLD) 
	//		{
	//			lHorizontal = DIAGONAL_MOVE;
	//			lVertical   = DIAGONAL_MOVE;
	//		} 
	//		else if (lDirectionY > THRESHOLD) 
	//		{
	//			lHorizontal = DIAGONAL_MOVE;
	//			lVertical   = -DIAGONAL_MOVE;
	//		} 
	//		else 
	//		{
	//			lHorizontal = ORTHOGONAL_MOVE;
	//			lVertical   = 0.0f;
	//		}
	//	} 
	//	else if (lDirectionY < -THRESHOLD) 
	//	{
	//		lHorizontal = 0.0f;
	//		lVertical   = ORTHOGONAL_MOVE;
	//	} 
	//	else if (lDirectionY > THRESHOLD) 
	//	{
	//		lHorizontal = 0.0f;
	//		lVertical   = -ORTHOGONAL_MOVE;
	//	}

	//	// Ends movement if there is a counter movement.
	//	if ((lHorizontal < 0.0f) && (m_horizontal > 0.0f)) 
	//	{
	//		m_horizontal = 0.0f;
	//	} 
	//	else if((lHorizontal > 0.0f) && (m_horizontal < 0.0f))
	//	{
	//		m_horizontal = 0.0f;
	//	} 
	//	else 
	//	{
	//		m_horizontal = lHorizontal;
	//	}
	//	if ((lVertical < 0.0f) && (m_vertical > 0.0f)) 
	//	{
	//		m_vertical = 0.0f;
	//	} 
	//	else if ((lVertical > 0.0f) && (m_vertical < 0.0f)) 
	//	{
	//		m_vertical = 0.0f;
	//	} 
	//	else 
	//	{
	//		m_vertical = lVertical;
	//	}
	//} 
	//else 
	//{
	//	m_horizontal = 0.0f; m_vertical = 0.0f;
	//}
	return true;
}

// bool InputService::onAccelerometerEvent(ASensorEvent* pEvent)
// {
// 	const float GRAVITY  =  ASENSOR_STANDARD_GRAVITY / 2.0f;
// 	const float MIN_X    = -1.0f; const float MAX_X = 1.0f;
// 	const float MIN_Y    =  0.0f; const float MAX_Y = 2.0f;
// 	const float CENTER_X = (MAX_X + MIN_X) / 2.0f;
// 	const float CENTER_Y = (MAX_Y + MIN_Y) / 2.0f;
// 
// 	float lRawHorizontal = pEvent->vector.x / GRAVITY;
// 	if (lRawHorizontal > MAX_X) 
// 	{
// 		lRawHorizontal = MAX_X;
// 	} 
// 	else if (lRawHorizontal < MIN_X) 
// 	{
// 		lRawHorizontal = MIN_X;
// 	}
// 	m_horizontal = CENTER_X - lRawHorizontal;
// 
// 	float lRawVertical = pEvent->vector.z / GRAVITY;
// 	if (lRawVertical > MAX_Y) 
// 	{
// 		lRawVertical = MAX_Y;
// 	} 
// 	else if (lRawVertical < MIN_Y) 
// 	{
// 		lRawVertical = MIN_Y;
// 	}
// 	m_vertical = lRawVertical - CENTER_Y;
// 
// 	return true;
// }

#elif defined D2D_ANDROID_JNI

using namespace d2d;

bool InputService::onBackKeyDown()
{
	m_eventList.push(Event(e_key_back_down, Vector()));
	return true;
}

bool InputService::onMenuKeyDown()
{
	m_eventList.push(Event(e_key_menu_down, Vector()));
	return true;
}

void InputService::onTouchesBegin(int x, int y)
{
	m_eventList.push(Event(e_touch_down, Vector(x, y)));
}

void InputService::onTouchesEnd(int x, int y)
{
	m_eventList.push(Event(e_touch_up, Vector(x, y)));
}

#endif