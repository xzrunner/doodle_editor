#include "Background.h"

using namespace dbs;

Background::Background(d2d::Context* pContext)
{
	m_timeService = pContext->m_timeService;
	m_graphicsService = pContext->m_graphicsService;
#ifdef D2D_WINDOWS
	std::string path = "D:/MyProject/Editor/Project/TestD2D/Data/DroidBlaster/";
	std::string cfg_path = path + "tilemap.tmx";
	std::string img_path = path + "tilemap.png";
#elif defined D2D_ANDROID_NATIVE
	std::string cfg_path = "tilemap.tmx";
	std::string img_path = "tilemap.png";
#elif defined D2D_ANDROID_JNI
	std::string cfg_path = "tilemap.tmx";
	std::string img_path = "tilemap.png";
#endif
	d2d::Texture* texture = m_graphicsService->registerTexture(img_path);
#ifdef D2D_WINDOWS
	m_tileMap = new d2d::TileMap(cfg_path, texture, &m_location);
#elif defined D2D_ANDROID_NATIVE
	m_tileMap = new d2d::TileMap(pContext->m_pApplication, cfg_path, texture, &m_location);
#elif defined D2D_ANDROID_JNI
	m_tileMap = new d2d::TileMap(cfg_path, texture, &m_location);
#endif
	m_animSpeed = 8.0f;
}

d2d::status Background::load()
{
	return m_tileMap->load();
}

void Background::draw() const
{
	m_tileMap->draw();
}

void Background::spawn()
{
	m_location.set(0.0f, 0.0f);
}

void Background::update()
{
	const float SCROLL_PER_SEC = -64.0f;
	float lScrolling = m_timeService->elapsed() * SCROLL_PER_SEC;
	m_location += d2d::Vector(0.0f, lScrolling);
}