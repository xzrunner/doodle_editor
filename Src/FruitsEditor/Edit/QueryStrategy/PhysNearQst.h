#ifndef _FEDITOR_PHYSICS_NEAR_QUERY_STRATEGY_H_
#define _FEDITOR_PHYSICS_NEAR_QUERY_STRATEGY_H_
#include <Box2D/Box2D.h>
#include <Fruits2D/Fruits2D.h>

namespace FEDITOR
{
	class PhysNearQst
	{
	public:
		PhysNearQst(b2World* world);

		b2Body* query(const f2Vec2& pos) const;

	private:
		b2World* m_world;

	}; // PhysNearQst
}

#endif // _FEDITOR_PHYSICS_NEAR_QUERY_STRATEGY_H_