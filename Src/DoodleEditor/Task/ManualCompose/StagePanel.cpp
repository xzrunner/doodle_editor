#include "StagePanel.h"
#include "StageCanvas.h"

using namespace deditor::manual_compose;

StagePanel::StagePanel(wxWindow* parent, wxgui::PropertySettingPanel* propertyPanel,
					   wxgui::LibraryPanel* libraryPanel)
	: EditPanel(parent)
	, wxgui::SpritesPanelImpl(this, libraryPanel)
{
	m_editOP = new wxgui::ArrangeSpriteOP<wxgui::SelectSpritesOP>(this, this, propertyPanel);
	m_canvas = new StageCanvas(this);

	m_background = NULL;
}

StagePanel::~StagePanel()
{
	delete m_background;
}

void StagePanel::clear()
{
	EditPanel::clear();
	SpritesPanelImpl::clear();
	delete m_background, m_background = NULL;
}

wxgui::ISprite* StagePanel::getBackground() 
{ 
	return m_background;
}

void StagePanel::setBackground(const wxString& filePath)
{
	if (m_background) 
		delete m_background;
	wxgui::ISymbol* symbol = wxgui::SymbolMgr::Instance()->getSymbol(filePath);
	m_background = wxgui::SpriteFactory::create(symbol);
	Refresh();
}