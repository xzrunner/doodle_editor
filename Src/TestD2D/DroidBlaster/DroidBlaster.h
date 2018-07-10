#ifndef _DBS_DROID_BLASTER_H_
#define _DBS_DROID_BLASTER_H_

#include "Doodle2D/doodle2d.h"

#include "Asteroid.h"
#include "Ship.h"
#include "Background.h"

namespace dbs
{
	class DroidBlaster : public d2d::ActivityHandler, public d2d::IDrawable
	{
	public:
		DroidBlaster(d2d::Context* pContext);
		virtual ~DroidBlaster();

		//
		// d2d::ActivityHandler interface
		//
#ifdef D2D_WINDOWS
		virtual std::string name() const;

		virtual void onDraw();
		virtual void onResize(int width, int height);
		virtual void onKey(int action, int keyCode, int unicode);
		virtual void onMouse(int action, int x, int y, int buttons);
		virtual void onUpdate(float deltaTime);
		virtual void onQuit();
#elif defined D2D_ANDROID_NATIVE
		virtual d2d::status onActivate();
		virtual void onDeactivate();
		virtual d2d::status onStep();

		virtual void onStart();
		virtual void onResume();
		virtual void onPause();
		virtual void onStop();
		virtual void onDestroy();

		virtual void onSaveState(void** pData, size_t* pSize);
		virtual void onConfigurationChanged();
		virtual void onLowMemory();

		virtual void onCreateWindow();
		virtual void onDestroyWindow();
		virtual void onGainFocus();
		virtual void onLostFocus();
#elif defined D2D_ANDROID_JNI
		virtual d2d::status onActivate();
		virtual void onDeactivate();
		virtual d2d::status onStep();
#endif

		//
		// d2d::IDrawable interface
		//
		virtual d2d::status load();
		virtual void draw() const;

	private:
		d2d::InputService* m_inputService;
		d2d::GraphicsService* m_graphicsService;
		d2d::PhysicsService*  m_physicsService;
		d2d::SoundService* m_soundService;
		d2d::TimeService* m_timeService;

		bool m_initialized;

		Background m_background;
		Ship m_ship;
		Asteroid::vec m_asteroids;
#ifdef D2D_ANDROID_NATIVE
		d2d::Sound* m_startSound;		
#endif

	}; // DroidBlaster
}

#endif // _DBS_DROID_BLASTER_H_