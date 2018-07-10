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
	addChild(new wxgui::PasteSymbolRandomCMPT(this, wxT("ճ��Ԫ��"), editPanel, editPanel, libraryPanel));
	addChild(new ArrangeSpriteCMPT(this, wxT("����Ԫ��"), editPanel, propertyPanel));

	SetSizer(initLayout());	
}

wxSizer* ToolbarPanel::initLayout()
{
	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	topSizer->Add(initChildrenLayout());
	return topSizer;
}