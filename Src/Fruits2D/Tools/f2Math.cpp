#include "f2Math.h"

using namespace F2D;

bool f2Math::isAcuteAngle(const f2Vec2& a, const f2Vec2& center, const f2Vec2& b)
{
	const float squareLenAC = getDistanceSquare(a, center),
		squareLenBC = getDistanceSquare(b, center),
		squareLenAB = getDistanceSquare(a, b);
	return squareLenAC + squareLenBC - squareLenAB > 0;
}

bool f2Math::isSegmentIntersectAABB(float lx1, float ly1, float lx2, float ly2,
									float ax1, float ay1, float ax2, float ay2)
{
	unsigned char typeS, typeE;
	typeS = typeE = 0;
	if ( lx1 < ax1 )      // left:  1000
		typeS |= 0x8; 
	else if ( lx1 > ax2 ) // right: 0100
		typeS |= 0x4; 
	if ( ly1 < ay1 )      // down:  0001
		typeS |= 0x1; 
	else if ( ly1 > ay2 ) // up:    0010
		typeS |= 0x2; 

	if ( lx2 < ax1 )      // left:  1000
		typeE |= 0x8; 
	else if ( lx2 > ax2 ) // right: 0100
		typeE |= 0x4; 
	if ( ly2 < ay1 )      // down:  0001
		typeE |= 0x1; 
	else if ( ly2 > ay2 ) // up:    0010
		typeE |= 0x2; 

	unsigned char comp;
	comp = typeS & typeE;
	if ( comp != 0 )		// must be outside, so must intersect
		return false;
	comp = typeS | typeE;
	if ( comp == 0 )		// must be inside, so must not intersect
		return true;

	// test each edge
	if ( comp & 0x8 )		// 1000, left edge
	{
		float cross_y;
		cross_y = findYOnSeg( lx1, ly1, lx2, ly2, ax1 );
		if ( cross_y >= ay1 && cross_y <= ay2 )
			return true;
	}
	if ( comp & 0x4 )		// 0100, right edge
	{
		float cross_y;
		cross_y = findYOnSeg( lx1, ly1, lx2, ly2, ax2 );
		if ( cross_y >= ay1 && cross_y <= ay2 )
			return true;
	}
	if ( comp & 0x1 )		// 0001, down edge
	{
		float cross_x;
		cross_x = findXOnSeg( lx1, ly1, lx2, ly2, ay1 );
		if ( cross_x >= ax1 && cross_x <= ax2 )
			return true;
	}
	if ( comp & 0x2 )		// 0010, up edge
	{
		float cross_x;
		cross_x = findXOnSeg( lx1, ly1, lx2, ly2, ay2 );
		if ( cross_x >= ax1 && cross_x <= ax2 )
			return true;
	}

	return false;
}

bool f2Math::isPolylineIntersectAABB(const std::vector<f2Vec2>& polyline, bool isLoop, const f2AABB& aabb)
{
	if (polyline.size() < 2) return false;

	for (size_t i = 0, n = polyline.size() - 1; i < n; ++i)
	{
		if (isSegmentIntersectAABB(polyline[i], polyline[i+1], aabb))
			return true;
	}

	if (isLoop && isSegmentIntersectAABB(polyline[polyline.size() - 1], polyline[0], aabb))
		return true;

	return false;
}

bool f2Math::isCircleIntersectAABB(const f2Vec2& center, float radius, const f2AABB& aabb)
{
	if (isPointInAABB(center, aabb))
		return true;

	std::vector<f2Vec2> bounding;
	bounding.push_back(f2Vec2(aabb.xMin, aabb.yMin));
	bounding.push_back(f2Vec2(aabb.xMax, aabb.yMin));
	bounding.push_back(f2Vec2(aabb.xMax, aabb.yMax));
	bounding.push_back(f2Vec2(aabb.xMin, aabb.yMax));
	bounding.push_back(f2Vec2(aabb.xMin, aabb.yMin));

	size_t index;
	return getDisPointToPolyline(center, bounding, &index) < radius;
}

bool f2Math::isPointInTriangle(const f2Vec2& p, const f2Vec2& a, const f2Vec2& b, const f2Vec2& c)
{
	const bool test0 = isPointAtSegmentLeft(p, a, b),
		test1 = isPointAtSegmentLeft(p, b, c),
		test2 = isPointAtSegmentLeft(p, c, a);
	return test0 == test1 && test1 == test2;
}

