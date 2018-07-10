#ifndef _WX_GUI_PHYSICS_QUERY_H_
#define _WX_GUI_PHYSICS_QUERY_H_

#include <Box2D/Box2D.h>
#include <Fruits2D/Fruits2D.h>

namespace wxgui
{
	class PhysicsQuery
	{
	public:
		static b2Body* queryOn(b2World* world, const f2Vec2& pos);
		static b2Body* queryNear(b2World* world, const f2Vec2& pos);

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

	}; // PhysicsQuery
}

#endif // _WX_GUI_PHYSICS_QUERY_H_