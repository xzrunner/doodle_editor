#include "PlayScene.h"

#ifdef D2D_WINDOWS
#include <esUtil.h>
#endif

#include "Tools/defs.h"

using namespace motox;

//#define CONTROL_BY_MOVE

PlayScene::PlayScene(d2d::Game* game, d2d::Context* pContext,
					 int scene, int level)
	: d2d::Scene(game, pContext)
	, m_level(pContext, scene, level, m_contactListener)
	, m_actor(pContext)
	, m_debugDraw(NULL)
{
#ifdef D2D_WINDOWS
	m_keyState[0] = m_keyState[1] = m_keyState[2] = m_keyState[3] = false;
#endif
}

PlayScene::~PlayScene()
{
	delete m_debugDraw;

	m_pContext->m_physicsService->open(false);
}

void PlayScene::load()
{
	m_actor.load();
	m_level.load();

	initDebugDraw();

	m_pContext->m_physicsService->setContactImpl(&m_contactListener);

	b2World* world = m_pContext->m_physicsService->getWorld();
	world->SetDebugDraw(m_debugDraw);
	world->SetGravity(b2Vec2(0.0f, -g_gravity));

	m_actor.translate(m_level.getActorStartPos());

	m_pContext->m_physicsService->open(true);
}

void PlayScene::draw() const
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();
	d2d::Vector center = m_actor.getCenterPos();
	glTranslatef(-center.x + (d2d::SCREEN_WIDTH >> 1), -center.y + (d2d::SCREEN_HEIGHT >> 1), 0.0f);

	m_level.draw();
	m_actor.draw();

	////////////////////////////////////////////////////////////////////////////
 	//glEnableClientState(GL_VERTEX_ARRAY);
 	//m_pContext->m_physicsService->getWorld()->DrawDebugData();
 	//glDisableClientState(GL_VERTEX_ARRAY);
	////////////////////////////////////////////////////////////////////////////

	glPopMatrix();
}

void PlayScene::update()
{
	bool backToParent = updateInput();

	m_actor.update();
	m_actor.driving(m_keyState);

	m_level.update(d2d::Vector(m_actor.getCenterPos().x, m_actor.getCenterPos().y + /*100*/ 10));

#ifdef D2D_FRAME_RATE
	logFrameRate();
#endif // D2D_FRAME_RATE

	if (backToParent)
	{
		if (m_parent) m_parent->load();
		m_game->setScene(m_parent);
	}
}

#ifdef D2D_WINDOWS
void PlayScene::onKey(int action, int keyCode)
{
 	if (action == ES_KEY_DOWN)
 	{
 		if (keyCode == VK_LEFT)
 			m_keyState[e_left] = true;
 		if (keyCode == VK_RIGHT)
 			m_keyState[e_right] = true;
 		if (keyCode == VK_UP)
 			m_keyState[e_up] = true;
 		if (keyCode == VK_DOWN)
 			m_keyState[e_down] = true;
 	}
 	else if (action == ES_KEY_UP)
 	{
 		if (keyCode == VK_LEFT)
 			m_keyState[e_left] = false;
 		if (keyCode == VK_RIGHT)
 			m_keyState[e_right] = false;
 		if (keyCode == VK_UP)
 			m_keyState[e_up] = false;
 		if (keyCode == VK_DOWN)
 			m_keyState[e_down] = false;
 	}
}
#endif // D2D_WINDOWS

void PlayScene::initDebugDraw()
{
	if (m_debugDraw) delete m_debugDraw;
	m_debugDraw = new d2d::b2GLESRender(d2d::BOX2D_SCALE_FACTOR);

	uint32 flags = 0;
	flags += b2Draw::e_shapeBit;
	flags += b2Draw::e_jointBit;
	//	flags += b2Draw::e_aabbBit;
	flags += b2Draw::e_pairBit;
	//	flags += b2Draw::e_centerOfMassBit;
	m_debugDraw->SetFlags(flags);		
}

