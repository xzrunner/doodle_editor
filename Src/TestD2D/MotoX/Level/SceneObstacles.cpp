#include "SceneObstacles.h"
#include "SpriteGridScene.h"

#include "Tools/defs.h"
#include "Tools/Sprite.h"

using namespace motox;

SceneObstacles::SceneObstacles(d2d::Context* pContext,
							   int scene, int level)
	: m_loader(pContext, OBSTACLE_DATA_FILENAME, scene, level)
	, m_texInfo(true)
	, m_world(pContext->m_physicsService->getWorld())
	, m_leftGridID(-1)
	, m_rightGridID(-1)
{
	m_loader.loadFromFile(true);
	initTextureInfo(pContext);
	initObstacles();
}

SceneObstacles::~SceneObstacles()
{
	for (size_t i = 0, n = m_grids.size(); i < n; ++i)
		delete m_grids[i];
	m_grids.clear();
}

void SceneObstacles::draw() const
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	m_batch->onDraw();

	glDisable(GL_BLEND);
}

void SceneObstacles::update(const d2d::Vector& center)
{
	int left = 0, right = 0;
	computeGridRegion(center, left, right);

	if (left > right) 
	{
		m_leftGridID = m_rightGridID = -1;
		m_batch->setEndIndex(0);
		return;
	}
//	if (left == m_leftGridID && right == m_rightGridID) return;

	int index = 0;
	for (int i = left; i <= right; ++i)
	{
		m_grids[i]->loadToBatch(m_batch, index);
		m_grids[i]->update(i, m_grids, m_loader.m_leftmost, m_loader.m_gridWidth);
	}
	m_batch->setEndIndex(index);

	if (m_leftGridID == -1 || m_rightGridID == -1)
	{
		for (int i = left; i <= right; ++i)
			m_grids[i]->setActive(true);
	}
	else
	{
		for (int i = m_leftGridID; i < left; ++i)
			m_grids[i]->setActive(false);
		for (int i = m_rightGridID + 1; i <= right; ++i)
			m_grids[i]->setActive(true);
	}

	m_leftGridID = left;
	m_rightGridID = right;	
}

void SceneObstacles::initTextureInfo(d2d::Context* pContext)
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

void SceneObstacles::initObstacles()
{
	m_batch = new d2d::SpriteBatch(m_texInfo.getTexture(), 200, d2d::SpriteBatch::USAGE_STATIC);

	assert(m_loader.m_internal.size() == m_loader.m_intersect.size() + 1);
	m_grids.reserve(m_loader.m_internal.size() + m_loader.m_intersect.size());
	for (size_t i = 0, n = m_loader.m_internal.size(); i < n; ++i)
	{
		Grid* grid = new Grid;
		grid->loading(m_loader.m_internal[i], m_texInfo, m_world);
		m_grids.push_back(grid);
		if (i != m_loader.m_internal.size() - 1)
		{
			Grid* grid = new Grid;
			grid->loading(m_loader.m_intersect[i], m_texInfo, m_world);
			m_grids.push_back(grid);
		}
	}
}

void SceneObstacles::computeGridRegion(const d2d::Vector& center, int& left, int& right)
{
	left = static_cast<int>((center.x - (d2d::SCREEN_WIDTH >> 1) - m_loader.m_leftmost) / m_loader.m_gridWidth);
	left = std::min(std::max(left, 0), (int) (m_loader.m_internal.size() - 1));

	right = static_cast<int>((center.x + (d2d::SCREEN_WIDTH >> 1) - m_loader.m_leftmost) / m_loader.m_gridWidth);
	right = std::max(std::min(right, (int) (m_loader.m_internal.size() - 1)), 0);

	left <<= 1;
	right <<= 1;

	assert(left >= 0 && left < m_grids.size()
		&& right >= 0 && right < m_grids.size());

	if (left > 0) --left;
	if (right < (int)(m_grids.size() - 1)) ++right;

	while (m_grids[left]->empty() && left != (int)(m_grids.size() - 1) && left <= right)
		++left;
	while (m_grids[right]->empty() && right != 0 && left <= right)
		--right;
}

//////////////////////////////////////////////////////////////////////////
// struct SceneObstacles::Grid
//////////////////////////////////////////////////////////////////////////

