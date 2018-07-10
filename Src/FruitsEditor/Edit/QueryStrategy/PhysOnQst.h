#ifndef _FEDITOR_PHYSICS_ON_QUERY_STRATEGY_H_
#define _FEDITOR_PHYSICS_ON_QUERY_STRATEGY_H_
#include <Box2D/Box2D.h>
#include <Fruits2D/Fruits2D.h>

namespace FEDITOR
{
	class PhysOnQst
	{
	public:
		PhysOnQst(b2World* world);

		b2Body* query(const f2Vec2& pos) const;

	private:
		class QueryCallback : public b2QueryCallback
		{
		public:
			QueryCallback(const b2Vec2& point);

			bool ReportFixture(b2Fixture* fixture);

		public:
	 		b2Vec2 m_point;
	 		b2Fixture* m_fixture;

		}; // QueryCallback

	private:
		b2World* m_world;

	}; // PhysOnQst
}

#endif // _FEDITOR_PHYSICS_ON_QUERY_STRATEGY_H_