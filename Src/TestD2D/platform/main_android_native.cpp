#include "Doodle2D/doodle2d.h"

#ifdef D2D_ANDROID_NATIVE

//#define DROID_BLASTER
#define MOTOX

#ifdef DROID_BLASTER
#include "../DroidBlaster/DroidBlaster.h"
#elif defined MOTOX
#include "Frame/MotoX.h"
#endif

void android_main(android_app* pApplication)
{
	d2d::EventLoop lEventLoop(pApplication);
	//	packt::Sensor lAccelerometer(lEventLoop, ASENSOR_TYPE_ACCELEROMETER);

	d2d::TimeService lTimeService;
	d2d::GraphicsService lGraphicsService(&lTimeService, pApplication);
	d2d::InputService lInputService(pApplication/*,&lAccelerometer*/);
	d2d::PhysicsService lPhysicsService(&lTimeService);
	d2d::SoundService lSoundService(pApplication);

	d2d::Context lContext = { 
		&lInputService, 
		&lGraphicsService, 
		&lPhysicsService, 
		&lSoundService, 
		&lTimeService,
		pApplication
	};

#ifdef DROID_BLASTER
	dbs::DroidBlaster lDroidBlaster(&lContext);
	lEventLoop.run(&lDroidBlaster, &lInputService);
#elif defined MOTOX
	motox::MotoX lMotoX(&lContext);
	lEventLoop.run(&lMotoX, &lInputService);
#endif
}

#endif