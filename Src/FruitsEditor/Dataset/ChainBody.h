#ifndef _FEDITOR_CHAIN_BODY_H_
#define _FEDITOR_CHAIN_BODY_H_
#include "Body.h"

namespace FEDITOR
{
	class BodyData;

	class ChainBody : public Body
	{
	public:
		ChainBody(b2World* world, const BodyData& bodyData, float scale = 1.0f);
		ChainBody(b2World* world, const std::vector<f2Vec2>& vertices, bool isLoop, float scale = 1.0f);
		ChainBody(b2World* world, float scale = 1.0f);

		virtual void getAABB(f2AABB& aabb, const f2Vec2& position, float angle) const;

	}; // ChainBody
}

#endif // _FEDITOR_CHAIN_BODY_H_