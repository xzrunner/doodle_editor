#ifndef _WX_GUI_CHAIN_BODY_H_
#define _WX_GUI_CHAIN_BODY_H_
#include "IBody.h"

namespace wxgui
{
	class BodyData;

	class ChainBody : public IBody
	{
	public:
		ChainBody(b2World* world, const BodyData& bodyData, float scale = 1.0f);
		ChainBody(b2World* world, const std::vector<f2Vec2>& vertices, bool isLoop, float scale = 1.0f);
		ChainBody(b2World* world, float scale = 1.0f);

		virtual void getAABB(f2AABB& aabb, const f2Vec2& position, float angle) const;

	}; // ChainBody
}

#endif // _WX_GUI_CHAIN_BODY_H_