#ifndef _D2D_BODY_FACTORY_H_
#define _D2D_BODY_FACTORY_H_

#include "common/Vector.h"
#include "modules/filesystem/PhysicsParser.h"

#include <vector>
#include <Box2D/Box2D.h>

namespace d2d
{
	class PhysicsBody;
		
	class BodyFactory
	{
	public:
		static PhysicsBody* createChains(b2World* world, const std::vector<std::vector<Vector> >& chains);
		static PhysicsBody* createPolygons(b2World* world, const std::vector<std::vector<Vector> >& loops, float scale = 1.0f);
		static PhysicsBody* createCircle(b2World* world, float radius);

		static PhysicsBody* createBody(b2World* world, const PhysicsParser::Body& body);

	}; // BodyFactory
}

#endif // _D2D_BODY_FACTORY_H_