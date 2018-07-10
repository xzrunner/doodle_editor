#include "common/config.h"

#ifdef D2D_ANDROID_NATIVE

#include "EventLoop.h"
#include "common/Log.h"

using namespace d2d;

EventLoop::EventLoop(android_app* pApplication)
{
	m_enabled = false;
	m_quit = false;
	m_application = pApplication;

	m_activityHandler = NULL;
	m_inputHandler = NULL;

	m_sensorManager = NULL;
	m_sensorEventQueue = NULL;

	m_application->userData = this;
	m_application->onAppCmd = callback_event;
	m_application->onInputEvent = callback_input;
}

void EventLoop::run(ActivityHandler* pActivityHandler, InputHandler* pInputHandler)
{
	int32_t lResult;
	int32_t lEvents;
	android_poll_source* lSource;

	app_dummy();

	m_activityHandler = pActivityHandler;
	m_inputHandler = pInputHandler;

	Log::info("Start event loop");
	while (true)
	{
		while ((lResult = ALooper_pollAll(m_enabled ? 0 : -1, NULL, &lEvents, (void**)&lSource)) >= 0)
		{
			if (lSource != NULL)
			{
//				Log::info("Processing an event");
				lSource->process(m_application, lSource);
			}
			if (m_application->destroyRequested)
			{
				Log::info("Exiting event loop");
				return;
			}
		}
		if (m_enabled && !m_quit)
		{
			if (m_activityHandler->onStep() != STATUS_OK)
			{
				m_quit = true;
				ANativeActivity_finish(m_application->activity);
			}
		}
	}
}

void EventLoop::activate()
{
// 	if (!m_enabled && m_application->window != NULL)
// 	{
// 		m_sensorPollSource.id = LOOPER_ID_USER;
// 		m_sensorPollSource.app = m_application;
// 		m_sensorPollSource.process = callback_sensor;
// 		m_sensorManager = ASensorManager_getInstance();
// 		if (m_sensorManager != NULL) 
// 		{
// 			m_sensorEventQueue = ASensorManager_createEventQueue(
// 				m_sensorManager, m_application->looper,
// 				LOOPER_ID_USER, NULL, &m_sensorPollSource);
// 			if (m_sensorEventQueue == NULL) goto ERROR;
// 		}
// 
// 		m_quit = false; m_enabled = true;
// 		if (m_activityHandler->onActivate() != STATUS_OK)
// 		{
// 			goto ERROR;
// 		}
// 	}
// 
// ERROR:
// 	m_quit = true;
// 	deactivate();
// 	ANativeActivity_finish(m_application->activity);

	if ((!m_enabled) && (m_application->window != NULL)) 
	{
		m_quit = false; m_enabled = true;
		if (m_activityHandler->onActivate() != STATUS_OK) {
			m_quit = true;
			ANativeActivity_finish(m_application->activity);
		}
	}
}

void EventLoop::deactivate()
{
	if (m_enabled)
	{
		m_activityHandler->onDeactivate();
		m_enabled = false;

		if (m_sensorEventQueue != NULL) 
		{
			ASensorManager_destroyEventQueue(m_sensorManager, m_sensorEventQueue);
			m_sensorEventQueue = NULL;
		}
		m_sensorManager = NULL;
	}
}

void EventLoop::processAppEvent(int32_t pCommand)
{
	switch (pCommand)
	{
	case APP_CMD_CONFIG_CHANGED:
		m_activityHandler->onConfigurationChanged();
		break;
	case APP_CMD_INIT_WINDOW:
		m_activityHandler->onCreateWindow();
		break;
	case APP_CMD_DESTROY:
		m_activityHandler->onDestroy();
		break;
	case APP_CMD_GAINED_FOCUS:
		activate();
		m_activityHandler->onGainFocus();
		break;
	case APP_CMD_LOST_FOCUS:
		m_activityHandler->onLostFocus();
		deactivate();
		break;
	case APP_CMD_LOW_MEMORY:
		m_activityHandler->onLowMemory();
		break;
	case APP_CMD_PAUSE:
		m_activityHandler->onPause();
		deactivate();
		break;
	case APP_CMD_RESUME:
		m_activityHandler->onResume();
		break;
	case APP_CMD_SAVE_STATE:
		m_activityHandler->onSaveState(&m_application->savedState, &m_application->savedStateSize);
		break;
	case APP_CMD_START:
		m_activityHandler->onStart();
		break;
	case APP_CMD_STOP:
		m_activityHandler->onStop();
		break;
	case APP_CMD_TERM_WINDOW:
		m_activityHandler->onDestroyWindow();
		deactivate();
		break;
	default:
		break;
	}
}

int32_t EventLoop::processInputEvent(AInputEvent* pEvent)
{
	int32_t lEventType = AInputEvent_getType(pEvent);
	switch (lEventType) 
	{
	case AINPUT_EVENT_TYPE_MOTION:
		switch (AInputEvent_getSource(pEvent)) 
		{
		case AINPUT_SOURCE_TOUCHSCREEN:
			return m_inputHandler->onTouchEvent(pEvent);
			break;

		case AINPUT_SOURCE_TRACKBALL:
			return m_inputHandler->onTrackballEvent(pEvent);
			break;
		}
		break;

	case AINPUT_EVENT_TYPE_KEY:
		return m_inputHandler->onKeyboardEvent(pEvent);
		break;
	}
	return 0;
}

// void EventLoop::processSensorEvent()
// {
// 	ASensorEvent lEvent;
// 	while (ASensorEventQueue_getEvents(m_sensorEventQueue, &lEvent, 1) > 0) 
// 	{
// 		switch (lEvent.type) 
// 		{
// 		case ASENSOR_TYPE_ACCELEROMETER:
// 			m_inputHandler->onAccelerometerEvent(&lEvent);
// 			break;
// 		}
// 	}
// }

void EventLoop::callback_event(android_app* pApplication, int32_t pCommand)
{
	EventLoop& lEventLoop = *(EventLoop*) pApplication->userData;
	lEventLoop.processAppEvent(pCommand);
}

int32_t EventLoop::callback_input(android_app* pApplication, AInputEvent* pEvent)
{
	EventLoop& lEventLoop = *(EventLoop*) pApplication->userData;
	return lEventLoop.processInputEvent(pEvent);
}

//void EventLoop::callback_sensor(android_app* pApplication, android_poll_source* pSource)
//{
//	EventLoop& lEventLoop = *(EventLoop*) pApplication->userData;
//	lEventLoop.processSensorEvent();
//}

#endif // D2D_ANDROID_NATIVE
