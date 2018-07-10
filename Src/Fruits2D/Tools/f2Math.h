#ifndef _F2D_MATH_H_
#define _F2D_MATH_H_

#include <cmath>
#include <vector>
#include <assert.h>

#include "f2Types.h"

namespace F2D
{
	template <typename T>
	inline T f2Min(T a, T b)
	{
		return a < b ? a : b;
	}

	template <typename T>
	inline T f2Max(T a, T b)
	{
		return a > b ? a : b;
	}

	template <typename T>
	inline T f2Clamp(T a, T low, T high)
	{
		return f2Max(low, f2Min(a, high));
	}

	class f2Math
	{
	public:
		//////////////////////////////////////////////////////////////////////////
		//
		// Test if satisfy some conditions, return type is bool.
		//
		//////////////////////////////////////////////////////////////////////////

		// To check if test at middle of bound0 and bound1
		static bool isBetween(float bound0, float bound1, float test)
		{
			if (bound0 < bound1)
				return test < bound1 + EPSILON && test > bound0 - EPSILON;
			else
				return test < bound0 + EPSILON && test > bound1 - EPSILON;
		}

		// To check if the 2 point overlapped with each other.
		static bool isTheSamePos(const f2Vec2& p0, const f2Vec2& p1, const float tolerance = EPSILON)
		{
			return fabs(p0.x - p1.x) <= tolerance
				&& fabs(p0.y - p1.y) <= tolerance;
		}

		// Attention: It can't handle the point on segment.
		//			  Before use it must make sure the point is not on the segment.
		static bool isPointAtSegmentLeft(const f2Vec2& p, const f2Vec2& s, const f2Vec2& e)
		{
			return (p.y - s.y) * (e.x - s.x) - (p.x - s.x) * (e.y - s.y) > EPSILON;
		}

		// To check if angle a-center-b is acute.
		static bool isAcuteAngle(const f2Vec2& a, const f2Vec2& center, const f2Vec2& b);

		static bool isAABBIntersectAABB(const f2AABB& r0, const f2AABB& r1)
		{
			return !(r0.xMin > r1.xMax || r0.xMax < r1.xMin || r0.yMin > r1.yMax || r0.yMax < r1.yMin);
		}

		// To check if the segment intersect with the f2AABB.
		static bool isSegmentIntersectAABB(float lx1, float ly1, float lx2, float ly2,
			float ax1, float ay1, float ax2, float ay2);
		static bool isSegmentIntersectAABB(const f2Vec2& b, const f2Vec2& e, const f2AABB& aabb)
		{
			return isSegmentIntersectAABB(b.x, b.y, e.x, e.y, aabb.xMin, aabb.yMin, aabb.xMax, aabb.yMax);
		}

		static bool isPolylineIntersectAABB(const std::vector<f2Vec2>& polyline, bool isLoop, const f2AABB& aabb);

		static bool isCircleIntersectAABB(const f2Vec2& center, float radius, const f2AABB& aabb);

		static bool isPointInTriangle(const f2Vec2& p, const f2Vec2& a, const f2Vec2& b, const f2Vec2& c);

		static bool isPointInAABB(const f2Vec2& pos, const f2Vec2& left_low, float w, float h)
		{
			return pos.x > left_low.x && pos.x < left_low.x + w 
				&& pos.y > left_low.y && pos.y < left_low.y + h;
		}

		static bool isPointInAABB(const f2Vec2& pos, const f2AABB& aabb)
		{
			return pos.x > aabb.xMin && pos.x < aabb.xMax
				&& pos.y > aabb.yMin && pos.y < aabb.yMax;
		}

		static bool isPointInArea(const f2Vec2& pos, const std::vector<f2Vec2>& area);

		static bool isPointInConvexHull(const f2Vec2& pos, const std::vector<f2Vec2>& hull);

		// To check if the point in the triangle.
		// return: [0] p is on the edge t0-t1		[1] p is on the edge t1-t2
		//		   [2] p is on the edge t2-t0
		//		   [4] p is in the triangle			[-1] p is outside
		static int checkPosInTriangle(const f2Vec2& p, const f2Vec2& t0, const f2Vec2& t1, const f2Vec2& t2);

		//////////////////////////////////////////////////////////////////////////
		//
		// Compute some geographic value, return type is float.
		//
		//////////////////////////////////////////////////////////////////////////

