#include "StagePanel.h"
#include "StageCanvas.h"

using namespace deditor::texture_edit;

StagePanel::StagePanel(wxWindow* parent, wxgui::LibraryPanel* libraryPanel)
	: EditPanel(parent)
	, wxgui::ShapesPanelImpl(parent)
	, wxgui::SpritesPanelImpl(this, libraryPanel)
	, m_texture(NULL)
{
	m_canvas = new StageCanvas(this);
}

void StagePanel::clear()
{
	wxgui::EditPanel::clear();
	wxgui::ShapesPanelImpl::clear();
	m_texture = NULL;
}

void StagePanel::loadTexture(const wxString& filePath)
{
	m_texture = wxgui::ImageMgr::Instance()->getItem(filePath);
	Refresh();
}