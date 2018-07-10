#ifndef _MOTOX_SPRITE_H_
#define _MOTOX_SPRITE_H_

#include <Doodle2D/doodle2d.h>

namespace motox
{
	class Sprite
	{
	public:
		Sprite();
		virtual ~Sprite();

		void setTransform(const d2d::Vector& location, float angle);

		void update();

		// only use in SceneObstacles1
		void getAABB(d2d::AABB& aabb) const;

	public:
		d2d::GraphicsSprite* m_graphics;
		d2d::PhysicsBody* m_physics;

		bool m_bDirty;

	}; // Sprite
}

#endif // _MOTOX_SPRITE_H_