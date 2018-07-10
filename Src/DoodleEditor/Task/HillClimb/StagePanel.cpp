#include "StagePanel.h"
#include "StageCanvas.h"

using namespace deditor::hill_climb;

StagePanel::StagePanel(wxWindow* parent, wxgui::LibraryPanel* libraryPanel)
	: EditPanel(parent)
	, ShapesPanelImpl(this)
	, SpritesPanelImpl(this, libraryPanel)
{
	m_canvas = new StageCanvas(this);
}

void StagePanel::clear()
{
	wxgui::EditPanel::clear();
	wxgui::ShapesPanelImpl::clear();
	wxgui::SpritesPanelImpl::clear();
}