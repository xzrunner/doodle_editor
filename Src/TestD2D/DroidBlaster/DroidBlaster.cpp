#include "DroidBlaster.h"

#ifdef D2D_ANDROID_NATIVE
#include <math.h>
#include <unistd.h>
#endif

using namespace dbs;

DroidBlaster::DroidBlaster(d2d::Context* pContext)
	: m_background(pContext)
	, m_ship(pContext)
{
	d2d::Log::info("Creating DroidBlaster");

	pContext->m_graphicsService->setImpl(this);

	m_inputService = pContext->m_inputService;
	m_graphicsService = pContext->m_graphicsService;
	m_physicsService = pContext->m_physicsService;
	m_soundService = pContext->m_soundService;
	m_timeService = pContext->m_timeService;

	m_initialized = false;

	for (int i = 0; i < 16; ++i)
	{
		Asteroid::ptr lAsteroid(new Asteroid(pContext));
		m_asteroids.push_back(lAsteroid);
	}

#ifdef D2D_ANDROID_NATIVE
	m_startSound = m_soundService->registerSound("start.pcm");
#endif
}

DroidBlaster::~DroidBlaster()
{
	d2d::Log::info("Destructing DroidBlaster");
}

#ifdef D2D_WINDOWS

std::string DroidBlaster::name() const
{
	return "DroidBlaster";
}

void DroidBlaster::onDraw()
{
	m_graphicsService->update();
}

void DroidBlaster::onResize(int width, int height)
{
	m_graphicsService->onResize(width, height);

	if (!m_initialized)
	{
		m_graphicsService->start();

		// 	m_soundService->playBGM("bgm.mp3");
		// 	m_soundService->playSound(m_startSound);

		m_background.spawn();
		m_ship.spawn();
		Asteroid::vec_it iAsteroid = m_asteroids.begin();
		for (; iAsteroid < m_asteroids.end() ; ++iAsteroid)
			(*iAsteroid)->spawn();

		m_timeService->reset();

		m_initialized = true;
	}
}

void DroidBlaster::onKey(int action, int keyCode, int unicode)
{

}

void DroidBlaster::onMouse(int action, int x, int y, int buttons)
{
	m_inputService->onMouseEvent(action, x, y, buttons);
}

void DroidBlaster::onUpdate(float deltaTime)
{
	m_timeService->update();

	m_background.update();
	m_ship.update();
	Asteroid::vec_it iAsteroid = m_asteroids.begin();
	for (; iAsteroid < m_asteroids.end(); ++iAsteroid)
		(*iAsteroid)->update();

//	m_graphicsService->update();
	m_physicsService->update();
}

void DroidBlaster::onQuit()
{
	d2d::Log::info("Deactivating DroidBlaster");

	m_graphicsService->stop();
}

#elif defined D2D_ANDROID_NATIVE

d2d::status DroidBlaster::onActivate()
{
	d2d::Log::info("Activating DroidBlaster");

	if (m_graphicsService->start() != d2d::STATUS_OK)
	{
		return d2d::STATUS_KO;
	}
	if (m_inputService->start() != d2d::STATUS_OK)
	{
		return d2d::STATUS_KO;
	}
	if (m_soundService->start() != d2d::STATUS_OK)
	{
		return d2d::STATUS_KO;
	}

	m_soundService->playBGM("bgm.mp3");
	m_soundService->playSound(m_startSound);

	m_background.spawn();
	m_ship.spawn();
	Asteroid::vec_it iAsteroid = m_asteroids.begin();
	for (; iAsteroid < m_asteroids.end() ; ++iAsteroid)
		(*iAsteroid)->spawn();

	m_timeService->reset();

	return d2d::STATUS_OK;
}

void DroidBlaster::onDeactivate()
{
	d2d::Log::info("Deactivating DroidBlaster");

	m_graphicsService->stop();
	m_inputService->stop();
	m_soundService->stop();
}

d2d::status DroidBlaster::onStep()
{
	m_timeService->update();

	m_background.update();
	m_ship.update();
	Asteroid::vec_it iAsteroid = m_asteroids.begin();
	for (; iAsteroid < m_asteroids.end(); ++iAsteroid)
		(*iAsteroid)->update();

	if (m_inputService->update() != d2d::STATUS_OK)
		return d2d::STATUS_KO;
	if (m_graphicsService->update() != d2d::STATUS_OK)
		return d2d::STATUS_KO;
	if (m_physicsService->update() != d2d::STATUS_OK)
		return d2d::STATUS_KO;

	return d2d::STATUS_OK;
}

void DroidBlaster::onStart()
{

}

void DroidBlaster::onResume()
{

}

void DroidBlaster::onPause()
{

}

void DroidBlaster::onStop()
{

}

void DroidBlaster::onDestroy()
{

}

void DroidBlaster::onSaveState(void** pData, size_t* pSize)
{

}

void DroidBlaster::onConfigurationChanged()
{

}

void DroidBlaster::onLowMemory()
{

}

void DroidBlaster::onCreateWindow()
{

}

void DroidBlaster::onDestroyWindow()
{

}

void DroidBlaster::onGainFocus()
{

}

void DroidBlaster::onLostFocus()
{

}

#elif defined D2D_ANDROID_JNI

d2d::status DroidBlaster::onActivate()
{

}

void DroidBlaster::onDeactivate()
{

}

d2d::status DroidBlaster::onStep()
{

}

#endif

d2d::status DroidBlaster::load()
{
	if (m_background.load() != d2d::STATUS_OK)
		return d2d::STATUS_KO;
	for (size_t i = 0, n = m_asteroids.size(); i < n; ++i)
	{
		if (m_asteroids[i]->load() != d2d::STATUS_OK)
			return d2d::STATUS_KO;
	}
	if (m_ship.load() != d2d::STATUS_OK)
		return d2d::STATUS_KO;
	return d2d::STATUS_OK;
}

void DroidBlaster::draw() const
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	m_background.draw();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	for (size_t i = 0, n = m_asteroids.size(); i < n; ++i)
		m_asteroids[i]->draw();
	m_ship.draw();

	glDisable(GL_BLEND);	
}