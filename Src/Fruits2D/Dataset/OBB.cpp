#include "OBB.h"
#include "Tools/f2Math.h"

using namespace F2D;

OBB::OBB()
{
	m_angle = 0.0f;
}

OBB::OBB(const OBB& obb)
{
	m_aabb = obb.m_aabb;
	m_angle = obb.m_angle;
}

OBB* OBB::clone()
{
	return new OBB(*this);
}

void OBB::loadFromTextFile(std::ifstream& fin)
{
	fin >> m_aabb.xMin >> m_aabb.xMax >> m_aabb.yMin >> m_aabb.yMax 
		>> m_angle;
}

void OBB::storeToTextFile(std::ofstream& fout) const
{
	fout << m_aabb.xMin << " " << m_aabb.xMax << " "
		<< m_aabb.yMin << " " << m_aabb.yMax << '\n'
		<< m_angle << '\n';
}

void OBB::translate(const f2Vec2& offset)
{
	m_aabb.translate(offset);
}

void OBB::rotate(float delta)
{
	m_angle += delta;
}

bool OBB::isContain(const f2Vec2& pos) const
{
	const f2Vec2 center(m_aabb.xCenter(), m_aabb.yCenter());
	const f2Vec2 trans = f2Math::rotateVector(pos - center, -m_angle) + center;
	return f2Math::isPointInAABB(trans, m_aabb);
}

bool OBB::isIntersect(const f2AABB& aabb) const
{
	// 0 3
	// 1 2
	std::vector<f2Vec2> bound;
	const f2Vec2 center(m_aabb.xCenter(), m_aabb.yCenter());
	f2Vec2 trans;
	trans = f2Math::rotateVector(f2Vec2(m_aabb.xMin, m_aabb.yMax) - center, m_angle) + center;
	bound.push_back(trans);
	if (f2Math::isPointInAABB(trans, aabb)) return true;
	trans = f2Math::rotateVector(f2Vec2(m_aabb.xMin, m_aabb.yMin) - center, m_angle) + center;
	bound.push_back(trans);
	if (f2Math::isPointInAABB(trans, aabb)) return true;
	trans = f2Math::rotateVector(f2Vec2(m_aabb.xMax, m_aabb.yMin) - center,		m_angle) + center;
	bound.push_back(trans);
	if (f2Math::isPointInAABB(trans, aabb)) return true;
	trans = f2Math::rotateVector(f2Vec2(m_aabb.xMax, m_aabb.yMax) - center, m_angle) + center;
	bound.push_back(trans);
	if (f2Math::isPointInAABB(trans, aabb)) return true;

	if (f2Math::isPointInConvexHull(f2Vec2(aabb.xMin, aabb.yMin), bound)) return true;
	if (f2Math::isPointInConvexHull(f2Vec2(aabb.xMin, aabb.yMax), bound)) return true;
	if (f2Math::isPointInConvexHull(f2Vec2(aabb.xMax, aabb.yMin), bound)) return true;
	if (f2Math::isPointInConvexHull(f2Vec2(aabb.xMax, aabb.yMax), bound)) return true;

	if (f2Math::isSegmentIntersectAABB(bound[0], bound[1], aabb)) return true;
	if (f2Math::isSegmentIntersectAABB(bound[1], bound[2], aabb)) return true;
	if (f2Math::isSegmentIntersectAABB(bound[2], bound[3], aabb)) return true;
	if (f2Math::isSegmentIntersectAABB(bound[3], bound[0], aabb)) return true;

	return false;
}

float OBB::area() const
{
	return m_aabb.xLength() * m_aabb.yLength();
}

float OBB::width() const
{
	return m_aabb.xLength();
}

float OBB::height() const
{
	return m_aabb.yLength();
}

f2Vec2 OBB::center() const
{
	return f2Vec2(m_aabb.xCenter(), m_aabb.yCenter());
}

void OBB::getBoundPos(std::vector<f2Vec2>& bound) const
{
	bound.clear();

	const f2Vec2 center(m_aabb.xCenter(), m_aabb.yCenter());
	bound.push_back(f2Math::rotateVector(f2Vec2(m_aabb.xMin, m_aabb.yMin) - center, m_angle) + center);
	bound.push_back(f2Math::rotateVector(f2Vec2(m_aabb.xMax, m_aabb.yMin) - center, m_angle) + center);
	bound.push_back(f2Math::rotateVector(f2Vec2(m_aabb.xMax, m_aabb.yMax) - center, m_angle) + center);
	bound.push_back(f2Math::rotateVector(f2Vec2(m_aabb.xMin, m_aabb.yMax) - center, m_angle) + center);
}

f2AABB OBB::transToAABB() const
{
	f2Vec2 leftLow(m_aabb.xMin, m_aabb.yMin),
		rightTop(m_aabb.xMax, m_aabb.yMax);
	f2Vec2 transLeftLow = f2Math::rotateVector(leftLow, m_angle),
		transRightTop = f2Math::rotateVector(rightTop, m_angle);

	f2AABB aabb;
	aabb.combine(transLeftLow);
	aabb.combine(transRightTop);
	return aabb;
}