void SceneObstacles::Grid::
loading(const std::vector<SpriteGridLoader::Entry*>& entries,
		const d2d::TextureInfo& texInfo,
		b2World* world)
{
	clear();

	Entry *last = NULL;
	for (size_t i = 0, n = entries.size(); i < n; ++i)
	{
		Entry* curr = new Entry;
		curr->sprite = initSprite(entries[i], texInfo, world);
		if (i == 0)
		{
			m_header = curr;
		}
		else
		{
			last->next = curr;
			curr->prev = last;
		}
		last = curr;
	}
}

void SceneObstacles::Grid::
setActive(bool flag)
{
	Entry* curr = m_header;
	while (curr)
	{
		curr->sprite->m_physics->getBody()->SetActive(flag);
		curr = curr->next;
	}
}

void SceneObstacles::Grid::
loadToBatch(d2d::SpriteBatch* batch, int& index)
{
	Entry* curr = m_header;
	while (curr)
	{
		batch->add(*curr->sprite->m_graphics, index++);
		curr = curr->next;
	}
}

void SceneObstacles::Grid::
update(int index, const std::vector<Grid*>& grids, float leftmost, float gridWidth)
{
	Entry *curr = m_header, *next;
	while (curr)
	{
		next = curr->next;

		curr->sprite->update();

 		d2d::AABB aabb;
 		curr->sprite->getAABB(aabb);
 
 		const int left = static_cast<int>((aabb.xMin - leftmost) / gridWidth),
			right = static_cast<int>((aabb.xMax - leftmost) / gridWidth);
 
 		if (left == right)
 		{
			if (index & 0x1)
			{
				moveEntryToOtherGrid(curr, grids[left << 1]);
			}
			else
			{
				if ((left << 1) != index)
				{
					moveEntryToOtherGrid(curr, grids[left << 1]);
				}
			}
 		}
 		else
 		{
 			assert(right == left + 1);

			if (index & 0x1)
			{
				if ((left << 1) + 1 != index)
				{
					moveEntryToOtherGrid(curr, grids[(left << 1) + 1]);
				}
			}
			else
			{
				moveEntryToOtherGrid(curr, grids[(left << 1) + 1]);
			}
 		}

		curr = next;
	}
}

void SceneObstacles::Grid::
moveEntryToOtherGrid(Entry* entry, Grid* dst)
{
	if (m_header == entry)
	{
		m_header = entry->next;
	}
	else
	{
		entry->prev->next = entry->next;
		if (entry->next)
			entry->next->prev = entry->prev;
	}

	if (dst->m_header)
	{
		entry->next = dst->m_header;
		dst->m_header->prev = entry;
		entry->prev = NULL;
	}
	else
	{
		entry->prev = entry->next = NULL;
	}
	dst->m_header = entry;
}

size_t SceneObstacles::Grid::
size() const
{
	size_t size = 0;

	Entry* curr = m_header;
	while (curr)
	{
		++size;
		curr = curr->next;
	}

	return size;
}

void SceneObstacles::Grid::
clear()
{
	std::vector<Entry*> entries;
	Entry* curr = m_header;
	while (curr)
	{
		entries.push_back(curr);
		curr = curr->next;
	}

	for (size_t i = 0, n = entries.size(); i < n; ++i)
	{
		delete entries[i]->sprite->m_graphics;
		delete entries[i]->sprite->m_physics;
		delete entries[i];
	}
	m_header = NULL;
}

Sprite* SceneObstacles::Grid::
initSprite(SpriteGridLoader::Entry* entry,
		   const d2d::TextureInfo& texInfo,
		   b2World* world) const
{
	Sprite* sprite = new Sprite;
	const d2d::TextureInfo::Region* region = texInfo.getRegion(entry->id);

	sprite->m_graphics = new d2d::GraphicsSprite(texInfo.getTexture(), region->left, region->top, 
		region->width, region->height, texInfo.getWidth(), texInfo.getHeight());
	sprite->m_physics = d2d::BodyFactory::createPolygons(world, region->loops);
	sprite->m_physics->getBody()->SetActive(false);
	sprite->setTransform(entry->pos, entry->angle);

	return sprite;
}