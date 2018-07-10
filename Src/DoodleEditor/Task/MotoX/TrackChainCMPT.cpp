#include "TrackChainCMPT.h"
#include "TrackChainIOCMPT.h"
#include "TrackChainEditCMPT.h"
#include "StagePanel.h"

using namespace deditor::motox;

TrackChainCMPT::TrackChainCMPT(wxWindow* parent, const wxString& name,
							   StagePanel* editPanel)
	: AbstractEditCMPT(parent, name, editPanel)
{
	addChild(new TrackChainIOCMPT(this, wxT("输入输出"), editPanel));

//	addChild(new wxgui::DrawLineCMPT(this, wxT("绘制"), editPanel, editPanel));
	addChild(new wxgui::DrawPolylineCMPT(this, wxT("绘制"), editPanel, editPanel, wxgui::DrawPolylineCMPT::e_CosineCurve));

	addChild(new TrackChainEditCMPT(this, wxT("编辑"), editPanel));
}

wxSizer* TrackChainCMPT::initLayout()
{
	return initChildrenLayout();
}