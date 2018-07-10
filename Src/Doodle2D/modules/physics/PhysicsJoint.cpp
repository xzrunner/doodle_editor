#include "PhysicsJoint.h"

using namespace d2d;

PhysicsJoint::PhysicsJoint(b2World* world)
	: m_world(world)
	, m_joint(NULL)
{
}

PhysicsJoint::~PhysicsJoint()
{
	if (m_joint)
	{
		m_world->DestroyJoint(m_joint);
		m_joint = NULL;
	}
}