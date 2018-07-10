#ifndef _WX_GUI_COMPLEX_BODY_H_
#define _WX_GUI_COMPLEX_BODY_H_

#include "IBody.h"
#include "FixtureData.h"

namespace wxgui
{
	class ComplexBody : public IBody
	{
	public:
		ComplexBody(b2World* world, const std::vector<FixtureDataInfo>& fixtures, 
			float scale = 1.0f);

		virtual void getAABB(f2AABB& aabb, const f2Vec2& position, float angle) const;

	}; // ComplexBody
}

#endif // _WX_GUI_COMPLEX_BODY_H_