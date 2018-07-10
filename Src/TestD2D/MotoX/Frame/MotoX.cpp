#include "MotoX.h"
#include "PlayScene.h"
#include "MainScene.h"
#include "Level1Scene.h"

using namespace motox;

MotoX::MotoX(d2d::Context* pContext)
{
	d2d::Log::info("Creating MotoX");

#ifdef D2D_WINDOWS
	d2d::FileSystem::Instance()->setWinRoot(
		"D:/MyProject/svn 2/FruitsEditor/MotoX/MotoX/pc/");
#endif

	pContext->m_graphicsService->setImpl(this);

	m_inputService = pContext->m_inputService;
	m_graphicsService = pContext->m_graphicsService;
	m_physicsService = pContext->m_physicsService;
	m_soundService = pContext->m_soundService;
	m_timeService = pContext->m_timeService;

	m_game = new d2d::Game();
//	m_game->setScene(new PlayScene(m_game, pContext, 1, 1));
	m_game->setScene(new MainScene(m_game, pContext));
//	m_game->setScene(new Level1Scene(m_game, pContext));

	m_initialized = false;
}

MotoX::~MotoX()
{
	d2d::Log::info("Destructing MotoX");

	delete m_game;
}

#ifdef D2D_WINDOWS

std::string MotoX::name() const
{
	return "MotoX";
}

void MotoX::onDraw()
{
	m_graphicsService->update();
}

void MotoX::onResize(int width, int height)
{
	m_graphicsService->onResize(width, height);

	if (!m_initialized)
	{
		m_graphicsService->start();

		// 	m_soundService->playBGM("bgm.mp3");
		// 	m_soundService->playSound(m_startSound);

		// 		m_background.spawn();
		// 		m_ship.spawn();
		// 		Asteroid::vec_it iAsteroid = m_asteroids.begin();
		// 		for (; iAsteroid < m_asteroids.end() ; ++iAsteroid)
		// 			(*iAsteroid)->spawn();

		m_timeService->reset();

		m_initialized = true;
	}
}

void MotoX::onKey(int action, int keyCode, int unicode)
{
	m_inputService->onKeyEvent(action, keyCode, unicode);

	if (PlayScene* scene = dynamic_cast<PlayScene*>(m_game->getScene()))
		scene->onKey(action, keyCode);
}

void MotoX::onMouse(int action, int x, int y, int buttons)
{
	m_inputService->onMouseEvent(action, x, y, buttons);

// 	if (action == ES_MOUSE_DOWN && buttons == ES_MOUSE_RBUTTON)
// 		m_physicsService->update();
}

void MotoX::onUpdate(float deltaTime)
{
	m_timeService->update();

	m_physicsService->update();

	update();
}

void MotoX::onQuit()
{
	d2d::Log::info("Deactivating MotoX");

	m_graphicsService->stop();
}

#elif defined D2D_ANDROID_NATIVE

d2d::status MotoX::onActivate()
{
	d2d::Log::info("Activating MotoX");

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

	m_timeService->reset();

	return d2d::STATUS_OK;
}

void MotoX::onDeactivate()
{
	d2d::Log::info("Deactivating MotoX");

	m_graphicsService->stop();
	m_inputService->stop();
	m_soundService->stop();
}

d2d::status MotoX::onStep()
{
	m_timeService->update();

	if (m_inputService->update() != d2d::STATUS_OK)
		return d2d::STATUS_KO;

 	if (m_graphicsService->update() != d2d::STATUS_OK)
 		return d2d::STATUS_KO;

	if (m_physicsService->update() != d2d::STATUS_OK)
		return d2d::STATUS_KO;

	update();

	return d2d::STATUS_OK;
}

void MotoX::onStart()
{

}

void MotoX::onResume()
{

}

void MotoX::onPause()
{

}

void MotoX::onStop()
{

}

void MotoX::onDestroy()
{

}

void MotoX::onSaveState(void** pData, size_t* pSize)
{

}

void MotoX::onConfigurationChanged()
{

}

void MotoX::onLowMemory()
{

}

void MotoX::onCreateWindow()
{
	
}

void MotoX::onDestroyWindow()
{

}

void MotoX::onGainFocus()
{

}

void MotoX::onLostFocus()
{

}

#elif defined D2D_ANDROID_JNI

d2d::status MotoX::onActivate()
{
	d2d::Log::info("Activating MotoX");

	if (m_graphicsService->start() != d2d::STATUS_OK)
	{
		return d2d::STATUS_KO;
	}
// 	if (m_inputService->start() != d2d::STATUS_OK)
// 	{
// 		return d2d::STATUS_KO;
// 	}
// 	if (m_soundService->start() != d2d::STATUS_OK)
// 	{
// 		return d2d::STATUS_KO;
// 	}

	m_timeService->reset();

	return d2d::STATUS_OK;
}

void MotoX::onDeactivate()
{
	d2d::Log::info("Deactivating MotoX");

	m_graphicsService->stop();
//	m_inputService->stop();
//	m_soundService->stop();
}

d2d::status MotoX::onStep()
{
	m_timeService->update();

// 	if (m_inputService->update() != d2d::STATUS_OK)
// 		return d2d::STATUS_KO;

	if (m_graphicsService->update() != d2d::STATUS_OK)
		return d2d::STATUS_KO;

	if (m_physicsService->update() != d2d::STATUS_OK)
		return d2d::STATUS_KO;

	update();

	return d2d::STATUS_OK;
}

#endif // D2D_ANDROID_NATIVE

d2d::status MotoX::load()
{
	m_game->load();

	return d2d::STATUS_OK;
}

void MotoX::draw() const
{
	m_game->draw();
}

void MotoX::update()
{
	m_game->update();

	if (!m_game->isAlive())
	{
#ifdef D2D_WINDOWS
		exit(0);
#elif defined D2D_ANDROID_JNI
		//onDeactivate();

		cocos2d::JniMethodInfo t;

		if (cocos2d::JniHelper::getStaticMethodInfo(t
			, "com/zz/d2d/jni/D2DActivity"
			, "terminateProcess"
			, "()V"))
		{
			t.env->CallStaticVoidMethod(t.classID, t.methodID);
			t.env->DeleteLocalRef(t.classID);
		}
#endif // D2D_WINDOWS
	}
}