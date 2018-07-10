#ifndef _FEDITOR_POLYGON_BODY_H_
#define _FEDITOR_POLYGON_BODY_H_
#include "Body.h"

namespace FEDITOR
{
	class BodyData;

	class PolygonBody : public Body
	{
	public:
		PolygonBody(b2World* world, const BodyData& bodyData, float scale = 1.0f);
		PolygonBody(b2World* world, float hWidth, float hHeight, bool isStatic, float scale = 1.0f);
		
		virtual void getAABB(f2AABB& aabb, const f2Vec2& position, float angle) const;

	}; // PolygonBody
}

#endif // _FEDITOR_POLYGON_BODY_H_