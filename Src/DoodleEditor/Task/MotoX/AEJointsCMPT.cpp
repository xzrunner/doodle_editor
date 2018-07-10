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
	wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("�ؽ�"));
	wxBoxSizer* sizer = new wxStaticBoxSizer(bounding, wxVERTICAL);

	wxArrayString choices;
	choices.Add(wxT("��"));
	choices.Add(wxT("��"));
	choices.Add(wxT("��"));
	choices.Add(wxT("��"));
	choices.Add(wxT("ϥ"));
	choices.Add(wxT("��"));
	choices.Add(wxT("��"));
	m_jointChoice = new wxComboBox(this, wxID_ANY, wxT("�ؽ�"), wxDefaultPosition, wxDefaultSize, choices);
	m_jointChoice->SetSelection(0);
	sizer->Add(m_jointChoice);

	sizer->AddSpacer(20);

	wxButton* btnCreate = new wxButton(this, wxID_ANY, wxT("����ȫ��"));
	Connect(btnCreate->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
		wxCommandEventHandler(AEJointsCMPT::onCreateAll));
	sizer->Add(btnCreate);

	return sizer;
}

void AEJointsCMPT::onCreateAll(wxCommandEvent& event)
{
	m_editPanel->getJoints().createAllJoints();
}