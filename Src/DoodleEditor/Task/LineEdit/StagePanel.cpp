#include "StagePanel.h"
#include "StageCanvas.h"

using namespace deditor::line_edit;

StagePanel::StagePanel(wxWindow* parent)
	: EditPanel(parent)
	, ShapesPanelImpl(this)
{
	m_canvas = new StageCanvas(this);
}

void StagePanel::clear()
{
	EditPanel::clear();
	ShapesPanelImpl::clear();
}