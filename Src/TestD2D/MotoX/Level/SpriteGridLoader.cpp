#include "SpriteGridLoader.h"

#include "Tools/defs.h"

using namespace motox;

SpriteGridLoader::SpriteGridLoader(d2d::Context* pContext, 
								   const std::string& filename,
								   int scene, int level)
	: m_gridWidth(0)
	, m_leftmost(0)
{
	std::string path_fix = d2d::int2String(scene) + "/" + d2d::int2String(level) + "/";

#ifdef D2D_WINDOWS
	m_filepath = RESOURCE_ROOT + path_fix + filename;

	std::ifstream fin(m_filepath.c_str());
	if (fin.fail()) m_filepath = path_fix + filename;
	fin.close();
#elif defined D2D_ANDROID_NATIVE
	m_pApplication = pContext->m_pApplication;
	m_filepath = path_fix + filename;
#elif defined D2D_ANDROID_JNI
	m_filepath = path_fix + filename;
#endif
}

SpriteGridLoader::~SpriteGridLoader()
{
	clear();
}

void SpriteGridLoader::loadFromFile(bool isSingleLayer)
{
#ifdef D2D_WINDOWS
	d2d::Resource lResource(m_filepath);
#elif defined D2D_ANDROID_NATIVE
	d2d::Resource lResource(m_pApplication, m_filepath);
#elif defined D2D_ANDROID_JNI
	d2d::Resource lResource(m_filepath);
#endif

	if (lResource.open() != d2d::STATUS_OK)
		assert(0);

	const void *buffer = lResource.bufferize();
	assert(buffer);

	clear();

	byte* ptr = static_cast<byte*>(const_cast<void*>(buffer));

	loadHeader(ptr);
	if (isSingleLayer)
		loadData(ptr, m_internal, m_intersect);
	else
		loadData(ptr, m_internals, m_intersects);

	lResource.close();
}

void SpriteGridLoader::clear()
{
	for (size_t i = 0, n = m_internal.size(); i < n; ++i)
		for_each(m_internal[i].begin(), m_internal[i].end(), DeletePointerFunctor<Entry>());
	m_internal.clear();

	for (size_t i = 0, n = m_internal.size(); i < n; ++i)
		for_each(m_intersect[i].begin(), m_intersect[i].end(), DeletePointerFunctor<Entry>());
	m_intersect.clear();
}

void SpriteGridLoader::loadHeader(byte*& ptr)
{
	memcpy(&m_leftmost, ptr, sizeof(float));
	ptr += sizeof(float);
	memcpy(&m_gridWidth, ptr, sizeof(float));
	ptr += sizeof(float);
}

void SpriteGridLoader::loadData(byte*& ptr, Grids& internal, 
								Grids& intersect)
{
	size_t gridSize = 0;
	memcpy(&gridSize, ptr, sizeof(size_t));
	ptr += sizeof(size_t);

	internal.reserve(gridSize);
	for (size_t i = 0; i < gridSize; ++i)
	{
		Grid tiles;
		loadData(ptr, tiles);
		internal.push_back(tiles);
	}

	if (gridSize > 1)
	{
		intersect.reserve(gridSize - 1);
		for (size_t i = 0, n = gridSize - 1; i < n; ++i)
		{
			Grid tiles;
			loadData(ptr, tiles);
			intersect.push_back(tiles);
		}
	}
}

void SpriteGridLoader::loadData(byte*& ptr, std::vector<Grids>& internals,
								std::vector<Grids>& intersects)
{
	size_t size = 0;
	memcpy(&size, ptr, sizeof(size_t));
	ptr += sizeof(size_t);
	for (size_t i = 0; i < size; ++i)
	{
		Grids internal, intersect;
		loadData(ptr, internal, intersect);
		internals.push_back(internal);
		intersects.push_back(intersect);
	}
}

void SpriteGridLoader::loadData(byte*& ptr, Grid& tiles)
{
	size_t tileSize = 0;
	memcpy(&tileSize, ptr, sizeof(size_t));
	ptr += sizeof(size_t);
	tiles.reserve(tileSize);
	for (size_t i = 0; i < tileSize; ++i)
	{
		Entry* tile = new Entry;

		memcpy(&tile->id, ptr, sizeof(int));
		ptr += sizeof(int);

		memcpy(&tile->pos.x, ptr, sizeof(float));
		ptr += sizeof(float);
		memcpy(&tile->pos.y, ptr, sizeof(float));
		ptr += sizeof(float);

		memcpy(&tile->angle, ptr, sizeof(float));
		ptr += sizeof(float);

		memcpy(&tile->scale, ptr, sizeof(float));
		ptr += sizeof(float);

		memcpy(&tile->type, ptr, sizeof(float));
		ptr += sizeof(unsigned int);

		tiles.push_back(tile);
	}
}
