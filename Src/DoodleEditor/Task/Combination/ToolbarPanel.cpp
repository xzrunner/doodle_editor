#include "ToolbarPanel.h"
#include "StagePanel.h"
#include "ArrangeSpriteCMPT.h"

#include "Frame/defs.h"

using namespace deditor::combination;

ToolbarPanel::ToolbarPanel(wxWindow* parent, StagePanel* editPanel,
						   wxgui::LibraryPanel* libraryPanel,
						   wxgui::PropertySettingPanel* propertyPanel)
	: wxgui::ToolbarPanel(parent, editPanel)
{
	addChild(new wxgui::PasteSymbolRandomCMPT(this, wxT("粘贴元件"), editPanel, editPanel, libraryPanel));
	addChild(new ArrangeSpriteCMPT(this, wxT("调整元件"), editPanel, propertyPanel));

	SetSizer(initLayout());	
}

wxSizer* ToolbarPanel::initLayout()
{
	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	topSizer->Add(initChildrenLayout());
	return topSizer;
}