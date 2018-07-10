#include "ToolbarPanel.h"
#include "StagePanel.h"
#include "BodyEditCmpt.h"
#include "FixtureEditCmpt.h"
#include "JointEditCmpt.h"

using namespace deditor::modeling;

ToolbarPanel::ToolbarPanel(wxWindow* parent, StagePanel* editPanel,
						   wxgui::LibraryPanel* libraryPanel,
						   wxgui::PropertySettingPanel* propertyPanel)
	: wxgui::ToolbarPanel(parent, editPanel)
{
	addChild(new BodyEditCmpt(this, wxT("Body"), editPanel, propertyPanel));
	addChild(new FixtureEditCmpt(this, wxT("Fixture"), editPanel, propertyPanel));
	addChild(new JointEditCmpt(this, wxT("Joint"), editPanel, propertyPanel));

	SetSizer(initLayout());	
}

wxSizer* ToolbarPanel::initLayout()
{
	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	topSizer->Add(initChildrenLayout());
	return topSizer;
}