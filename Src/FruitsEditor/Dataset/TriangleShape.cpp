#include "TriangleShape.h"

using namespace FEDITOR;

TriangleShape::TriangleShape()
	: Shape(e_triangle)
{
}

TriangleShape::TriangleShape(const TriangleShape& triangle)
	: Shape(e_triangle)
{
	setPos(triangle.m_pos);
}

TriangleShape* TriangleShape::clone()
{
	return new TriangleShape(*this);
}

void TriangleShape::loadFromTextFile(std::ifstream& fin)
{
	for (size_t i = 0; i < 3; ++i)
		fin >> m_pos[i];
}

void TriangleShape::storeToTextFile(std::ofstream& fout) const
{
	for (size_t i = 0; i < 3; ++i)
		fout << m_pos[i] << " ";
	fout << '\n';
}

bool TriangleShape::isContain(const f2Vec2& pos, float scale) const
{
	return f2Math::isPointInTriangle(pos, m_pos[0], m_pos[1], m_pos[2]);
}

void TriangleShape::getAABB(f2AABB& aabb, const f2Vec2& position, float angle) const
{
	aabb.makeInfinite();
	for (size_t i = 0; i < 3; ++i)
	{
		const f2Vec2& src = m_pos[i];
		f2Vec2 transform = f2Math::rotateVector(src, angle) + position;
		aabb.combine(transform);
	}
}