		// Get the coordinate of a segment.
		static float findXOnSeg(float x1, float y1, float x2, float y2, float y)
		{
			if (y1 == y2) 
				return std::min(x1, x2);
			return (y - y2) * (x1 - x2) / (y1 - y2) + x2;
		}
		static float findYOnSeg(float x1, float y1, float x2, float y2, float x)
		{
			if (x1 == x2) 
				return std::min(y1, y2);
			return (x - x2) * (y1 - y2) / (x1 - x2) + y2;
		}
		static float findXOnSeg(const f2Vec2& b, const f2Vec2& e, float y)
		{
			return findXOnSeg(b.x, b.y, e.x, e.y, y);
		}
		static float findYOnSeg(const f2Vec2& b, const f2Vec2& e, float x)
		{
			return findYOnSeg(b.x, b.y, e.x, e.y, x);
		}

		static float getDistance(const f2Vec2& p0, const f2Vec2& p1)
		{
			const float dx = p0.x - p1.x,
				dy = p0.y - p1.y;
			return sqrt(dx * dx + dy * dy);
		}

		static float getDistanceSquare(const f2Vec2& p0, const f2Vec2& p1)
		{
			const float dx = p0.x - p1.x,
				dy = p0.y - p1.y;
			return dx * dx + dy * dy;
		}

		static float getDisPointToStraightLine(const f2Vec2& p, const f2Vec2& s, const f2Vec2& e);

		static float getDisPointToSegment(const f2Vec2& p, const f2Vec2& s, const f2Vec2& e);

		static float getDisPointToPolyline(const f2Vec2& p, const std::vector<f2Vec2>& polyline, size_t* iPos);

		static float getDisPointToMultiLines(const f2Vec2& p, const std::vector<std::vector<f2Vec2> >& multiLines, size_t* iLine, size_t* iPos);

		static float getDisPointToMultiPos(const f2Vec2& p, const std::vector<f2Vec2>& pos, size_t* index);

		static float getDisPointToMultiPos(const f2Vec2& p, const std::vector<std::vector<f2Vec2> >& pos, size_t* index0, size_t* index1);

		static float getAngle(const f2Vec2& center, const f2Vec2& pa, const f2Vec2& pb);

		static float getAngleInDirection(const f2Vec2& center, const f2Vec2& start, const f2Vec2& end);

		static float getLineAngle(const f2Vec2& s, const f2Vec2& e);

		//////////////////////////////////////////////////////////////////////////
		//
		// Test through input value, output the multiple situations.
		// Return type is int, different value denote different situations.
		//
		//////////////////////////////////////////////////////////////////////////

		// To check if the point on the segment.
		// return: [-1] outside		[0] on the middle		[1] overlap with startPos
		//		    [2] overlap with endPos		[3] the 3 point are overlap each other.
		static int testPointOnSection(const f2Vec2& startPos, const f2Vec2& endPos, const f2Vec2& thdPos, float tolerance = EPSILON);

		// 3 point can decide a circle, get its center.
		// return: [0] success, [-1] not success, 3 points on a segment.
		static int getCircumcenter(const f2Vec2& pos1, const f2Vec2& pos2, const f2Vec2& pos3, f2Vec2* center, float tolerance = EPSILON);

		//////////////////////////////////////////////////////////////////////////
		//
		// Get other value.
		//
		//////////////////////////////////////////////////////////////////////////

		// Get the foot of out at line(s, e).
		// Is return -1 the foot is outside the line(s, e), return 0 the foot on the line(s, e).
		static int getFootOfPerpendicular(const f2Vec2& s, const f2Vec2& e, const f2Vec2& out, f2Vec2* foot);

		// Get the nearest position of Line to Point.
		static void getNearestPosOnLineToPoint(const f2Vec2& p, const std::vector<f2Vec2>& l, f2Vec2* nearest, size_t* index);

		static f2Vec2 rotateVector(const f2Vec2& v, float rad);

		static f2Vec2 rotateVectorRightAngle(const f2Vec2& v, bool isTurnLeft);

		static f2Vec2 transCoordsLocalToWorld(const f2Vec2& origin, const f2Vec2& xDir, const f2Vec2& local);

		static f2Vec2 transCoordsWorldToLocal(const f2Vec2& origin, const f2Vec2& xDir, const f2Vec2& world);

		static void getMBR(const std::vector<f2Vec2>& pos, f2AABB* mbr);

		static f2Vec2 getTriGravityCenter(const f2Vec2& p0, const f2Vec2& p1, const f2Vec2& p2)
		{
			return f2Vec2((p0.x + p1.x + p2.x) / 3, (p0.y + p1.y + p2.y) / 3);
		}

	}; // f2Math
}

#endif // _F2D_MATH_H_