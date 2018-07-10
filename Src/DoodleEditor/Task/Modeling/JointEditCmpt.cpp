#include "JointEditCmpt.h"
#include "StagePanel.h"
#include "SelectJointOP.h"
#include "RevoluteJoint.h"
#include "PrismaticJoint.h"
#include "DistanceJoint.h"
#include "WheelJoint.h"
#include "BodyData.h"

using namespace deditor::modeling;

JointEditCmpt::JointEditCmpt(wxWindow* parent, const wxString& name, 
							 StagePanel* editPanel, wxgui::PropertySettingPanel* propertyPanel)
	: wxgui::AbstractEditCMPT(parent, name, editPanel)
{
	m_editOP = new wxgui::ArrangeSpriteOP<SelectJointOP>(editPanel, editPanel, propertyPanel, this, false);
}

void JointEditCmpt::updateControlValue()
{
	wxgui::SpriteSelection* selection = static_cast<StagePanel*>(m_editPanel)->getSpriteSelection();
	m_btnOK->Enable(selection->size() == 2);
}

wxSizer* JointEditCmpt::initLayout()
{
	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	{
		wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("����"));
		wxBoxSizer* sizer = new wxStaticBoxSizer(bounding, wxVERTICAL);
		{
			wxString choices[4];
			choices[0] = wxT("Revolute");
			choices[1] = wxT("Prismatic");
			choices[2] = wxT("Distance");
			choices[3] = wxT("Wheel");

			m_typeChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 4, choices);
			m_typeChoice->SetSelection(0);
			sizer->Add(m_typeChoice);
		}
		topSizer->Add(sizer);
	}
	topSizer->AddSpacer(10);
	{
		m_btnOK = new wxButton(this, wxID_ANY, wxT("OK"));
		Connect(m_btnOK->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(JointEditCmpt::onCreateJoint));
		m_btnOK->Enable(false);
		topSizer->Add(m_btnOK);
	}
	return topSizer;
}

void JointEditCmpt::onCreateJoint(wxCommandEvent& event)
{
	StagePanel* editPanel = static_cast<StagePanel*>(m_editPanel);

	std::vector<wxgui::ISprite*> sprites;
	wxgui::SpriteSelection* selection = editPanel->getSpriteSelection();
	selection->traverse(FetchAllVisitor<wxgui::ISprite>(sprites));
	assert(sprites.size() == 2);

	BodyData *body0 = static_cast<BodyData*>(sprites[0]->getUserData()),
		*body1 = static_cast<BodyData*>(sprites[1]->getUserData());

	JointData* joint = NULL;
	wxString type = m_typeChoice->GetString(m_typeChoice->GetSelection());
	if (type == wxT("Revolute"))
		editPanel->insertJoint(new RevoluteJoint(body0, body1));
	else if (type == wxT("Prismatic"))
		editPanel->insertJoint(new PrismaticJoint(body0, body1));
	else if (type == wxT("Distance"))
		editPanel->insertJoint(new DistanceJoint(body0, body1));
	else if (type == wxT("Wheel"))
	{
		SelectWheelDialog dlg(this, wxT("ѡ������"), body0->m_name, body1->m_name);
		if (dlg.ShowModal() == wxID_OK)
		{
			if (dlg.getChoice() == 0)
				editPanel->insertJoint(new WheelJoint(body1, body0));
			else
				editPanel->insertJoint(new WheelJoint(body0, body1));
		}
	}

	m_editPanel->Refresh();
}

JointEditCmpt::SelectWheelDialog::
SelectWheelDialog(wxWindow* parent, const wxString& title, const wxString& body0, const wxString& body1)
	: wxDialog(parent, wxID_ANY, title)
{
	initLayout(body0, body1);
}

void JointEditCmpt::SelectWheelDialog::
initLayout(const wxString& body0, const wxString& body1)
{
	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);	
	{
		wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("wheel"));
		wxBoxSizer* sizer = new wxStaticBoxSizer(bounding, wxVERTICAL);
		{
			wxString choices[2];
			choices[0] = body0;
			choices[1] = body1;

			m_wheelChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 2, choices);
			m_wheelChoice->SetSelection(0);
			sizer->Add(m_wheelChoice);
		}
		topSizer->Add(sizer, 0, wxALIGN_CENTER_HORIZONTAL);
	}
	{
		wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
		btnSizer->Add(new wxButton(this, wxID_OK), wxALL, 5);
		btnSizer->Add(new wxButton(this, wxID_CANCEL), wxALL, 5);
		topSizer->Add(btnSizer, 0, wxALL, 5);
	}
	SetSizer(topSizer);
	topSizer->Fit(this);
}