bool  PlayScene::updateInput()
{
	bool backToParent = false;

	const int HALF_WIDTH = m_pContext->m_graphicsService->getWidth() * 0.5f,
		HALF_HEIGHT = m_pContext->m_graphicsService->getHeight() * 0.5f;

#ifdef CONTROL_BY_MOVE
	m_keyState[e_left] = false;
	m_keyState[e_right] = false;
	m_keyState[e_up] = false;
	m_keyState[e_down] = false;
#endif // CONTROL_BY_MOVE

	d2d::EventList& list = m_pContext->m_inputService->getEventList();
	while (!list.empty())
	{
		d2d::Event e = list.pop();
		switch (e.type)
		{
#ifdef CONTROL_BY_MOVE
		case d2d::e_touch_move:
			if (e.pos.x > HALF_WIDTH && e.pos.y > HALF_HEIGHT)
			{
				m_keyState[e_left] = true;
				m_keyState[e_right] = false;
			}
			else if (e.pos.x > HALF_WIDTH && e.pos.y < HALF_HEIGHT)
			{
				m_keyState[e_left] = false;
				m_keyState[e_right] = true;
			}
			else if (e.pos.x < HALF_WIDTH && e.pos.y > HALF_HEIGHT)
			{
				m_keyState[e_down] = true;
				m_keyState[e_up] = false;
			}
			else if (e.pos.x < HALF_WIDTH && e.pos.y < HALF_HEIGHT)
			{
				m_keyState[e_down] = false;
				m_keyState[e_up] = true;
			}
			break;
#else
		case d2d::e_touch_down:
			if (e.pos.x > HALF_WIDTH && e.pos.y > HALF_HEIGHT)
			{
				m_keyState[e_left] = true;
				m_keyState[e_right] = false;
			}
			else if (e.pos.x > HALF_WIDTH && e.pos.y < HALF_HEIGHT)
			{
				m_keyState[e_left] = false;
				m_keyState[e_right] = true;
			}
			else if (e.pos.x < HALF_WIDTH && e.pos.y > HALF_HEIGHT)
			{
				m_keyState[e_down] = true;
				m_keyState[e_up] = false;
			}
			else if (e.pos.x < HALF_WIDTH && e.pos.y < HALF_HEIGHT)
			{
				m_keyState[e_down] = false;
				m_keyState[e_up] = true;
			}
			break;
		case d2d::e_touch_up:
			if (e.pos.x > HALF_WIDTH && e.pos.y > HALF_HEIGHT)
			{
				m_keyState[e_left] = false;
				m_keyState[e_right] = false;
			}
			else if (e.pos.x > HALF_WIDTH && e.pos.y < HALF_HEIGHT)
			{
				m_keyState[e_left] = false;
				m_keyState[e_right] = false;
			}
			else if (e.pos.x < HALF_WIDTH && e.pos.y > HALF_HEIGHT)
			{
				m_keyState[e_down] = false;
				m_keyState[e_up] = false;
			}
			else if (e.pos.x < HALF_WIDTH && e.pos.y < HALF_HEIGHT)
			{
				m_keyState[e_down] = false;
				m_keyState[e_up] = false;
			}
			break;
#endif // CONTROL_BY_MOVE
		case d2d::e_key_down:
			if (e.pos == d2d::Vector(-1, 0))
				m_keyState[e_left] = true;
			else if (e.pos == d2d::Vector(1, 0))
				m_keyState[e_right] = true;
			else if (e.pos == d2d::Vector(0, 1))
				m_keyState[e_up] = true;
			else if (e.pos == d2d::Vector(0, -1))
				m_keyState[e_down] = true;
			break;
		case d2d::e_key_up:
			if (e.pos == d2d::Vector(-1, 0))
				m_keyState[e_left] = false;
			else if (e.pos == d2d::Vector(1, 0))
				m_keyState[e_right] = false;
			else if (e.pos == d2d::Vector(0, 1))
				m_keyState[e_up] = false;
			else if (e.pos == d2d::Vector(0, -1))
				m_keyState[e_down] = false;
			break;
		case d2d::e_key_back_down:
			backToParent = true;
			break;
		case d2d::e_key_menu_down:
			break;
		}
	}

	return backToParent;
}

void PlayScene::logFrameRate()
{
	static float time = 0.0f, totTime = 0.0f;
	static int frame = 0, totFrame = 0;

	float step = m_pContext->m_timeService->elapsed();
	if (step > 1.0f)
	{
		time = totTime = 0;
		frame = totFrame = 0;
		m_pContext->m_timeService->reset();
	}
	else
	{
		time += step;
		totTime += step;
		++frame;
		++totFrame;
		if (time > 1.0f)
		{
			d2d::Log::info("---------------------------------------------");
			d2d::Log::info("tot: %.0f", 1.0f * totFrame / totTime);
			time = 0.0f;
			frame = 0;
		}
	}
}