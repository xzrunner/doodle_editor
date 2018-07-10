// Only handle image obstacle, not include combine & breakable

#ifndef _MOTOX_SCENE_OBSTACLES2_H_
#define _MOTOX_SCENE_OBSTACLES2_H_

#include "ObstaclesLoader.h"

namespace motox
{
	class Sprite;

	class SceneObstacles2
	{
	public:
		SceneObstacles2(d2d::Context* pContext,
			int scene, int level);
		~SceneObstacles2();

		void draw() const;
		void update(const d2d::Vector& center);

	private:
		void initTextureInfo(d2d::Context* pContext);
		void initObstacles();

	private:
		class SpriteCmp
		{
		public:
			bool operator() (const Sprite* s0, const Sprite* s1) const;
		}; // SpriteCmp

	private:
		ObstaclesLoader m_loader;

		d2d::TextureInfo m_texInfo;

		b2World* m_world;

		d2d::SpriteBatch* m_batch;
		std::vector<Sprite*> m_sprites;

	}; // SceneObstacles2
}

#endif // _MOTOX_SCENE_OBSTACLES2_H_