#ifndef _FEDITOR_SHAPE_H_
#define _FEDITOR_SHAPE_H_
#include <Fruits2D/Fruits2D.h>
#include "ShapeTypes.h"

namespace FEDITOR
{
	class Shape : public IObject, public ISerializable
	{
	public:
		Shape(SHAPE_TYPE type);
		virtual ~Shape() {}

		virtual bool isContain(const f2Vec2& pos, float scale) const = 0;
		virtual void getAABB(f2AABB& aabb, const f2Vec2& position, float angle) const = 0;

		SHAPE_TYPE getType() const;

	protected:
		static const float QUERY_ACCURACY;

	protected:
		SHAPE_TYPE m_type;
		
	}; // Shape

	inline Shape::Shape(SHAPE_TYPE type)
	{
		m_type = type;
	}

	inline SHAPE_TYPE Shape::getType() const
	{
		return m_type;
	}
}

#endif // _FEDITOR_SHAPE_H_