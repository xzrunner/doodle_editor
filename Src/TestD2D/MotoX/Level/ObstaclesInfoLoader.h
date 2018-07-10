#ifndef _MOTOX_OBSTACLES_INFO_LOADER_H_
#define _MOTOX_OBSTACLES_INFO_LOADER_H_

#include <Doodle2D/doodle2d.h>

namespace motox
{
	class ObstaclesInfoLoader
	{
	public:
		ObstaclesInfoLoader(d2d::Context* pContext, 
			const std::string& filename,
			const d2d::TextureInfo& texInfo);
		~ObstaclesInfoLoader();

		void loadFromFile();

	private:
		void clear();

		void loadMeshes(byte*& ptr);
		void loadCombines(byte*& ptr);
		void loadBreakables(byte*& ptr);

	public:
		struct MeshData
		{
			int id;
			d2d::Mesh* mesh;

			float left, right, low, top;

			MeshData() : mesh(NULL) {}
			~MeshData() { delete mesh; }

		}; // MeshData

		struct CombineData
		{
			struct Entry
			{
				int id;
				d2d::Vector pos;
				float angle;
				float scale;
			};

			std::vector<Entry> entries;
			std::vector<std::vector<d2d::Vector> > fixtures;

			void loadFixtures(const d2d::TextureInfo& texInfo,
				const std::vector<MeshData*>& meshes);

		}; // CombineData

		struct BreakableData
		{
			int spritesID;
			int meshesID;
		}; // BreakableData

	public:
		std::string m_filepath;
		const d2d::TextureInfo& m_texInfo;

		std::vector<MeshData*> m_meshesData;
		std::vector<CombineData*> m_combinesData;
		std::vector<BreakableData*> m_breakablesData;

	private:
#ifdef D2D_ANDROID_NATIVE
		android_app* m_pApplication;
#endif

	}; // ObstaclesInfoLoader
}

#endif // _MOTOX_OBSTACLES_INFO_LOADER_H_