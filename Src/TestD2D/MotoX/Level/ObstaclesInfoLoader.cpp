#include "ObstaclesInfoLoader.h"

#include "Tools/defs.h"

using namespace motox;

ObstaclesInfoLoader::ObstaclesInfoLoader(d2d::Context* pContext, 
										 const std::string& filename,
										 const d2d::TextureInfo& texInfo)
	: m_texInfo(texInfo)
{
#ifdef D2D_WINDOWS
	m_filepath = RESOURCE_ROOT + filename;

	std::ifstream fin(m_filepath.c_str());
	if (fin.fail()) m_filepath = filename;
	fin.close();
#elif defined D2D_ANDROID_NATIVE
	m_pApplication = pContext->m_pApplication;
	m_filepath = filename;
#elif defined D2D_ANDROID_JNI
	m_filepath = filename;
#endif
}

ObstaclesInfoLoader::~ObstaclesInfoLoader()
{
	clear();
}

void ObstaclesInfoLoader::loadFromFile()
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
	loadMeshes(ptr);
	loadCombines(ptr);
	loadBreakables(ptr);
	lResource.close();
}

void ObstaclesInfoLoader::clear()
{
	for_each(m_meshesData.begin(), m_meshesData.end(), DeletePointerFunctor<MeshData>());
	for_each(m_combinesData.begin(), m_combinesData.end(), DeletePointerFunctor<CombineData>());
	for_each(m_breakablesData.begin(), m_breakablesData.end(), DeletePointerFunctor<BreakableData>());

	m_meshesData.clear();
	m_combinesData.clear();
	m_breakablesData.clear();
}

void ObstaclesInfoLoader::loadMeshes(byte*& ptr)
{
	size_t size = 0;
	memcpy(&size, ptr, sizeof(size_t));
	ptr += sizeof(size_t);
	m_meshesData.reserve(size);

	for (size_t i = 0; i < size; ++i)
	{
		MeshData* data = new MeshData;

		memcpy(&data->id, ptr, sizeof(int));
		ptr += sizeof(int);

		const d2d::TextureInfo::Region* pRegion = m_texInfo.getRegion(data->id);
		const float width = m_texInfo.getWidth(),
			height = m_texInfo.getHeight();

		data->mesh = new d2d::Mesh;
		size_t pSize = 0;
		memcpy(&pSize, ptr, sizeof(size_t));
		ptr += sizeof(size_t);
		data->mesh->m_vertices.reserve(pSize);
		for (size_t j = 0; j < pSize; ++j)
		{
			d2d::Vertex vertex;

			memcpy(&vertex.x, ptr, sizeof(float));
			ptr += sizeof(float);
			memcpy(&vertex.y, ptr, sizeof(float));
			ptr += sizeof(float);
			memcpy(&vertex.u, ptr, sizeof(float));
			ptr += sizeof(float);
			memcpy(&vertex.v, ptr, sizeof(float));
			ptr += sizeof(float);

			vertex.u = (pRegion->left + pRegion->width * vertex.u) / width;
			vertex.v = ((height - pRegion->top - pRegion->height) + pRegion->height * vertex.v) / height;

			data->mesh->m_vertices.push_back(vertex);
		}

		memcpy(&data->left, ptr, sizeof(float));
		ptr += sizeof(float); 
		memcpy(&data->right, ptr, sizeof(float));
		ptr += sizeof(float); 
		memcpy(&data->low, ptr, sizeof(float));
		ptr += sizeof(float); 
		memcpy(&data->top, ptr, sizeof(float));
		ptr += sizeof(float); 

		m_meshesData.push_back(data);
	}
}

