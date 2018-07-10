#include "Doodle2D/doodle2d.h"

#ifdef D2D_WINDOWS

//#define DROID_BLASTER
#define MOTOX

#include <esUtil.h>

//d2d::ActivityHandler* activity = NULL;

//////////////////////////////////////////////////////////////////////////

#ifdef DROID_BLASTER
#include "DroidBlaster/DroidBlaster.h"
#elif defined MOTOX
#include "MotoX/Frame/MotoX.h"
#endif

d2d::TimeService lTimeService;
d2d::GraphicsService lGraphicsService(&lTimeService);
d2d::InputService lInputService;
d2d::PhysicsService lPhysicsService(&lTimeService);
d2d::SoundService lSoundService;

d2d::Context lContext = { 
	&lInputService, 
	&lGraphicsService, 
	&lPhysicsService, 
	&lSoundService, 
	&lTimeService 
};

#ifdef DROID_BLASTER
	dbs::DroidBlaster droidBlaster(&lContext);
	d2d::ActivityHandler* activity = &droidBlaster;
#elif defined MOTOX
	motox::MotoX motoX(&lContext);
	d2d::ActivityHandler* activity = &motoX;
#endif

//////////////////////////////////////////////////////////////////////////

int init(ESContext* esContext)
{
	return TRUE;
}

void onDraw(ESContext* esContext)
{
	glViewport(0, 0, esContext->width, esContext->height);

// 	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
// 	glClear(GL_COLOR_BUFFER_BIT);

	activity->onDraw();

	eglSwapBuffers (esContext->eglDisplay, esContext->eglSurface);
}

void onResize(ESContext* esContext, int width, int height)
{
	activity->onResize(width, height);
}

void onKey(ESContext* esContext, int action, int keyCode, int unicode)
{
	activity->onKey(action, keyCode, unicode);
}

void onMouse(ESContext* esContext, int action, int x, int y, int buttons)
{
	activity->onMouse(action, x, y, buttons);
}

void onUpdate(ESContext* esContext, float deltaTime)
{
	activity->onUpdate(deltaTime);
}

void onQuit(ESContext* esContext)
{
	activity->onQuit();
}

int main(int argc, char* argv[])
{
	ESContext esContext;

	esInitContext(&esContext);

	esCreateWindow (&esContext, activity->name().c_str(), d2d::SCREEN_WIDTH, d2d::SCREEN_HEIGHT, ES_WINDOW_RGB);

	if (!init(&esContext))
		return 0;

	esRegisterDrawFunc(&esContext, onDraw);
	esRegisterResizeFunc(&esContext, onResize);
	esRegisterKeyFunc(&esContext, onKey);
	esRegisterMouseFunc(&esContext, onMouse);
	esRegisterUpdateFunc(&esContext, onUpdate);
	esRegisterQuitFunc(&esContext, onQuit);

	esMainLoop(&esContext);
}

#endif