#include "Doodle2D/doodle2d.h"

#ifdef D2D_ANDROID_JNI

#define MOTOX

#ifdef MOTOX
#include "Frame/MotoX.h"
#endif

d2d::TimeService lTimeService;
d2d::GraphicsService lGraphicsService(&lTimeService);
d2d::InputService lInputService(lGraphicsService.getWidth(), lGraphicsService.getHeight());
d2d::PhysicsService lPhysicsService(&lTimeService);
d2d::SoundService lSoundService();

d2d::Context lContext = { 
	&lInputService, 
	&lGraphicsService, 
	&lPhysicsService, 
	&lSoundService, 
	&lTimeService
};

#ifdef MOTOX
motox::MotoX lMotoX(&lContext);
#endif

#endif // D2D_ANDROID_JNI