#include "GroundSurfaceLoader.h"

#include "Tools/defs.h"

using namespace motox;

GroundSurfaceLoader::GroundSurfaceLoader(d2d::Context* pContext,
										 int scene, int level)
	: m_gridWidth(0)
	, m_leftmost(0)
{
	std::string path_fix = d2d::int2String(scene) + "/" + d2d::int2String(level) + "/";

#ifdef D2D_WINDOWS
	std::string path = RESOURCE_ROOT + path_fix + GROUND_SURFACE_FILENAME;

	std::ifstream fin(path.c_str());
	if (fin.fail()) path = path_fix + GROUND_SURFACE_FILENAME;
	fin.close();
#elif defined D2D_ANDROID_NATIVE
	m_pApplication = pContext->m_pApplication;
	std::string path = path_fix + GROUND_SURFACE_FILENAME;
#elif defined D2D_ANDROID_JNI
	std::string path = path_fix + GROUND_SURFACE_FILENAME;
#endif
	loadFromFile(path);
}

GroundSurfaceLoader::~GroundSurfaceLoader()
{
	clear();
}

void GroundSurfaceLoader::loadFromFile(const std::string& filename)
{
#ifdef D2D_WINDOWS
	d2d::Resource lResource(filename);
#elif defined D2D_ANDROID_NATIVE
	d2d::Resource lResource(m_pApplication, filename);
#elif defined D2D_ANDROID_JNI
	d2d::Resource lResource(filename);
#endif

	if (lResource.open() != d2d::STATUS_OK)
		assert(0);

	const void *buffer = lResource.bufferize();
	assert(buffer);

	clear();

	byte* ptr = static_cast<byte*>(const_cast<void*>(buffer));

	memcpy(&m_leftmost, ptr, sizeof(float));
	ptr += sizeof(float);
	memcpy(&m_gridWidth, ptr, sizeof(float));
	ptr += sizeof(float);

	size_t gridSize = 0;
	memcpy(&gridSize, ptr, sizeof(size_t));
	ptr += sizeof(size_t);
	m_grids.reserve(gridSize);
	for (size_t i = 0; i < gridSize; ++i)
	{
		Grid* grid = new Grid;

		size_t colorSize = 0;
		memcpy(&colorSize, ptr, sizeof(size_t));
		ptr += sizeof(size_t);
		grid->colorBlocks.reserve(colorSize);
		for (size_t j = 0; j < colorSize; ++j)
			grid->colorBlocks.push_back(loadColorBlock(ptr));

		size_t textureSize = 0;
		memcpy(&textureSize, ptr, sizeof(size_t));
		ptr += sizeof(size_t);
		grid->textureBlocks.reserve(textureSize);
		for (size_t j = 0; j < textureSize; ++j)
			grid->textureBlocks.push_back(loadTextureBlock(ptr));

		m_grids.push_back(grid);
	}

	lResource.close();
}

GroundSurfaceLoader::ColorBlock* GroundSurfaceLoader::loadColorBlock(byte*& ptr)
{
	ColorBlock* block = new ColorBlock;

	unsigned int color = 0;
	memcpy(&color, ptr, sizeof(unsigned int));
	ptr += sizeof(unsigned int);
	block->color.unpack(color);
// 	block->color.r = 255;
// 	block->color.g = 255;
// 	block->color.b = 0;
// 	block->color.a = 255;

	loadVerticeIndices(ptr, block->vertices, block->indices);

	return block;
}

GroundSurfaceLoader::TextureBlock* GroundSurfaceLoader::loadTextureBlock(byte*& ptr)
{
	TextureBlock* block = new TextureBlock;

	block->id = 0;
	memcpy(&block->id, ptr, sizeof(unsigned int));
	ptr += sizeof(unsigned int);

	size_t verticesSize = 0;
	memcpy(&verticesSize, ptr, sizeof(size_t));
	ptr += sizeof(size_t);
	block->vertices.reserve(verticesSize);
	for (size_t i = 0; i < verticesSize; ++i)
	{
		d2d::Vector pos;
		memcpy(&pos.x, ptr, sizeof(float));
		ptr += sizeof(float);
		memcpy(&pos.y, ptr, sizeof(float));
		ptr += sizeof(float);
		block->vertices.push_back(pos);
	}

	size_t textureSize = 0;
	memcpy(&textureSize, ptr, sizeof(size_t));
	ptr += sizeof(size_t);
	block->texCoords.reserve(textureSize);
	for (size_t i = 0; i < textureSize; ++i)
	{
		d2d::Vector pos;
		memcpy(&pos.x, ptr, sizeof(float));
		ptr += sizeof(float);
		memcpy(&pos.y, ptr, sizeof(float));
		// fix y-flip
		pos.y = 1.0f - pos.y;
		ptr += sizeof(float);
		block->texCoords.push_back(pos);
	}

	return block;
}

void GroundSurfaceLoader::loadVerticeIndices(byte*& ptr, std::vector<d2d::Vector>& vertices, std::vector<unsigned short>& indices)
{
	size_t verticesSize = 0;
	memcpy(&verticesSize, ptr, sizeof(size_t));
	ptr += sizeof(size_t);
	vertices.clear();
	vertices.reserve(verticesSize);
	for (size_t i = 0; i < verticesSize; ++i)
	{
		d2d::Vector pos;
		memcpy(&pos.x, ptr, sizeof(float));
		ptr += sizeof(float);
		memcpy(&pos.y, ptr, sizeof(float));
		ptr += sizeof(float);
		vertices.push_back(pos);
	}

	size_t indicesSize = 0;
	memcpy(&indicesSize, ptr, sizeof(size_t));
	ptr += sizeof(size_t);
	indices.clear();
	indices.reserve(indicesSize);
	for (size_t i = 0; i < indicesSize; ++i)
	{
		int index = 0;
		memcpy(&index, ptr, sizeof(int));
		ptr += sizeof(int);
		indices.push_back(index);
	}
}

void GroundSurfaceLoader::clear()
{
	for_each(m_grids.begin(), m_grids.end(), DeletePointerFunctor<Grid>());
	m_grids.clear();
}