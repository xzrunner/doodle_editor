#include "SceneObstacles3.h"
#include "CommonSprite.h"
#include "MeshSprite.h"
#include "CombinationSprite.h"
#include "BreakableSprite.h"

#include "Frame/ContactListener.h"
#include "Tools/connect_id_defs.h"
#include "Tools/defs.h"

using namespace motox;

SceneObstacles3::SceneObstacles3(d2d::Context* pContext,
								 int scene, int level,
								 ContactListener& contactListener)
	: m_contactListener(contactListener)
	, m_texInfo(true)
	, m_infoLoader(pContext, OBSTACLE_INFO_FILENAME, m_texInfo)
	, m_dataLoader(pContext, OBSTACLE_DATA_FILENAME, scene, level)
	, m_world(pContext->m_physicsService->getWorld())
{
	initTextureInfo(pContext);
	initObstacles();
}

SceneObstacles3::~SceneObstacles3()
{
	std::list<IObstacleSprite*>::iterator itr = m_obstacles.begin();
	for ( ; itr != m_obstacles.end(); ++itr)
		(*itr)->release();
	m_obstacles.clear();
}

void SceneObstacles3::draw() const
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_batch->onDraw();

	glDisable(GL_BLEND);
}

void SceneObstacles3::update(const d2d::Vector& center)
{
	handleBreakableSprites();

	m_batch->setEndIndex(0);
	size_t index = 0;

	std::list<IObstacleSprite*>::iterator itr = m_obstacles.begin();
	for ( ; itr != m_obstacles.end(); )
	{
		const float x = (*itr)->getPosition().x;
		if (x < center.x - 600)
		{
 			(*itr)->release();
 			itr = m_obstacles.erase(itr);
		}
		else if (x > center.x + 600)
		{
 			if ((*itr)->m_physics)
 				(*itr)->m_physics->getBody()->SetActive(false);
 			++itr;
		}
		else
		{
			if ((*itr)->m_physics)
			{
				b2Body* body = (*itr)->m_physics->getBody();
				void* data = body->GetUserData();
				if (data && *static_cast<int*>(data) == PIECE_ID && !body->IsAwake())
				{
	 				delete (*itr)->m_physics;
	 				(*itr)->m_physics = NULL;
				}
				else
				{
					(*itr)->m_physics->getBody()->SetActive(true);
				}
			}

			(*itr)->update();
			(*itr)->addToBatch(m_batch);
			++itr;
		}
	}
}

void SceneObstacles3::initTextureInfo(d2d::Context* pContext)
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

void SceneObstacles3::initObstacles()
{
	m_infoLoader.loadFromFile();

//	m_batch = new d2d::SpriteBatch(m_texInfo.getTexture(), 200, d2d::SpriteBatch::USAGE_STATIC);
	m_batch = new d2d::MeshBatch(m_texInfo.getTexture(), 2000, d2d::SpriteBatch::USAGE_STATIC);

	for (size_t i = 0, n = m_dataLoader.m_sprites.size(); i < n; ++i)
	{
		ObstaclesLoader::Entry* entry = m_dataLoader.m_sprites[i];
		if (isCommonSprite(entry->id))
			loadCommonSprite(entry->id, entry->pos, entry->angle);
		else if (isCombinationSprite(entry->id))
			loadCombinationSprite(entry->id, entry->pos, entry->angle);
		else if (isBreakableSprite(entry->id))
			loadBreakableSprite(entry->id, entry->pos, entry->angle);
		else
			assert(0);
	}

	std::list<IObstacleSprite*>::iterator itr = m_obstacles.begin();
	for ( ; itr != m_obstacles.end(); ++itr)
		(*itr)->addToBatch(m_batch);
}

bool SceneObstacles3::isCommonSprite(int id) const
{
	return id < m_texInfo.regionSize();
}

bool SceneObstacles3::isCombinationSprite(int id) const
{
	return id >= m_texInfo.regionSize() 
		&& id < m_texInfo.regionSize() + m_infoLoader.m_combinesData.size();
}

bool SceneObstacles3::isBreakableSprite(int id) const
{
	return id >= m_texInfo.regionSize() + m_infoLoader.m_combinesData.size()
		&& id < m_texInfo.regionSize() + m_infoLoader.m_combinesData.size() + m_infoLoader.m_breakablesData.size();
}

