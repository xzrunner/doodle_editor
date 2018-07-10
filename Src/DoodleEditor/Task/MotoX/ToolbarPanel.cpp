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
	addChild(new TrackChainCMPT(this, wxT("��·�༭"), editPanel));
	addChild(m_tileCMPT = new TileEditCMPT(this, wxT("Ԫ���༭"), libraryPanel, propertyPanel, editPanel));
	addChild(new ObstacleEditCMPT(this, wxT("�ϰ��༭"), editPanel, libraryPanel, propertyPanel));
	addChild(new MotorbikeCMPT(this, wxT("Ħ�в���"), editPanel));
	addChild(new PackageCMPT(this, wxT("���ݷ���"), editPanel));

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