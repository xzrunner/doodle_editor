#include "Asteroid.h"

using namespace dbs;

Asteroid::Asteroid(d2d::Context* pContext)
{
	m_timeService = pContext->m_timeService;
	m_graphicsService = pContext->m_graphicsService;
	
// 	m_physics = pContext->m_physicsService->registerEntity(
// 		0X1, 0x2, 64, 1.0f
// 		);
#ifdef D2D_WINDOWS
	std::string path = "D:/MyProject/Editor/Project/TestD2D/Data/DroidBlaster/";
	std::string filepath = path + "asteroid.png";
#elif defined D2D_ANDROID_NATIVE
	std::string filepath = "asteroid.png";
#elif defined D2D_ANDROID_JNI
	std::string filepath = "asteroid.png";
#endif
	d2d::Texture* texture = m_graphicsService->registerTexture(filepath);
//	m_sprite = new d2d::FrameAnimSprite(texture, 64, 64, &m_physics->m_location);
}

d2d::status Asteroid::load()
{
	m_sprite->load();
	return d2d::STATUS_OK;
}

void Asteroid::draw() const
{
	m_sprite->onDraw(m_timeService->elapsed());
}

void Asteroid::spawn()
{
	const float MIN_VELOCITY = 1.0f, VELOCITY_RANGE=19.0f;
	const float MIN_ANIM_SPEED = 8.0f, ANIM_SPEED_RANGE = 16.0f;

	float lVelocity = -(d2d::RAND(VELOCITY_RANGE) + MIN_VELOCITY);
	float lPosX = d2d::RAND(m_graphicsService->getWidth());
	float lPosY = d2d::RAND(m_graphicsService->getHeight()) + m_graphicsService->getHeight();
//	m_physics->initialize(lPosX, lPosY, 0.0f, lVelocity);

	float lAnimSpeed = MIN_ANIM_SPEED + d2d::RAND(ANIM_SPEED_RANGE);
	m_sprite->setAnimation(8, -1, lAnimSpeed, true);
}

void Asteroid::update()
{
	//if ((m_physics->m_location.x < 0.0f) ||
	//	(m_physics->m_location.x > m_graphicsService->getWidth())||
	//	(m_physics->m_location.y < 0.0f) ||
	//	(m_physics->m_location.y > m_graphicsService->getHeight()*2))
	//{
	//	spawn();
	//}
}