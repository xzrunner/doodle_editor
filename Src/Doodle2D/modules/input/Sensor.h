// #ifndef _D2D_SENSOR_H_
// #define _D2D_SENSOR_H_
// 
// #include "Types.h"
// 
// #include <android/sensor.h>
// 
// namespace d2d
// {
// 	class EventLoop;
// 
// 	class Sensor 
// 	{
// 	public:
// 		Sensor(EventLoop& pEventLoop, int32_t pSensorType);
// 
// 		status toggle();
// 		status enable();
// 		status disable();
// 
// 	private:
// 		EventLoop& m_eventLoop;
// 		const ASensor* m_sensor;
// 		int32_t m_sensorType;
// 
// 	}; // Sensor
// }
// 
// #endif // _D2D_SENSOR_H_