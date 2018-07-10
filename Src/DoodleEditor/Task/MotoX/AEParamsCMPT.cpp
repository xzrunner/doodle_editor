#include "AEParamsCMPT.h"
#include "AEParamsOP.h"
#include "AEEditPanel.h"
#include "LibraryActorItem.h"

#include <wx/spinctrl.h>

using namespace deditor::motox;

const float AEParamsCMPT::SPEED_SCALE = 10.0f;
const float AEParamsCMPT::ANGLE_SCALE = 100.0f;

AEParamsCMPT::AEParamsCMPT(wxWindow* parent, const wxString& name,
						   AEEditPanel* editPanel)
	: wxgui::AbstractEditCMPT(parent, name, editPanel)
	, m_joints(editPanel->getJoints())
{
	m_editOP = new AEParamsOP(editPanel);
}

void AEParamsCMPT::show(bool show)
{
	static_cast<AEEditPanel*>(m_editPanel)->traverseSprites(SetBodyAliveVisitor(show));
}

wxSizer* AEParamsCMPT::initLayout()
{
	wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxEmptyString);
	wxBoxSizer* sizer = new wxStaticBoxSizer(bounding, wxVERTICAL);

	initChoicePanel(sizer);
	sizer->AddSpacer(10);
	initSettingPanel(sizer);
	sizer->AddSpacer(10);
	initSpeedPanel(sizer);
	sizer->AddSpacer(10);
	initAnglePanel(sizer);
	sizer->AddSpacer(10);
	initTorquePanel(sizer);
	sizer->AddSpacer(10);
	initControlPanel(sizer);

	return sizer;
}

void AEParamsCMPT::initChoicePanel(wxSizer* topSizer)
{
	wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

	sizer->Add(new wxStaticText(this, wxID_ANY, wxT("选择：")));

	wxArrayString choices;
	choices.Add(wxT("脖"));
	choices.Add(wxT("肩"));
	choices.Add(wxT("肘"));
	choices.Add(wxT("胯"));
	choices.Add(wxT("膝"));

	m_jointChoice = new wxComboBox(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, choices);
	m_jointChoice->SetSelection(0);
	Connect(m_jointChoice->GetId(), wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler(AEParamsCMPT::onChoiceChanged));
	sizer->Add(m_jointChoice);

	topSizer->Add(sizer);
}

void AEParamsCMPT::initSettingPanel(wxSizer* topSizer)
{
	wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("设置"));
	wxBoxSizer* settingSizer = new wxStaticBoxSizer(bounding, wxVERTICAL);

	m_checkLimit = new wxCheckBox(this, wxID_ANY, wxT("EnableLimit"));
	Connect(m_checkLimit->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AEParamsCMPT::onSettingChanged));
	settingSizer->Add(m_checkLimit);

	m_checkMotor = new wxCheckBox(this, wxID_ANY, wxT("EnableMotor"));
	Connect(m_checkMotor->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(AEParamsCMPT::onSettingChanged));
	settingSizer->Add(m_checkMotor);

	topSizer->Add(settingSizer);
}

void AEParamsCMPT::initSpeedPanel(wxSizer* topSizer)
{
	wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("速度"));
	wxBoxSizer* speedSizer = new wxStaticBoxSizer(bounding, wxVERTICAL);
	{
		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		sizer->Add(new wxStaticText(this, wxID_ANY, wxT("正向：")));

		m_speedPositive = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), 
			wxSP_ARROW_KEYS, 0 * SPEED_SCALE, 10 * SPEED_SCALE, 2 * SPEED_SCALE);
		Connect(m_speedPositive->GetId(), wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(AEParamsCMPT::onSetParams));
		sizer->Add(m_speedPositive);

		speedSizer->Add(sizer);
	}
	{
		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		sizer->Add(new wxStaticText(this, wxID_ANY, wxT("负向：")));

		m_speedNegative = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), 
			wxSP_ARROW_KEYS, -10 * SPEED_SCALE, 0 * SPEED_SCALE, -2 * SPEED_SCALE);
		Connect(m_speedNegative->GetId(), wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(AEParamsCMPT::onSetParams));
		sizer->Add(m_speedNegative);

		speedSizer->Add(sizer);
	}
	topSizer->Add(speedSizer);
}

void AEParamsCMPT::initAnglePanel(wxSizer* topSizer)
{
	wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("角度"));
	wxBoxSizer* angleSizer = new wxStaticBoxSizer(bounding, wxVERTICAL);
	{
		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		sizer->Add(new wxStaticText(this, wxID_ANY, wxT("左小：")));

		m_angleLeftSmall = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), 
			wxSP_ARROW_KEYS, -1 * ANGLE_SCALE, 1 * ANGLE_SCALE, 0 * ANGLE_SCALE);
		Connect(m_angleLeftSmall->GetId(), wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(AEParamsCMPT::onSetParams));
		sizer->Add(m_angleLeftSmall);

		angleSizer->Add(sizer);
	}
	{
		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		sizer->Add(new wxStaticText(this, wxID_ANY, wxT("左大：")));

		m_angleLeftLarge = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), 
			wxSP_ARROW_KEYS, -1 * ANGLE_SCALE, 1 * ANGLE_SCALE, 0 * ANGLE_SCALE);
		Connect(m_angleLeftLarge->GetId(), wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(AEParamsCMPT::onSetParams));
		sizer->Add(m_angleLeftLarge);

		angleSizer->Add(sizer);
	}
	{
		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		sizer->Add(new wxStaticText(this, wxID_ANY, wxT("右小：")));

		m_angleRightSmall = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), 
			wxSP_ARROW_KEYS, -1 * ANGLE_SCALE, 1 * ANGLE_SCALE, 0 * ANGLE_SCALE);
		Connect(m_angleRightSmall->GetId(), wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(AEParamsCMPT::onSetParams));
		sizer->Add(m_angleRightSmall);

		angleSizer->Add(sizer);
	}
	{
		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		sizer->Add(new wxStaticText(this, wxID_ANY, wxT("右大：")));

		m_angleRightLarge = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), 
			wxSP_ARROW_KEYS, -1 * ANGLE_SCALE, 1 * ANGLE_SCALE, 0 * ANGLE_SCALE);
		Connect(m_angleRightLarge->GetId(), wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(AEParamsCMPT::onSetParams));
		sizer->Add(m_angleRightLarge);

		angleSizer->Add(sizer);
	}
	topSizer->Add(angleSizer);
}

