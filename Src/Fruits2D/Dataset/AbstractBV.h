#ifndef _F2D_ABSTRACT_BV_H_
#define _F2D_ABSTRACT_BV_H_
#include "../Tools/Tools.h"

namespace F2D
{
	class f2AABB;
	class f2Vec2;

	class AbstractBV : public IObject, public ISerializable
	{
	public:
		
		virtual void initFromAABB(const f2AABB& aabb) = 0;

		virtual bool isValid() const = 0;
		virtual void makeInfinite() = 0;

		virtual void translate(const f2Vec2& offset) = 0;
		virtual void rotate(float delta) = 0;

		virtual void combine(const f2Vec2& pos) = 0;
		virtual void combine(const f2AABB& aabb) = 0;

		virtual bool isContain(const f2Vec2& pos) const = 0;
		virtual bool isIntersect(const f2AABB& aabb) const = 0;

		virtual float area() const = 0;
		virtual float width() const = 0;
		virtual float height() const = 0;
		virtual f2Vec2 center() const = 0;

		virtual void getBoundPos(std::vector<f2Vec2>& bound) const = 0;

	}; // AbstractBV
}

#endif // _F2D_ABSTRACT_BV_H_