#include "PhysOnQst.h"

using namespace FEDITOR;

PhysOnQst::PhysOnQst(b2World* world)
{
	m_world = world;
}

b2Body* PhysOnQst::query(const f2Vec2& pos) const
{
	const b2Vec2 b2Pos(pos.x, pos.y);

	// Make a small box.
	b2AABB aabb;
	b2Vec2 d;
	d.Set(0.001f, 0.001f);
	aabb.lowerBound = b2Pos - d;
	aabb.upperBound = b2Pos + d;

	// Query the world for overlapping shapes.
	QueryCallback callback(b2Pos);
	m_world->QueryAABB(&callback, aabb);

	if (callback.m_fixture)
		return callback.m_fixture->GetBody();
	else
		return NULL;
}

//////////////////////////////////////////////////////////////////////////
// class PhysOnQst::QueryCallback
//////////////////////////////////////////////////////////////////////////

PhysOnQst::QueryCallback::QueryCallback(const b2Vec2& point)
{
	m_point = point;
	m_fixture = NULL;
}

bool PhysOnQst::QueryCallback::ReportFixture(b2Fixture* fixture)
{
	b2Body* body = fixture->GetBody();
	if (body->GetType() == b2_dynamicBody)
	{
		bool inside = fixture->TestPoint(m_point);
		if (inside)
		{
			m_fixture = fixture;

			// We are done, terminate the query.
			return false;
		}
	}

	// Continue the query.
	return true;
}