void AEParamsCMPT::initTorquePanel(wxSizer* topSizer)
{
	wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("力矩"));
	wxBoxSizer* torqueSizer = new wxStaticBoxSizer(bounding, wxVERTICAL);
	{
		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		sizer->Add(new wxStaticText(this, wxID_ANY, wxT("最大值：")));

		m_maxTroque = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), wxSP_ARROW_KEYS, 0, 200, 20);
		Connect(m_maxTroque->GetId(), wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(AEParamsCMPT::onSetParams));
		sizer->Add(m_maxTroque);

		torqueSizer->Add(sizer);
	}
	topSizer->Add(torqueSizer);
}

void AEParamsCMPT::initControlPanel(wxSizer* topSizer)
{
	wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("操作"));
	wxBoxSizer* ctrlSizer = new wxStaticBoxSizer(bounding, wxVERTICAL);

	wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);

	wxButton* btnPositive = new wxButton(this, wxID_ANY, wxT("正向"), wxDefaultPosition, wxSize(50, -1));
	Connect(btnPositive->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AEParamsCMPT::onJointMotionPositive));
	btnSizer->Add(btnPositive);

	wxButton* btnNegative = new wxButton(this, wxID_ANY, wxT("负向"), wxDefaultPosition, wxSize(50, -1));
	Connect(btnNegative->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(AEParamsCMPT::onJointMotionNegative));
	btnSizer->Add(btnNegative);

	ctrlSizer->Add(btnSizer);

	topSizer->Add(ctrlSizer);
}

void AEParamsCMPT::onChoiceChanged(wxCommandEvent& event)
{
	int index = m_jointChoice->GetSelection();

	m_checkLimit->SetValue(m_joints.m_params.m_joints[index].enableLimit);
	m_checkMotor->SetValue(m_joints.m_params.m_joints[index].enableMotor);

	m_speedPositive->SetValue(m_joints.m_params.m_joints[index].positive_speed * SPEED_SCALE);
	m_speedNegative->SetValue(m_joints.m_params.m_joints[index].negative_speed * SPEED_SCALE);

	m_angleLeftSmall->SetValue(m_joints.m_params.m_joints[index].left_angle_small * ANGLE_SCALE);
	m_angleLeftLarge->SetValue(m_joints.m_params.m_joints[index].left_angle_large * ANGLE_SCALE);
	m_angleRightSmall->SetValue(m_joints.m_params.m_joints[index].right_angle_small * ANGLE_SCALE);
	m_angleRightLarge->SetValue(m_joints.m_params.m_joints[index].right_angle_large * ANGLE_SCALE);

	m_maxTroque->SetValue(m_joints.m_params.m_joints[index].max_torque);
}

void AEParamsCMPT::onSettingChanged(wxCommandEvent& event)
{
	int index = m_jointChoice->GetSelection();
	m_joints.m_params.m_joints[index].enableLimit = m_checkLimit->IsChecked();
	m_joints.m_params.m_joints[index].enableMotor = m_checkMotor->IsChecked();

	m_joints.setJointParams(index);
}

void AEParamsCMPT::onSetParams(wxSpinEvent& event)
{
	int index = m_jointChoice->GetSelection();

	m_joints.m_params.m_joints[index].positive_speed = m_speedPositive->GetValue() / SPEED_SCALE;
	m_joints.m_params.m_joints[index].negative_speed = m_speedNegative->GetValue() / SPEED_SCALE;

	m_joints.m_params.m_joints[index].left_angle_small = m_angleLeftSmall->GetValue() / ANGLE_SCALE;
	m_joints.m_params.m_joints[index].left_angle_large = m_angleLeftLarge->GetValue() / ANGLE_SCALE;
	m_joints.m_params.m_joints[index].right_angle_small = m_angleRightSmall->GetValue() / ANGLE_SCALE;
	m_joints.m_params.m_joints[index].right_angle_large = m_angleRightLarge->GetValue() / ANGLE_SCALE;

	m_joints.m_params.m_joints[index].max_torque = m_maxTroque->GetValue();

	m_joints.setJointParams(index);
}

void AEParamsCMPT::onJointMotionPositive(wxCommandEvent& event)
{
	m_joints.setJointMotion(m_jointChoice->GetSelection(), true);
}

void AEParamsCMPT::onJointMotionNegative(wxCommandEvent& event)
{
	m_joints.setJointMotion(m_jointChoice->GetSelection(), false);
}

//////////////////////////////////////////////////////////////////////////
// class AEParamsCMPT::SetBodyAliveVisitor
//////////////////////////////////////////////////////////////////////////

AEParamsCMPT::SetBodyAliveVisitor::SetBodyAliveVisitor(bool alive)
{
	m_alive = alive;
}

void AEParamsCMPT::SetBodyAliveVisitor::
visit(IObject* object, bool& bFetchNext)
{
	wxgui::ISprite* sprite = static_cast<wxgui::ISprite*>(object);
	sprite->getBody()->setAlive(m_alive);
	bFetchNext = true;
}