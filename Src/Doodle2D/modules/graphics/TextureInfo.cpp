#include "TextureInfo.h"

#include "common/tools.h"
#include "common/Resource.h"

#include <assert.h>

using namespace d2d;

TextureInfo::TextureInfo(bool hasBoundaryInfo)
	: m_texture(NULL)
	, m_hasBoundaryInfo(hasBoundaryInfo)
	, m_width(0)
	, m_height(0) 
{
}

TextureInfo::~TextureInfo()
{
	clear();
}

void TextureInfo::setSizer(int width, int height)
{
	m_width = width;
	m_height = height;
}

void TextureInfo::addRegion(int left, int top, int width, int height)
{
	m_regions.push_back(new Region(left, top, width, height));
}

const TextureInfo::Region* TextureInfo::getRegion(int index) const
{
	if (index >= 0 && index < (int)(m_regions.size()))
		return m_regions[index];
	else
		return NULL;
}

void TextureInfo::loadFromMemory(byte** ptr)
{
	clear();

	memcpy(&m_width, *ptr, sizeof(int));
	*ptr += sizeof(int);
	memcpy(&m_height, *ptr, sizeof(int));
	*ptr += sizeof(int);

	size_t size = 0;
	memcpy(&size, *ptr, sizeof(int));
	*ptr += sizeof(int);
	m_regions.reserve(size);
	for (size_t i = 0; i < size; ++i)
	{
		Region* region = new Region;

		memcpy(&region->left, *ptr, sizeof(int));
		*ptr += sizeof(int);
		memcpy(&region->top, *ptr, sizeof(int));
		*ptr += sizeof(int);
		memcpy(&region->width, *ptr, sizeof(int));
		*ptr += sizeof(int);
		memcpy(&region->height, *ptr, sizeof(int));
		*ptr += sizeof(int);

		if (m_hasBoundaryInfo)
			loadBoundary(ptr, region);

		m_regions.push_back(region);
	}
}

#ifdef D2D_WINDOWS
void TextureInfo::loadFromFile(const std::string& filepath)
{
	Resource lResource(filepath);

	if (lResource.open() != d2d::STATUS_OK)
		assert(0);

	const void *buffer = lResource.bufferize();
	assert(buffer);

	byte* ptr = static_cast<byte*>(const_cast<void*>(buffer));
	loadFromMemory(&ptr);

	lResource.close();
}
#elif defined D2D_ANDROID_NATIVE
void TextureInfo::loadFromFile(android_app* pApplication, const std::string& filepath)
{
	Resource lResource(pApplication, filepath);

	if (lResource.open() != d2d::STATUS_OK)
		assert(0);

	const void *buffer = lResource.bufferize();
	assert(buffer);

	byte* ptr = static_cast<byte*>(const_cast<void*>(buffer));
	loadFromMemory(&ptr);

	lResource.close();
}
#elif defined D2D_ANDROID_JNI
void TextureInfo::loadFromFile(const std::string& filepath)
{
	Resource lResource(filepath);

	if (lResource.open() != d2d::STATUS_OK)
		assert(0);

	const void *buffer = lResource.bufferize();
	assert(buffer);

	byte* ptr = static_cast<byte*>(const_cast<void*>(buffer));
	loadFromMemory(&ptr);

	lResource.close();
}
#endif

void TextureInfo::clear()
{
	for_each(m_regions.begin(), m_regions.end(), DeletePointerFunctor<Region>());
	m_regions.clear();
}

void TextureInfo::loadBoundary(byte** ptr, Region* region)
{
	int flag = 0;
	memcpy(&flag, *ptr, sizeof(int));
	*ptr += sizeof(int);
	switch (flag)
	{
	case 0:
		break;
	case 1:
		loadPolygonInfo(ptr, region);	
		break;
	case 2:
		loadCircleInfo(ptr, region);
		break;
	default:
		assert(0);
	}
}

void TextureInfo::loadPolygonInfo(byte** ptr, Region* region)
{
	size_t loopSize = 0;
	memcpy(&loopSize, *ptr, sizeof(int));
	*ptr += sizeof(int);
	for (size_t i = 0; i < loopSize; ++i)
	{
		size_t posSize = 0;
		memcpy(&posSize, *ptr, sizeof(int));
		*ptr += sizeof(int);

		std::vector<Vector> loop;
		loop.reserve(posSize);
		for (size_t j = 0; j < posSize; ++j)
		{
			Vector pos;
			memcpy(&pos.x, *ptr, sizeof(float));
			*ptr += sizeof(float);
			memcpy(&pos.y, *ptr, sizeof(float));
			*ptr += sizeof(float);
			loop.push_back(pos);
		}

		region->loops.push_back(loop);
	}
}

void TextureInfo::loadCircleInfo(byte** ptr, Region* region)
{
	int width = 0;
	memcpy(&width, *ptr, sizeof(int));
	*ptr += sizeof(int);
}
