#include "PhysNearQst.h"
#include "PhysOnQst.h"

using namespace FEDITOR;

PhysNearQst::PhysNearQst(b2World* world)
{
	m_world = world;
}

b2Body* PhysNearQst::query(const f2Vec2& pos) const
{
	PhysOnQst query(m_world);
	b2Body* onBody = query.query(pos);
	if (onBody)
	{
		return onBody;
	}
	else
	{
		b2Body* nearBody = NULL;
		float nearDis = FLOAT_MAX;
		for (b2Body* b = m_world->GetBodyList(); b; b = b->GetNext())
		{
			b2Vec2 bPos = b->GetPosition();
			const float dis = f2Math::getDistance(pos, f2Vec2(bPos.x, bPos.y));
			if (dis < nearDis)
			{
				nearDis = dis;
				nearBody = b;
			}
		}
		return nearBody;
	}
}
