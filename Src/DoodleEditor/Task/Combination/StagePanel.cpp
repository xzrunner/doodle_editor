#include "StagePanel.h"
#include "StageCanvas.h"

using namespace deditor::combination;

StagePanel::StagePanel(wxWindow* parent, wxgui::PropertySettingPanel* propertyPanel,
					   wxgui::LibraryPanel* libraryPanel)
	: wxgui::EditPanel(parent)
	, wxgui::SpritesPanelImpl(this, libraryPanel)
	, wxgui::ShapesPanelImpl(this)
{
	m_editOP = new wxgui::ArrangeSpriteOP<wxgui::SelectSpritesOP>(this, this, propertyPanel);
	m_canvas = new StageCanvas(this);
}

StagePanel::~StagePanel()
{
	clear();
}

void StagePanel::clear()
{
	wxgui::EditPanel::clear();
	wxgui::SpritesPanelImpl::clear();
	wxgui::ShapesPanelImpl::clear();
}
