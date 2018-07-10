// #include "Sensor.h"
// #include "EventLoop.h"
// #include "Log.h"
// 
// using namespace d2d;
// 
// Sensor::Sensor(EventLoop& pEventLoop, int32_t pSensorType)
// 	: m_eventLoop(pEventLoop)
// {
// 	m_sensor = NULL;
// 	m_sensorType = pSensorType;
// }
// 
// status Sensor::toggle()
// {
// 	return (m_sensor != NULL) ? disable() : enable();
// }
// 
// status Sensor::enable()
// {
// 	if (m_eventLoop.m_enabled) 
// 	{
// 		m_sensor = ASensorManager_getDefaultSensor(m_eventLoop.m_sensorManager, m_sensorType);
// 		if (m_sensor != NULL) 
// 		{
// 			if (ASensorEventQueue_enableSensor(m_eventLoop.m_sensorEventQueue, m_sensor) < 0) 
// 			{
// 				goto ERROR;
// 			}
// 
// 			int32_t lMinDelay = ASensor_getMinDelay(m_sensor);
// 			if (ASensorEventQueue_setEventRate(m_eventLoop.m_sensorEventQueue, m_sensor, lMinDelay) < 0) 
// 			{
// 				goto ERROR;
// 			}
// 		} 
// 		else 
// 		{
// 			d2d::Log::error("No sensor type %d", m_sensorType);
// 		}
// 	}
// 
// 	return STATUS_OK;
// 
// ERROR:
// 	Log::error("Error while activating sensor.");
// 	disable();
// 	return STATUS_KO;
// }
// 
// status Sensor::disable()
// {
// 	if ((m_eventLoop.m_enabled) && (m_sensor != NULL)) 
// 	{
// 		if (ASensorEventQueue_disableSensor(m_eventLoop.m_sensorEventQueue, m_sensor) < 0) 
// 		{
// 			goto ERROR;
// 		}
// 		m_sensor = NULL;
// 	}
// 
// 	return STATUS_OK;
// 
// ERROR:
// 	Log::error("Error while deactivating sensor.");
// 	return STATUS_KO;
// }