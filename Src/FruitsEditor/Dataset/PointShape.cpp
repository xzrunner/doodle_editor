#include "PointShape.h"

using namespace FEDITOR;

PointShape::PointShape()
	: Shape(e_point)
{
	m_pos.x = m_pos.y = 0;
}

PointShape::PointShape(const PointShape& point)
	: Shape(e_point)
{	
	m_pos = point.m_pos;
}

PointShape* PointShape::clone()
{
	return new PointShape(*this);
}

void PointShape::loadFromTextFile(std::ifstream& fin)
{
	fin >> m_pos;
}

void PointShape::storeToTextFile(std::ofstream& fout) const
{
	fout << "type " << m_type << '\n';
	fout << m_pos << '\n';
}

bool PointShape::isContain(const f2Vec2& pos, float scale) const
{
	return f2Math::getDistance(pos, m_pos) < QUERY_ACCURACY * scale;
}

void PointShape::getAABB(f2AABB& aabb, const f2Vec2& position, float angle) const
{
	aabb.xMin = aabb.xMax = m_pos.x + position.x;
	aabb.yMin = aabb.yMax = m_pos.y + position.y;
}