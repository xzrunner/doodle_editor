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
	addChild(new wxgui::PasteSymbolCaptureCMPT(this, wxT("ճ��Ԫ��"), editPanel, editPanel, libraryPanel));
	addChild(new wxgui::PasteSpriteCMPT(this, wxT("����ճ��"), editPanel, editPanel, propertyPanel));
	addChild(new SetTexCoordsCMPT(this, wxT("����Ԫ��"), editPanel, propertyPanel));
	addChild(new wxgui::DrawPolylineCMPT(this, wxT("�༭����߽�"), editPanel, editPanel, wxgui::DrawPolylineCMPT::e_PenLine));
	addChild(new SetPolylinePropertyCMPT(this, wxT("������������"), editPanel));

	SetSizer(initLayout());	
}

wxSizer* ToolbarPanel::initLayout()
{
	return initChildrenLayout();
}