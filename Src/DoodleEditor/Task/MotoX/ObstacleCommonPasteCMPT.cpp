#include "ObstacleCommonPasteCMPT.h"
#include "StagePanel.h"

#include <wx/spinctrl.h>

using namespace deditor::motox;

ObstacleCommonPasteCMPT::ObstacleCommonPasteCMPT(wxWindow* parent, const wxString& name,
												 StagePanel* editPanel, wxgui::LibraryPanel* libraryPanel)
	: wxgui::AbstractEditCMPT(parent, name, editPanel)
	, m_scaleVal(1.0f)
{
	addChild(new wxgui::PasteSymbolPhysicsCMPT(this, wxT("ÎïÀí"), editPanel, editPanel, libraryPanel, editPanel, editPanel->getWorld(), editPanel->getWorldReverse(), &m_scaleVal));
}

wxSizer* ObstacleCommonPasteCMPT::initLayout()
{
	wxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	{
		wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		sizer->Add(new wxStaticText(this, wxID_ANY, wxT("Ëõ·Å: ")));

		wxSpinCtrl* scaleCtrl = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), 
			wxSP_ARROW_KEYS, 10, 100, 100);
		Connect(scaleCtrl->GetId(), wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(ObstacleCommonPasteCMPT::onChangeScale));
		sizer->Add(scaleCtrl);

		sizer->Add(new wxStaticText(this, wxID_ANY, wxT("%")));
		topSizer->Add(sizer);
	}
	topSizer->AddSpacer(10);
	{
		topSizer->Add(initChildrenLayout());
	}
	return topSizer;
}

void ObstacleCommonPasteCMPT::onChangeScale(wxSpinEvent& event)
{
	m_scaleVal = event.GetValue() * 0.01f;
}