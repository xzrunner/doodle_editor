#include "CurveShape.h"

#include "Render/PrimitiveDraw.h"
#include "Tools/Settings.h"

using namespace wxgui;

#define SIMPLIFY

const float CurveShape::SAMPLING_WIDTH = 10.0f;

CurveShape::CurveShape(const CurveShape& curve)
	: ChainShape(curve)
{
	m_midPoints = curve.m_midPoints;
}

CurveShape::CurveShape(const std::vector<f2Vec2>& vertices)
	: ChainShape(vertices, false)
{
	setMidPoints();
}

CurveShape::~CurveShape()
{
	
}

CurveShape* CurveShape::clone()
{
	return new CurveShape(*this);	
}

void CurveShape::draw(const f2Colorf& color/* = f2Colorf(0, 0, 0)*/) const
{
	if (m_vertices.empty()) return;

	PrimitiveDraw::resetColorAndTexture();

	PrimitiveDraw::drawPolyline(m_midPoints, color, m_isLoop);
	if (Settings::ctlPosSize != 0)
		PrimitiveDraw::drawCircles(m_vertices, Settings::ctlPosSize, f2Colorf(0.4f, 0.8f, 0.4f));
	if (Settings::ctlPosSize != 0)
		PrimitiveDraw::drawCircles(m_midPoints, Settings::ctlPosSize * 0.5f, f2Colorf(0.8f, 0.8f, 0.4f));
}

void CurveShape::insertVertices(size_t index, const f2Vec2& pos)
{
	ChainShape::insertVertices(index, pos);
	setMidPoints();
}

void CurveShape::removeVertices(const f2Vec2& pos)
{
	ChainShape::removeVertices(pos);
	setMidPoints();
}

void CurveShape::changeVertices(const f2Vec2& from, const f2Vec2& to)
{
	ChainShape::changeVertices(from, to);
	setMidPoints();
}

void CurveShape::refresh()
{
//	createBody();
}

void CurveShape::setMidPoints()
{
	m_midPoints.clear();

	if (m_vertices.size() <= 1) return;

	std::vector<f2Vec2> smooth;
	CosineSmooth::implement(m_vertices, SAMPLING_WIDTH, smooth);

#ifdef SIMPLIFY
	DouglasPeucker::implement(smooth, 0.75f, m_midPoints);
#endif
}