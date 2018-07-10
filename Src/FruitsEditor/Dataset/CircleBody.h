#ifndef _FEDITOR_CIRCLE_BODY_H_
#define _FEDITOR_CIRCLE_BODY_H_
#include "Body.h"

namespace FEDITOR
{
	class BodyData;

	class CircleBody : public Body
	{
	public:
		CircleBody(b2World* world, const BodyData& bodyData, float scale = 1.0f);
		CircleBody(b2World* world, float radius);

		virtual void getAABB(f2AABB& aabb, const f2Vec2& position, float angle) const;

	}; // CircleBody
}

#endif // _FEDITOR_CIRCLE_BODY_H_