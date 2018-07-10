#include "Ship.h"

using namespace dbs;

Ship::Ship(d2d::Context* pContext)
{
	m_inputService = pContext->m_inputService;
	m_graphicsService = pContext->m_graphicsService;
	m_timeService = pContext->m_timeService;

//	m_physics = pContext->m_physicsService->registerEntity(0x2, 0x1, 64, 0.0f);
//	m_target = m_physics->createTarget(50.0f);

#ifdef D2D_WINDOWS
	std::string path = "D:/MyProject/Editor/Project/TestD2D/Data/DroidBlaster/";
	std::string filepath = path + "ship.png";
#elif defined D2D_ANDROID_NATIVE
	std::string filepath = "ship.png";
#elif defined D2D_ANDROID_JNI
	std::string filepath = "ship.png";
#endif
	d2d::Texture* texture = m_graphicsService->registerTexture(filepath);
//	m_sprite = new d2d::FrameAnimSprite(texture, 64, 64, &m_physics->m_location);

//	m_inputService->setRefPoint(&m_physics->m_location);
}

d2d::status Ship::load()
{
	m_sprite->load();
	return d2d::STATUS_OK;
}

void Ship::draw() const
{
	m_sprite->onDraw(m_timeService->elapsed());
}

void Ship::spawn()
{
	const int32_t FRAME_1 = 0; const int32_t FRAME_NB = 8;
	m_sprite->setAnimation(FRAME_1, FRAME_NB, 8.0f, true);
	//m_physics->initialize(m_graphicsService->getWidth() * 1 / 2, 
	//	m_graphicsService->getHeight() * 1 / 4, 0.0f, 0.0f);
}

void Ship::update()
{
//	m_target->setTarget(m_inputService->getHorizontal(), m_inputService->getVertical());
//	if (m_physics->m_collide) 
	{
		d2d::Log::info("Ship has been touched");
	}
}