#include "ToolbarPanel.h"
#include "StagePanel.h"
#include "TrackChainCMPT.h"
#include "TileEditCMPT.h"
#include "ObstacleEditCMPT.h"
#include "MotorbikeCMPT.h"
#include "PackageCMPT.h"

using namespace deditor::motox;

ToolbarPanel::ToolbarPanel(wxWindow* parent, wxgui::PropertySettingPanel* propertyPanel,
						   StagePanel* editPanel, wxgui::LibraryPanel* libraryPanel)
	: wxgui::ToolbarPanel(parent, editPanel)
{
	addChild(new TrackChainCMPT(this, wxT("道路编辑"), editPanel));
	addChild(m_tileCMPT = new TileEditCMPT(this, wxT("元件编辑"), libraryPanel, propertyPanel, editPanel));
	addChild(new ObstacleEditCMPT(this, wxT("障碍编辑"), editPanel, libraryPanel, propertyPanel));
	addChild(new MotorbikeCMPT(this, wxT("摩托参数"), editPanel));
	addChild(new PackageCMPT(this, wxT("数据发布"), editPanel));

	SetSizer(initLayout());	
}

wxgui::LayersMgrWidget* ToolbarPanel::getLayersMgr()
{
	return m_tileCMPT->getLayersMgr();
}

wxSizer* ToolbarPanel::initLayout()
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(initChildrenLayout());
	return sizer;
}