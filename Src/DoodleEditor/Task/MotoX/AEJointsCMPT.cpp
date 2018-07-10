#include "AEJointsCMPT.h"
#include "AEEditPanel.h"
#include "AEJointsOP.h"

using namespace deditor::motox;

AEJointsCMPT::AEJointsCMPT(wxWindow* parent, const wxString& name, AEEditPanel* editPanel)
	: wxgui::AbstractEditCMPT(parent, name, editPanel)
{
	m_editPanel = editPanel;
	m_editOP = new AEJointsOP(editPanel, this);
}

wxSizer* AEJointsCMPT::initLayout()
{
	wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("关节"));
	wxBoxSizer* sizer = new wxStaticBoxSizer(bounding, wxVERTICAL);

	wxArrayString choices;
	choices.Add(wxT("脖"));
	choices.Add(wxT("肩"));
	choices.Add(wxT("肘"));
	choices.Add(wxT("胯"));
	choices.Add(wxT("膝"));
	choices.Add(wxT("手"));
	choices.Add(wxT("足"));
	m_jointChoice = new wxComboBox(this, wxID_ANY, wxT("关节"), wxDefaultPosition, wxDefaultSize, choices);
	m_jointChoice->SetSelection(0);
	sizer->Add(m_jointChoice);

	sizer->AddSpacer(20);

	wxButton* btnCreate = new wxButton(this, wxID_ANY, wxT("创建全部"));
	Connect(btnCreate->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
		wxCommandEventHandler(AEJointsCMPT::onCreateAll));
	sizer->Add(btnCreate);

	return sizer;
}

void AEJointsCMPT::onCreateAll(wxCommandEvent& event)
{
	m_editPanel->getJoints().createAllJoints();
}