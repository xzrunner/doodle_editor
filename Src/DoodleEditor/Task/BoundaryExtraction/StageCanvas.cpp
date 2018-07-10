#include "StageCanvas.h"
#include "StagePanel.h"

using namespace deditor::boundary_extraction;

StageCanvas::StageCanvas(StagePanel* editPanel)
	: wxgui::ShapeStageCanvas(editPanel, editPanel, f2Colorf(1.0f, 0.0f, 0.0f))
{
}

void StageCanvas::onDraw()
{
	static_cast<StagePanel*>(m_editPanel)->onDraw();
	wxgui::ShapeStageCanvas::onDraw();
}