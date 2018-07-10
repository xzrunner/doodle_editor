#include "AABB.h"
#include "Tools/f2Math.h"

using namespace F2D;

AABB::AABB()
{
}

AABB::AABB(const AABB& aabb)
{
	m_aabb = aabb.m_aabb;	
}

AABB* AABB::clone()
{
	return new AABB(*this);
}

void AABB::loadFromTextFile(std::ifstream& fin)
{
	fin >> m_aabb.xMin >> m_aabb.xMax >> m_aabb.yMin >> m_aabb.yMax;
}

void AABB::storeToTextFile(std::ofstream& fout) const
{
	fout << m_aabb.xMin << " " << m_aabb.xMax << " "
		<< m_aabb.yMin << " " << m_aabb.yMax << '\n';
}

bool AABB::isContain(const f2Vec2& pos) const
{
	return f2Math::isPointInAABB(pos, m_aabb);
}

bool AABB::isIntersect(const f2AABB& aabb) const
{
	return f2Math::isAABBIntersectAABB(m_aabb, aabb);
}

float AABB::area() const
{
	return m_aabb.xLength() * m_aabb.yLength();
}

float AABB::width() const
{
	return m_aabb.xLength();
}

float AABB::height() const
{
	return m_aabb.yLength();
}

f2Vec2 AABB::center() const
{
	return f2Vec2(m_aabb.xCenter(), m_aabb.yCenter());
}

void AABB::getBoundPos(std::vector<f2Vec2>& bound) const
{
	bound.clear();
	bound.push_back(f2Vec2(m_aabb.xMin, m_aabb.yMin));
	bound.push_back(f2Vec2(m_aabb.xMax, m_aabb.yMin));
	bound.push_back(f2Vec2(m_aabb.xMax, m_aabb.yMax));
	bound.push_back(f2Vec2(m_aabb.xMin, m_aabb.yMax));
}