#include "ToolbarPanel.h"
#include "StagePanel.h"

using namespace deditor::line_edit;

ToolbarPanel::ToolbarPanel(wxWindow* parent, StagePanel* editPanel)
	: wxgui::ToolbarPanel(parent, editPanel)
{
	addChild(new wxgui::DrawLineCMPT(this, wxT("»­Ïß"), editPanel, editPanel));

	SetSizer(initLayout());	
}

wxSizer* ToolbarPanel::initLayout()
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(initChildrenLayout());
	return sizer;
}
