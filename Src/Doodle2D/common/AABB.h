#ifndef _D2D_AABB_H_
#define _D2D_AABB_H_

#include "Vector.h"

namespace d2d
{
	class AABB
	{
	public:
		float xMin, xMax;
		float yMin, yMax;

		AABB() { makeInfinite(); }

		void makeInfinite() {
			xMin = yMin = FLOAT_MAX;
			xMax = yMax = - FLOAT_MAX;
		}

		void combine(const Vector& pos)
		{
			if (pos.x < xMin) xMin = pos.x;
			if (pos.x > xMax) xMax = pos.x;
			if (pos.y < yMin) yMin = pos.y;
			if (pos.y > yMax) yMax = pos.y;
		}
		void combine(const AABB& aabb)
		{
			if (aabb.xMin < xMin) xMin = aabb.xMin;
			if (aabb.xMax > xMax) xMax = aabb.xMax;
			if (aabb.yMin < yMin) yMin = aabb.yMin;
			if (aabb.yMax > yMax) yMax = aabb.yMax;
		}
	};
}

#endif // _D2D_AABB_H_