#ifndef _WX_GUI_CIRCLE_BODY_H_
#define _WX_GUI_CIRCLE_BODY_H_

#include "IBody.h"

namespace wxgui
{
	class BodyData;

	class CircleBody : public IBody
	{
	public:
		CircleBody(b2World* world, const BodyData& bodyData, float scale = 1.0f);
		CircleBody(b2World* world, float radius);

		virtual void getAABB(f2AABB& aabb, const f2Vec2& position, float angle) const;

	}; // CircleBody
}

#endif // _WX_GUI_CIRCLE_BODY_H_