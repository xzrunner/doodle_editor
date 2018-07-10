#include "DrawCosineCurveOP.h"

#include "View/MultiShapesImpl.h"
#include "Dataset/CurveShape.h"

using namespace wxgui;

DrawCosineCurveOP::DrawCosineCurveOP(EditPanel* editPanel, MultiShapesImpl* shapesImpl)
	: DrawPolylineOP(editPanel, false)
	, m_shapesImpl(shapesImpl)
{
}

bool DrawCosineCurveOP::onMouseLeftDClick(int x, int y)
{
	if (DrawPolylineOP::onMouseLeftDClick(x, y)) return true;

	CurveShape* curve = new CurveShape(m_polyline);
	curve->setMidPoints();

	m_shapesImpl->insertShape(curve);
	m_polyline.clear();
	m_currPos.setInvalid();

	return false;
}