void ObstaclesInfoLoader::loadCombines(byte*& ptr)
{
	size_t size = 0;
	memcpy(&size, ptr, sizeof(size_t));
	ptr += sizeof(size_t);
	m_combinesData.reserve(size);

	for (size_t i = 0; i < size; ++i)
	{
		CombineData* data = new CombineData;

		size_t pSize = 0;
		memcpy(&pSize, ptr, sizeof(size_t));
		ptr += sizeof(size_t);
		data->entries.reserve(pSize);
		for (size_t j = 0; j < pSize; ++j)
		{
			CombineData::Entry entry;
			
			memcpy(&entry.id, ptr, sizeof(int));
			ptr += sizeof(int);

			memcpy(&entry.pos.x, ptr, sizeof(float));
			ptr += sizeof(float);
			memcpy(&entry.pos.y, ptr, sizeof(float));
			ptr += sizeof(float);
			memcpy(&entry.angle, ptr, sizeof(float));
			ptr += sizeof(float);
			memcpy(&entry.scale, ptr, sizeof(float));
			ptr += sizeof(float);

			data->entries.push_back(entry);
		}

		data->loadFixtures(m_texInfo, m_meshesData);

		m_combinesData.push_back(data);
	}
}

void ObstaclesInfoLoader::loadBreakables(byte*& ptr)
{
	size_t size = 0;
	memcpy(&size, ptr, sizeof(size_t));
	ptr += sizeof(size_t);
	m_breakablesData.reserve(size);

	for (size_t i = 0; i < size; ++i)
	{
		BreakableData* data = new BreakableData;

		memcpy(&data->spritesID, ptr, sizeof(int));
		ptr += sizeof(int);
		memcpy(&data->meshesID, ptr, sizeof(int));
		ptr += sizeof(int);

		m_breakablesData.push_back(data);
	}
}

//////////////////////////////////////////////////////////////////////////
// class ObstaclesInfoLoader::CombineData
//////////////////////////////////////////////////////////////////////////

void ObstaclesInfoLoader::CombineData::loadFixtures(const d2d::TextureInfo& texInfo,
													const std::vector<MeshData*>& meshes)
{
	for (size_t i = 0, n = entries.size(); i < n; ++i)
	{
		const Entry& entry = entries[i];
		if (entry.id < texInfo.regionSize())
		{
			const d2d::TextureInfo::Region* region = texInfo.getRegion(entry.id);

			for (size_t j = 0, m = region->loops.size(); j < m; ++j)
			{
				std::vector<d2d::Vector> loop;
				loop.reserve(region->loops[j].size());
				for (size_t k = 0, l = region->loops[j].size(); k < l; ++k)
				{
					d2d::Vector trans;
					if (entry.scale == 1.0f)
						d2d::rotateVector(region->loops[j][k], entry.angle, trans);
					else
						d2d::rotateVector(region->loops[j][k] * entry.scale, entry.angle, trans);
					trans += entry.pos;
					loop.push_back(trans);
				}
				fixtures.push_back(loop);
			}
		}
		else
		{
			assert(entry.id < texInfo.regionSize() + meshes.size());

			//////////////////////////////////////////////////////////////////////////
			// Probably
			//////////////////////////////////////////////////////////////////////////

			MeshData* data = meshes[entry.id - texInfo.regionSize()];

			std::vector<d2d::Vector> loop(4);
			loop[0] = d2d::Vector(data->left, data->low);
			loop[1] = d2d::Vector(data->right, data->low);
			loop[2] = d2d::Vector(data->right, data->top);
			loop[3] = d2d::Vector(data->left, data->top);
			for (size_t i = 0; i < 4; ++i)
			{
				d2d::Vector trans;
				if (entry.scale == 1.0f)
					d2d::rotateVector(loop[i], entry.angle, trans);
				else
					d2d::rotateVector(loop[i] * entry.scale, entry.angle, trans);
				trans += entry.pos;
				loop[i] = trans;
			}
			fixtures.push_back(loop);

			//////////////////////////////////////////////////////////////////////////
			// Accurate
			//////////////////////////////////////////////////////////////////////////

//			d2d::Mesh* mesh = meshes[entry.id - texInfo.regionSize()]->mesh;
// 			int index = 0;
// 			for (size_t j = 0, m = mesh->m_vertices.size() / 3; j < m; ++j)
// 			{
// 				std::vector<d2d::Vector> loop(3);
// 				for (size_t k = 0; k < 3; ++k)
// 				{
// 					d2d::Vector trans;
// 					d2d::rotateVector(d2d::Vector(mesh->m_vertices[index].x, mesh->m_vertices[index].y) * entry.scale, 
// 						entry.angle, trans);
// 					trans += entry.pos;
// 					loop[k] = trans;
// 					++index;
// 				}
// 				fixtures.push_back(loop);
// 			}
		}
	}
}