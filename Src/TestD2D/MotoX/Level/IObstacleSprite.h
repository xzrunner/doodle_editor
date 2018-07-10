#ifndef _MOTOX_INTERFACE_OBSTACLE_SPRITE_H_
#define _MOTOX_INTERFACE_OBSTACLE_SPRITE_H_

#include <Doodle2D/doodle2d.h>

namespace motox
{
	class IObstacleSprite : public d2d::Object
	{
	public:
		IObstacleSprite() 
			: m_physics(NULL) {}
		virtual ~IObstacleSprite() {
			delete m_physics;
		}

		virtual void setTransform(const d2d::Vector& location, float angle) {
			if (m_physics)
			{
				b2Vec2 loc;
				loc.x = location.x * d2d::BOX2D_SCALE_FACTOR_INVERSE;
				loc.y = location.y * d2d::BOX2D_SCALE_FACTOR_INVERSE;
				m_physics->getBody()->SetTransform(loc, angle);
			}
		}

		virtual void update() = 0;

		virtual void addToBatch(d2d::MeshBatch* batch) const = 0;

		virtual const d2d::Vector& getPosition() const = 0;
		virtual float getAngle() const = 0;

	public:
		d2d::PhysicsBody* m_physics;

	}; // IObstacleSprite
}

#endif // _MOTOX_INTERFACE_OBSTACLE_SPRITE_H_