#include "ToolbarPanel.h"
#include "TrackChainCMPT.h"
#include "TrackSurfaceCMPT.h"
#include "TileEditCMPT.h"
#include "StagePanel.h"

using namespace deditor::hill_climb;

ToolbarPanel::ToolbarPanel(wxWindow* parent, StagePanel* editPanel,
						   wxgui::LibraryPanel* libraryPanel,
						   wxgui::PropertySettingPanel* propertyPanel)
	: wxgui::ToolbarPanel(parent, editPanel)
{
	addChild(new TrackChainCMPT(this, wxT("道路编辑"), editPanel));
	addChild(new TrackSurfaceCMPT(this, wxT("路面纹理"), editPanel));
	addChild(new TileEditCMPT(this, wxT("元件编辑"), editPanel, libraryPanel, propertyPanel));

	SetSizer(initLayout());	
}

wxSizer* ToolbarPanel::initLayout()
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(initChildrenLayout());
	return sizer;
}