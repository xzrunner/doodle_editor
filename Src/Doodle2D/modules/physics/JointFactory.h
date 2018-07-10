#ifndef _D2D_JOINT_FACTORY_H_
#define _D2D_JOINT_FACTORY_H_

#include "modules/filesystem/PhysicsParser.h"

#include <Box2D/Box2D.h>

namespace d2d
{
	class JointFactory
	{
	public:
		static b2Joint* createJoint(b2World* world, const PhysicsParser::Joint& data, 
			const std::vector<b2Body*>& bodies);

	}; // JointFactory
}

#endif // _D2D_JOINT_FACTORY_H_