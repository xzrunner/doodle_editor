// Group all obstacles to grids

#ifndef _MOTOX_SCENE_OBSTACLES_H_
#define _MOTOX_SCENE_OBSTACLES_H_

#include "SpriteGridLoader.h"

namespace motox
{
	class Sprite;

	class SceneObstacles
	{
	public:
		SceneObstacles(d2d::Context* pContext,
			int scene, int level);
		~SceneObstacles();

		void draw() const;
		void update(const d2d::Vector& center);
		
	private:
		void initTextureInfo(d2d::Context* pContext);
		void initObstacles();

		void computeGridRegion(const d2d::Vector& center, int& left, int& right);

	private:
		class Grid
		{
		public:
			struct Entry
			{
				Entry *prev, *next;
				Sprite* sprite;

				Entry() : prev(NULL), next(NULL), sprite(NULL) {}
			};

		public:
			Grid() : m_header(NULL) {}
			~Grid() { clear(); }

			void loading(const std::vector<SpriteGridLoader::Entry*>& entries, 
				const d2d::TextureInfo& texInfo, b2World* world);

			void setActive(bool flag);

			void loadToBatch(d2d::SpriteBatch* batch, int& index);
			void update(int index, const std::vector<Grid*>& grids, float leftmost, float gridWidth);

			void moveEntryToOtherGrid(Entry* entry, Grid* dst);

			bool empty() const { return m_header == NULL; }

			// debug
			size_t size() const;

		private:
			void clear();

			Sprite* initSprite(SpriteGridLoader::Entry* entry,
				const d2d::TextureInfo& texInfo, b2World* world) const;

		private:
			Entry* m_header;

		};
 
	private:
		SpriteGridLoader m_loader;

		d2d::TextureInfo m_texInfo;

		b2World* m_world;

		d2d::SpriteBatch* m_batch;
		std::vector<Grid*> m_grids;

		size_t m_leftGridID, m_rightGridID;

	}; // SceneObstacles
}

#endif // _MOTOX_SCENE_OBSTACLES_H_