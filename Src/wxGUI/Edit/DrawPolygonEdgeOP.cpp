#include "DrawPolygonEdgeOP.h"

#include "View/MultiShapesImpl.h"
#include "Dataset/PolygonShape.h"

using namespace wxgui;

DrawPolygonEdgeOP::DrawPolygonEdgeOP(EditPanel* editPanel, MultiShapesImpl* shapesImpl)
	: DrawPolylineOP(editPanel, false)
	, m_shapesImpl(shapesImpl)
{
}

bool DrawPolygonEdgeOP::onMouseLeftDClick(int x, int y)
{
	if (DrawPolylineOP::onMouseLeftDClick(x, y)) return true;

	m_shapesImpl->insertShape(new PolygonShape(m_polyline));
	m_polyline.clear();
	m_currPos.setInvalid();

	return false;
}