void SceneObstacles3::loadCommonSprite(int id, const d2d::Vector& pos, float angle)
{
	CommonSprite* sprite = new CommonSprite;
	const d2d::TextureInfo::Region* region = m_texInfo.getRegion(id);

	sprite->m_texID = id;
	sprite->m_graphics = new d2d::GraphicsSprite(m_texInfo.getTexture(), region->left, region->top, 
		region->width, region->height, m_texInfo.getWidth(), m_texInfo.getHeight());
	sprite->m_physics = d2d::BodyFactory::createPolygons(m_world, region->loops);
	sprite->setTransform(pos, angle);

	m_obstacles.push_back(sprite);	
}

void SceneObstacles3::loadCombinationSprite(int id, const d2d::Vector& pos, float angle)
{
	CombinationSprite* sprite = new CombinationSprite;
	loadCombinationSprite(sprite, id, pos, angle);
	m_obstacles.push_back(sprite);
}

void SceneObstacles3::loadBreakableSprite(int id, const d2d::Vector& pos, float angle)
{
	ObstaclesInfoLoader::BreakableData* data = m_infoLoader.m_breakablesData[id - m_texInfo.regionSize() - m_infoLoader.m_combinesData.size()];
	BreakableSprite* sprite = new BreakableSprite(m_world, m_texInfo, m_infoLoader, data->meshesID);
	if (data->spritesID == -1)
	{
		sprite->setBreakType(false);
		loadCombinationSprite(sprite, data->meshesID + m_texInfo.regionSize(), pos, angle);
	}
	else
	{
		sprite->setBreakType(true);
		loadCombinationSprite(sprite, data->spritesID + m_texInfo.regionSize(), pos, angle);
	}
	sprite->m_physics->getBody()->SetUserData(new int(BREAKABLE_ID));
	sprite->update();
	m_obstacles.push_back(sprite);
}

void SceneObstacles3::loadCombinationSprite(CombinationSprite* sprite, int id, 
											const d2d::Vector& pos, float angle)
{
	ObstaclesInfoLoader::CombineData* data = m_infoLoader.m_combinesData[id - m_texInfo.regionSize()];
	for (size_t i = 0, n = data->entries.size(); i < n; ++i)
	{
		CombinationSprite::Part* part = new CombinationSprite::Part;
		if (data->entries[i].id < m_texInfo.regionSize())
		{
			const d2d::TextureInfo::Region* region = m_texInfo.getRegion(data->entries[i].id);
			CommonSprite* sprite = new CommonSprite;
			sprite->m_texID = data->entries[i].id;
			sprite->m_graphics = new d2d::GraphicsSprite(m_texInfo.getTexture(), region->left, region->top, 
				region->width, region->height, m_texInfo.getWidth(), m_texInfo.getHeight(), data->entries[i].scale);
			part->sprite = sprite;
		}
		else
		{
			assert(data->entries[i].id < m_texInfo.regionSize() + m_infoLoader.m_meshesData.size());
			MeshSprite* sprite = new MeshSprite(data->entries[i].scale);
			sprite->m_meshID = data->entries[i].id - m_texInfo.regionSize();
			sprite->m_mesh = m_infoLoader.m_meshesData[sprite->m_meshID]->mesh;
			part->sprite = sprite;
		}
		part->offset = data->entries[i].pos;
		part->delta = data->entries[i].angle;
		part->scale = data->entries[i].scale;

		sprite->m_children.push_back(part);
	}
	sprite->m_physics = d2d::BodyFactory::createPolygons(m_world, data->fixtures);
	sprite->setTransform(pos, angle);
}

void SceneObstacles3::handleBreakableSprites()
{
	std::map<b2Body*, d2d::Vector>::iterator itr = m_contactListener.m_breakCache.begin();
	for ( ; itr != m_contactListener.m_breakCache.end(); ++itr)
	{
		b2Body* body = itr->first;

		std::list<IObstacleSprite*>::iterator itrObstacle = m_obstacles.begin();
		for ( ; itrObstacle != m_obstacles.end(); ++itrObstacle)
		{
			if ((*itrObstacle)->m_physics && (*itrObstacle)->m_physics->getBody() == body)
			{
 				BreakableSprite* sprite = static_cast<BreakableSprite*>(*itrObstacle);
 				std::vector<IObstacleSprite*> pieces;
 				sprite->breakToPieces(itr->second, pieces);
 
				(*itrObstacle)->release();
 				m_obstacles.erase(itrObstacle);
				m_obstacles.insert(m_obstacles.end(), pieces.begin(), pieces.end());
 
 				break;
			}
		}
	}

	m_contactListener.m_breakCache.clear();
}