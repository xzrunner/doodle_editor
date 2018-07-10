// Handle all types

#ifndef _MOTOX_SCENE_OBSTACLES3_H_
#define _MOTOX_SCENE_OBSTACLES3_H_

#include "ObstaclesLoader.h"
#include "ObstaclesInfoLoader.h"

#include <list>

namespace motox
{
	class ContactListener;
	class IObstacleSprite;
	class CombinationSprite;

	class SceneObstacles3
	{
	public:
		SceneObstacles3(d2d::Context* pContext,
			int scene, int level,
			ContactListener& contactListener);
		~SceneObstacles3();

		void draw() const;
		void update(const d2d::Vector& center);

	private:
		void initTextureInfo(d2d::Context* pContext);
		void initObstacles();

		bool isCommonSprite(int id) const;
		bool isCombinationSprite(int id) const;
		bool isBreakableSprite(int id) const;

		void loadCommonSprite(int id, const d2d::Vector& pos, float angle);
		void loadCombinationSprite(int id, const d2d::Vector& pos, float angle);
		void loadBreakableSprite(int id, const d2d::Vector& pos, float angle);

		void loadCombinationSprite(CombinationSprite* sprite, 
			int id, const d2d::Vector& pos, float angle);

		void handleBreakableSprites();

	private:
		ContactListener& m_contactListener;

		d2d::TextureInfo m_texInfo;

		ObstaclesInfoLoader m_infoLoader;
		ObstaclesLoader m_dataLoader;

		b2World* m_world;

		d2d::MeshBatch* m_batch;
		std::list<IObstacleSprite*> m_obstacles;

	}; // SceneObstacles3
}

#endif // _MOTOX_SCENE_OBSTACLES3_H_