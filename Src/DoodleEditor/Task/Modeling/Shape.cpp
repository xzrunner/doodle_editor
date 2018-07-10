#include "Shape.h"

using namespace deditor::modeling;

//////////////////////////////////////////////////////////////////////////
// class CircleShape
//////////////////////////////////////////////////////////////////////////

CircleShape::CircleShape() 
	: m_radius(0.0f)
{
	m_type = e_circle;
}

bool CircleShape::isContain(const f2Vec2& pos, const f2Vec2& offset, float delta) const
{
	return f2Math::getDistance(m_center + offset, pos) < m_radius;
}

bool CircleShape::isIntersect(const f2AABB& aabb, const f2Vec2& offset, float delta) const
{
	return f2Math::isCircleIntersectAABB(m_center + offset, m_radius, aabb);
}

void CircleShape::draw(const f2Colorf& cFace, const f2Colorf& cEdge) const
{
	wxgui::PrimitiveDraw::drawCircle(f2Vec2(), m_radius, cFace);
	wxgui::PrimitiveDraw::drawRing(f2Vec2(), m_radius, cEdge, 2, 32);
}

//////////////////////////////////////////////////////////////////////////
// class PolygonShape
//////////////////////////////////////////////////////////////////////////

PolygonShape::PolygonShape()
{
	m_type = e_polygon;
}

bool PolygonShape::isContain(const f2Vec2& pos, const f2Vec2& offset, float delta) const
{
	std::vector<f2Vec2> vertices(m_vertices);
	for (size_t i = 0, n = vertices.size(); i < n ; ++i)
		vertices[i] = f2Math::rotateVector(vertices[i], delta) + offset;
	return f2Math::isPointInArea(pos, vertices);
}

bool PolygonShape::isIntersect(const f2AABB& aabb, const f2Vec2& offset, float delta) const
{
	std::vector<f2Vec2> vertices(m_vertices);
	for (size_t i = 0, n = vertices.size(); i < n ; ++i)
		vertices[i] = f2Math::rotateVector(vertices[i], delta) + offset;
	return f2Math::isPolylineIntersectAABB(vertices, true, aabb);
}

void PolygonShape::draw(const f2Colorf& cFace, const f2Colorf& cEdge) const
{
	wxgui::PrimitiveDraw::drawPolygon(m_vertices, cFace);
	wxgui::PrimitiveDraw::drawPolyline(m_vertices, cEdge, true, 2);
}