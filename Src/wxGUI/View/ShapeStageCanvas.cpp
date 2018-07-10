#include "ShapeStageCanvas.h"

#include "Dataset/ChainShape.h"
#include "Dataset/CurveShape.h"
#include "Dataset/PolygonShape.h"
#include "View/EditPanel.h"
#include "View/MultiShapesImpl.h"
#include "Render/DrawShapesVisitor.h"

using namespace wxgui;

ShapeStageCanvas::ShapeStageCanvas(EditPanel* editPanel, MultiShapesImpl* shapesImpl, 
								   const f2Colorf& color/* = f2Colorf(0.0f, 0.0f, 0.0f)*/)
	: GLCanvas(editPanel)
	, m_color(color)
	, m_shapesImpl(shapesImpl)
{
}

void ShapeStageCanvas::onDraw()
{
	m_shapesImpl->traverseShapes(DrawShapesVisitor(m_color), e_visible);
	m_editPanel->drawEditTemp();
}