bool f2Math::isPointInArea(const f2Vec2& pos, const std::vector<f2Vec2>& area)
{
	bool oddNodes = false;
	for (size_t i = 0, n = area.size(), j = n - 1; i < n; ++i)
	{
		if ((area[i].y < pos.y && area[j].y >= pos.y ||
			area[j].y < pos.y && area[i].y >= pos.y) &&
			(area[i].x <= pos.x || area[j].x <= pos.x))
		{
			oddNodes ^= (area[i].x + (pos.y - area[i].y) / (area[j].y - area[i].y) * (area[j].x - area[i].x) < pos.x);
		}
		j = i;
	}
	return oddNodes;
}

bool f2Math::isPointInConvexHull(const f2Vec2& pos, const std::vector<f2Vec2>& hull)
{
	if (hull.size() < 3) return false;

	size_t count = 0;
	for (size_t i = 0, n = hull.size(); i < n; ++i)
	{
		const f2Vec2 s = hull[i], 
			e = i == hull.size() - 1 ? hull[0] : hull[i + 1];
		if (isPointAtSegmentLeft(pos, s, e)) ++count;
	}
	return count == hull.size() || count == 0;
}

int f2Math::checkPosInTriangle(const f2Vec2& p, const f2Vec2& t0, const f2Vec2& t1, const f2Vec2& t2)
{
	if (isTheSamePos(p, t0) || isTheSamePos(p, t1) || isTheSamePos(p, t2))
		return 3;
	if (testPointOnSection(t0, t1, p) == 0)
		return 0;
	if (testPointOnSection(t1, t2, p) == 0)
		return 1;
	if (testPointOnSection(t2, t0, p) == 0)
		return 2;

	if (isPointAtSegmentLeft(p, t0, t1) != isPointAtSegmentLeft(p, t0, t2)
		&& isPointAtSegmentLeft(p, t1, t2) != isPointAtSegmentLeft(p, t1, t0)
		&& isPointAtSegmentLeft(p, t2, t1) != isPointAtSegmentLeft(p, t2, t0))
		return 4;
	else 
		return -1;
}

float f2Math::getDisPointToStraightLine(const f2Vec2& p, const f2Vec2& s, const f2Vec2& e)
{
	float divider = getDistance(s, e);
	if (fabs(divider) < EPSILON) return getDistance(p, s);
	else return fabs((s.x - p.x) * (e.y - p.y) - (s.y - p.y) * (e.x - p.x)) / divider;
}

float f2Math::getDisPointToSegment(const f2Vec2& p, const f2Vec2& s, const f2Vec2& e)
{
	if (!isAcuteAngle(p, s, e))
		return getDistance(p, s);
	else if (!isAcuteAngle(p, e, s))
		return getDistance(p, e);
	else
		return fabs((s.x - p.x) * (e.y - p.y) - (s.y - p.y) * (e.x - p.x)) / getDistance(s, e);
}

float f2Math::getDisPointToPolyline(const f2Vec2& p, const std::vector<f2Vec2>& polyline, size_t* iPos)
{
	if (polyline.size() < 2) return FLOAT_MAX;

	float nearest = FLOAT_MAX;
	size_t iNearest = -1;
	for (size_t i = 0, n = polyline.size() - 1; i < n; ++i)
	{
		const float dis = getDisPointToSegment(p, polyline[i], polyline[i + 1]);
		if (dis < nearest) 
		{
			nearest = dis;
			iNearest = i;
		}
	}
	if (iPos) *iPos = iNearest;
	return nearest;
}

float f2Math::getDisPointToMultiLines(const f2Vec2& p, const std::vector<std::vector<f2Vec2> >& multiLines, size_t* iLine, size_t* iPos)
{
	float nearest = FLOAT_MAX;
	size_t iNearest0 = -1, iNearest1 = -1;
	for (size_t i = 0, n = multiLines.size(); i < n; ++i)
	{
		size_t index;
		const float dis = getDisPointToPolyline(p, multiLines[i], &index);
		if (dis < nearest)
		{
			nearest = dis;
			iNearest0 = i;
			iNearest1 = index;
		}
	}
	if (iLine && iPos)
	{
		*iLine = iNearest0;
		*iPos = iNearest1;
	}
	return nearest;
}

