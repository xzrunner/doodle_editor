#ifndef _D2D_PHYSICS_JOINT_H_
#define _D2D_PHYSICS_JOINT_H_

#include <Box2D/Box2D.h>

namespace d2d
{
	class PhysicsJoint
	{
	public:
		virtual ~PhysicsJoint();

	private:
		PhysicsJoint(b2World* world);

	private:
		b2World* m_world;
		b2Joint* m_joint;

		friend class JointFactory;

	}; // PhysicsJoint
}

#endif // _D2D_PHYSICS_JOINT_H_