#include "ObstaclesLoader.h"

#include "Tools/defs.h"

using namespace motox;

ObstaclesLoader::ObstaclesLoader(d2d::Context* pContext, 
								 const std::string& filename,
								 int scene, int level)
{
	std::string path_fix = d2d::int2String(scene) + "/" + d2d::int2String(level) + "/";

#ifdef D2D_WINDOWS
	std::string path = RESOURCE_ROOT + path_fix + filename;

	std::ifstream fin(path.c_str());
	if (fin.fail()) path = path_fix + filename;
	fin.close();
#elif defined D2D_ANDROID_NATIVE
	m_pApplication = pContext->m_pApplication;
	std::string path = path_fix + filename;
#elif defined D2D_ANDROID_JNI
	std::string path = path_fix + filename;
#endif
	loadFromFile(path);
}

ObstaclesLoader::~ObstaclesLoader()
{
	clear();
}

void ObstaclesLoader::clear()
{
	for_each(m_sprites.begin(), m_sprites.end(), DeletePointerFunctor<Entry>());
	m_sprites.clear();
}

void ObstaclesLoader::loadFromFile(const std::string& filepath)
{
#ifdef D2D_WINDOWS
	d2d::Resource lResource(filepath);
#elif defined D2D_ANDROID_NATIVE
	d2d::Resource lResource(m_pApplication, filepath);
#elif defined D2D_ANDROID_JNI
	d2d::Resource lResource(filepath);
#endif

	if (lResource.open() != d2d::STATUS_OK)
		assert(0);

	const void *buffer = lResource.bufferize();
	assert(buffer);

	clear();

	byte* ptr = static_cast<byte*>(const_cast<void*>(buffer));

	size_t size = 0;
	memcpy(&size, ptr, sizeof(size_t));
	ptr += sizeof(size_t);
	m_sprites.reserve(size);
	for (size_t i = 0; i < size; ++i)
	{
		Entry* entry = new Entry;

		memcpy(&entry->id, ptr, sizeof(int));
		ptr += sizeof(int);

		memcpy(&entry->pos.x, ptr, sizeof(float));
		ptr += sizeof(float);
		memcpy(&entry->pos.y, ptr, sizeof(float));
		ptr += sizeof(float);

		memcpy(&entry->angle, ptr, sizeof(float));
		ptr += sizeof(float);

		memcpy(&entry->scale, ptr, sizeof(float));
		ptr += sizeof(float);

		memcpy(&entry->type, ptr, sizeof(float));
		ptr += sizeof(unsigned int);

		m_sprites.push_back(entry);
	}

	lResource.close();
}