float f2Math::getDisPointToMultiPos(const f2Vec2& p, const std::vector<f2Vec2>& pos, size_t* index)
{
	float nearest = FLOAT_MAX;
	size_t iNearest = -1;
	for (size_t i = 0, n = pos.size(); i < n; ++i)
	{
		const float dis = f2Math::getDistance(p, pos[i]);
		if (dis < nearest)
		{
			nearest = dis;
			iNearest = i;
		}
	}
	if (index) *index = iNearest;
	return nearest;
}

float f2Math::getDisPointToMultiPos(const f2Vec2& p, const std::vector<std::vector<f2Vec2> >& pos, size_t* index0, size_t* index1)
{
	float nearest = FLOAT_MAX;
	size_t iNearest0 = -1, iNearest1 = -1;
	for (size_t i = 0, n = pos.size(); i < n; ++i)
	{
		size_t index;
		const float dis = getDisPointToMultiPos(p, pos[i], &index);
		if (dis < nearest)
		{
			nearest = dis;
			iNearest0 = i;
			iNearest1 = index;
		}
	}
	if (index0 && index1)
	{
		*index0 = iNearest0;
		*index1 = iNearest1;
	}
	return nearest;
}

float f2Math::getAngle(const f2Vec2& center, const f2Vec2& pa, const f2Vec2& pb)
{
	const float a = getDistance(center, pa),
		b = getDistance(center, pb),
		c = getDistance(pa, pb);

	float cosVal = (a * a + b * b - c * c) / (2 * a * b);
	cosVal = std::max(std::min(cosVal, 1.0f), -1.0f);

	return acos(cosVal);
}

float f2Math::getAngleInDirection(const f2Vec2& center, const f2Vec2& start, const f2Vec2& end)
{
	float angle = f2Math::getAngle(center, start, end);
	const float cross = f2Cross(start - center, end - start);
	if (cross < 0) angle = -angle;
	return angle;
}

float f2Math::getLineAngle(const f2Vec2& s, const f2Vec2& e)
{
	const f2Vec2 other(s.x + 1.0f, s.y);
	const float ang = getAngle(s, e, other);
	if (f2Cross(other - s, e - s) > 0) return ang;
	else return -ang;
}

int f2Math::testPointOnSection(const f2Vec2& startPos, const f2Vec2& endPos, const f2Vec2& thdPos, float tolerance/* = EPSILON*/)
{
	assert(tolerance > 0.0);
	f2AABB aabb;
	aabb.xMin = thdPos.x - tolerance / 2.0f;
	aabb.xMax = thdPos.x + tolerance / 2.0f;
	aabb.yMin = thdPos.y - tolerance / 2.0f;
	aabb.yMax = thdPos.y + tolerance / 2.0f;

	if (!isSegmentIntersectAABB(startPos, endPos, aabb)) return -1;

	int resultA = 0;
	int resultB = 0;
	if (isPointInAABB(startPos, aabb)) resultA = 1;
	if (isPointInAABB(endPos, aabb)) resultB = 2;

	return resultA + resultB;
}

int f2Math::getCircumcenter(const f2Vec2& pos1, const f2Vec2& pos2, const f2Vec2& pos3, f2Vec2* center, float tolerance/* = EPSILON*/)
{
	if (testPointOnSection(pos1, pos2, pos3, tolerance) != -1)
		return -1;

	float x1, x2, x3, y1, y2, y3;
	float a, b, c, d, e, f;
	x1 = pos1.x; y1 = pos1.y;
	x2 = pos2.x; y2 = pos2.y;
	x3 = pos3.x; y3 = pos3.y;

	a = 2 * (x2 - x1);
	b = 2 * (y2 - y1);
	c = x2 * x2 + y2 * y2 - x1 * x1 - y1 * y1;
	d = 2 * (x3 - x2);
	e = 2 * (y3 - y2);
	f = x3 * x3 + y3 * y3 - x2 * x2 - y2 * y2;

	center->x = (b * f - e * c) / (b * d - e * a);
	center->y = (d * c - a * f) / (b * d - e * a);

	return 0;
}

