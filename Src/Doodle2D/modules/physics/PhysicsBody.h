#ifndef _D2D_PHYSICS_BODY_H_
#define _D2D_PHYSICS_BODY_H_

#include <Box2D/Box2D.h>

namespace d2d
{
	class PhysicsBody
	{
	public:
		virtual ~PhysicsBody();

		void setDensity(float density);
		void setFriction(float friction);
		void setCollisionFilter(const b2Filter& filter);

		b2Body* getBody() { return m_body; }

	private:
		PhysicsBody(b2World* world);

	private:
		b2World* m_world;
		b2Body* m_body;

		friend class BodyFactory;

	}; // PhysicsBody
}

#endif // _D2D_PHYSICS_BODY_H_