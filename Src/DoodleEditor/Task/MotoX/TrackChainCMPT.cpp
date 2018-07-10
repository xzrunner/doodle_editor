#include "TrackChainCMPT.h"
#include "TrackChainIOCMPT.h"
#include "TrackChainEditCMPT.h"
#include "StagePanel.h"

using namespace deditor::motox;

TrackChainCMPT::TrackChainCMPT(wxWindow* parent, const wxString& name,
							   StagePanel* editPanel)
	: AbstractEditCMPT(parent, name, editPanel)
{
	addChild(new TrackChainIOCMPT(this, wxT("�������"), editPanel));

//	addChild(new wxgui::DrawLineCMPT(this, wxT("����"), editPanel, editPanel));
	addChild(new wxgui::DrawPolylineCMPT(this, wxT("����"), editPanel, editPanel, wxgui::DrawPolylineCMPT::e_CosineCurve));

	addChild(new TrackChainEditCMPT(this, wxT("�༭"), editPanel));
}

wxSizer* TrackChainCMPT::initLayout()
{
	return initChildrenLayout();
}