int f2Math::getFootOfPerpendicular(const f2Vec2& s, const f2Vec2& e, const f2Vec2& out, f2Vec2* foot)
{
	const float dx = e.x - s.x, dy = e.y - s.y;
	const float dxSquare = dx * dx, dySquare = dy * dy;

	if (dxSquare + dySquare < EPSILON)
	{
		*foot = s;
		return -1;
	}

	foot->x = (dxSquare * out.x + dySquare * s.x + dx * dy * (out.y - s.y)) / (dxSquare + dySquare);
	if (s.x == e.x)
	{
		foot->y = out.y;
	}
	else
	{
		foot->y = findYOnSeg(s, e, foot->x);
	}

	if (isBetween(s.x, e.x, foot->x) && isBetween(s.y, e.y, foot->y))
		return 0;
	else
		return -1;
}

void f2Math::getNearestPosOnLineToPoint(const f2Vec2& p, const std::vector<f2Vec2>& l, f2Vec2* nearest, size_t* index)
{
	size_t iNearestPos = 0;
	float nearestDis = getDistance(p, l.at(iNearestPos));
	for (size_t i = 1; i < l.size(); ++i)
	{
		float dis = getDistance(p, l.at(i));
		if (dis < nearestDis)
		{
			nearestDis = dis;
			iNearestPos = i;
		}
	}
	*nearest = l.at(iNearestPos);
	*index = iNearestPos;

	if (iNearestPos != l.size() - 1)
	{
		f2Vec2 foot;
		if (getFootOfPerpendicular(l.at(iNearestPos), l.at(iNearestPos + 1), p, &foot) == 0)
		{
			float dis = getDistance(foot, p);
			if (dis < nearestDis)
			{
				nearestDis = dis;
				*nearest = foot;
				*index = iNearestPos;
			}
		}
	}

	if (iNearestPos != 0)
	{
		f2Vec2 foot;
		if (getFootOfPerpendicular(l.at(iNearestPos), l.at(iNearestPos - 1), p, &foot) == 0)
		{
			float dis = getDistance(foot, p);
			if (dis < nearestDis)
			{
				*nearest = foot;
				*index = iNearestPos - 1;
			}
		}
	}
}

f2Vec2 f2Math::rotateVector(const f2Vec2& v, float rad)
{
	f2Vec2 ret;
	ret.x = v.x * cos(rad) - v.y * sin(rad);
	ret.y = v.x * sin(rad) + v.y * cos(rad);
	return ret;
}

f2Vec2 f2Math::rotateVectorRightAngle(const f2Vec2& v, bool isTurnLeft)
{
	f2Vec2 ret = v;
	if (isTurnLeft)
	{
		ret.x = -v.y;
		ret.y = v.x;
	}
	else
	{
		ret.x = v.y;
		ret.y = -v.x;
	}
	return ret;
}

f2Vec2 f2Math::transCoordsLocalToWorld(const f2Vec2& origin, const f2Vec2& xDir, const f2Vec2& local)
{
	f2Vec2 nx(xDir);
	nx.normalize();
	f2Vec2 ny = rotateVectorRightAngle(nx, true);
	return origin + (nx * local.x + ny * local.y);
}

f2Vec2 f2Math::transCoordsWorldToLocal(const f2Vec2& origin, const f2Vec2& xDir, const f2Vec2& world)
{
	f2Vec2 offset = world - origin;
	f2Vec2 local;
	float dis = xDir.length();
	local.x = f2Dot(offset, xDir) / dis;
	f2Vec2 perp = offset - xDir * (local.x / dis);
	if (f2Cross(xDir, perp) > 0)
		local.y = perp.length();
	else
		local.y = -perp.length();
	return local;
}

void f2Math::getMBR(const std::vector<f2Vec2>& pos, f2AABB* mbr)
{
	if (pos.empty()) return;

	mbr->xMin = mbr->xMax = pos[0].x;
	mbr->yMin = mbr->yMax = pos[0].y;
	for (size_t i = 1, n = pos.size(); i < n; ++i)
	{
		if (pos[i].x < mbr->xMin) mbr->xMin = pos[i].x;
		if (pos[i].x > mbr->xMax) mbr->xMax = pos[i].x;
		if (pos[i].y < mbr->yMin) mbr->yMin = pos[i].y;
		if (pos[i].y > mbr->yMax) mbr->yMax = pos[i].y;
	}
}

