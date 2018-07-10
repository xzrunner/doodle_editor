#include "SceneObstacles2.h"

#include "Tools/defs.h"
#include "Tools/Sprite.h"

using namespace motox;

SceneObstacles2::SceneObstacles2(d2d::Context* pContext,
								 int scene, int level)
	: m_loader(pContext, OBSTACLE_DATA_FILENAME, scene, level)
	, m_texInfo(true)
	, m_world(pContext->m_physicsService->getWorld())
{
	initTextureInfo(pContext);
	initObstacles();
}

SceneObstacles2::~SceneObstacles2()
{
	for (size_t i = 0, n = m_sprites.size(); i < n; ++i)
	{
		delete m_sprites[i]->m_graphics;
		delete m_sprites[i]->m_physics;
		delete m_sprites[i];
	}
	m_sprites.clear();
}

void SceneObstacles2::draw() const
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_batch->onDraw();

	glDisable(GL_BLEND);
}

// active obstacle individual, may affect its neighbor when many connected
// should active obstacle in group
void SceneObstacles2::update(const d2d::Vector& center)
{
	for (size_t i = 0, n = m_sprites.size(); i < n; ++i)
	{
		//// 1
		//m_sprites[i]->update();
		//m_batch->add(*m_sprites[i]->m_graphics, i);

 		// 2
 		Sprite* sprite = m_sprites[i];
 		if (sprite->m_physics->getBody()->IsActive())
 		{
 			sprite->update();
 			m_batch->add(*sprite->m_graphics, i);
 		}
 		if ((sprite->m_graphics->getLocation().x - center.x) < 500)
 			sprite->m_physics->getBody()->SetActive(true);
 		else
 			sprite->m_physics->getBody()->SetActive(false);
	}
}

void SceneObstacles2::initTextureInfo(d2d::Context* pContext)
{
#ifdef D2D_WINDOWS
	std::string imgPath = RESOURCE_ROOT + OBSTACLE_TEXTURE_FILENAME;

	std::ifstream finImg(imgPath.c_str());
	if (finImg.fail()) imgPath = OBSTACLE_TEXTURE_FILENAME;
	finImg.close();
#elif defined D2D_ANDROID_NATIVE
	std::string imgPath = OBSTACLE_TEXTURE_FILENAME;
#elif defined D2D_ANDROID_JNI
	std::string imgPath = OBSTACLE_TEXTURE_FILENAME;
#endif
	d2d::Texture* texture = pContext->m_graphicsService->registerTexture(imgPath);
	m_texInfo.setTexture(texture);
	texture->load();

#ifdef D2D_WINDOWS
	std::string infoPath = RESOURCE_ROOT + OBSTACLE_TEXTURE_INFO_FILENAME;

	std::ifstream finInfo(infoPath.c_str());
	if (finInfo.fail()) infoPath = OBSTACLE_TEXTURE_INFO_FILENAME;
	finInfo.close();

	m_texInfo.loadFromFile(infoPath);
#elif defined D2D_ANDROID_NATIVE
	std::string infoPath = OBSTACLE_TEXTURE_INFO_FILENAME;
	m_texInfo.loadFromFile(pContext->m_pApplication, infoPath);
#elif defined D2D_ANDROID_JNI
	std::string infoPath = OBSTACLE_TEXTURE_INFO_FILENAME;
	m_texInfo.loadFromFile(infoPath);
#endif
}

void SceneObstacles2::initObstacles()
{
	m_batch = new d2d::SpriteBatch(m_texInfo.getTexture(), 200, d2d::SpriteBatch::USAGE_STATIC);

	m_sprites.reserve(m_loader.m_sprites.size());
	for (size_t i = 0, n = m_loader.m_sprites.size(); i < n; ++i)
	{
		ObstaclesLoader::Entry* entry = m_loader.m_sprites[i];
		if (entry->id >= m_texInfo.regionSize())
			continue;

		Sprite* sprite = new Sprite;
		const d2d::TextureInfo::Region* region = m_texInfo.getRegion(entry->id);

		sprite->m_graphics = new d2d::GraphicsSprite(m_texInfo.getTexture(), region->left, region->top, 
			region->width, region->height, m_texInfo.getWidth(), m_texInfo.getHeight());
		sprite->m_physics = d2d::BodyFactory::createPolygons(m_world, region->loops);
	//	sprite->m_physics->getBody()->SetActive(false);
		sprite->setTransform(entry->pos, entry->angle);

		m_sprites.push_back(sprite);
	}

	std::sort(m_sprites.begin(), m_sprites.end(), SpriteCmp());

	for (size_t i = 0, n = m_sprites.size(); i < n; ++i)
		m_batch->add(*m_sprites[i]->m_graphics, -1);
}

bool SceneObstacles2::SpriteCmp::operator() (const Sprite* s0, const Sprite* s1) const 
{
	return s0->m_graphics->getLocation().x < s1->m_graphics->getLocation().x;
}