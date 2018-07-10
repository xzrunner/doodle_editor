#include "ToolbarPanel.h"
#include "StagePanel.h"
#include "SetTexCoordsCMPT.h"
#include "SetPolylinePropertyCMPT.h"

using namespace deditor::skater;

ToolbarPanel::ToolbarPanel(wxWindow* parent, StagePanel* editPanel,
						   wxgui::LibraryPanel* libraryPanel,
						   wxgui::PropertySettingPanel* propertyPanel)
	: wxgui::ToolbarPanel(parent, editPanel)
{
	addChild(new wxgui::PasteSymbolCaptureCMPT(this, wxT("粘贴元件"), editPanel, editPanel, libraryPanel));
	addChild(new wxgui::PasteSpriteCMPT(this, wxT("批量粘贴"), editPanel, editPanel, propertyPanel));
	addChild(new SetTexCoordsCMPT(this, wxT("调整元件"), editPanel, propertyPanel));
	addChild(new wxgui::DrawPolylineCMPT(this, wxT("编辑物理边界"), editPanel, editPanel, wxgui::DrawPolylineCMPT::e_PenLine));
	addChild(new SetPolylinePropertyCMPT(this, wxT("设置物理属性"), editPanel));

	SetSizer(initLayout());	
}

wxSizer* ToolbarPanel::initLayout()
{
	return initChildrenLayout();
}