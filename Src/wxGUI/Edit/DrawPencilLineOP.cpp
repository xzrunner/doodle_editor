#include "DrawPencilLineOP.h"

#include "Component/DrawPencilLineCMPT.h"
#include "View/MultiShapesImpl.h"
#include "Dataset/ChainShape.h"

using namespace wxgui;

DrawPencilLineOP::DrawPencilLineOP(EditPanel* editPanel, MultiShapesImpl* shapesImpl,
								   DrawPencilLineCMPT* cmpt)
	: DrawCurveOP(editPanel)
	, m_shapesImpl(shapesImpl)
	, m_cmpt(cmpt)
{
}

bool DrawPencilLineOP::onMouseLeftUp(int x, int y)
{
	if (DrawCurveOP::onMouseLeftUp(x, y)) return true;

	if (!m_curve.empty())
	{
		std::vector<f2Vec2> simplified;
		DouglasPeucker::implement(m_curve, m_cmpt->getSimplifyThreshold(), simplified);
		m_shapesImpl->insertShape(new ChainShape(simplified, false));
		clear();
	}

	return false;
}