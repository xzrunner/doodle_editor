#include "MotorbikeCMPT.h"
#include "StagePanel.h"
#include "Actor.h"
#include "Blackboard.h"

#include <wx/spinctrl.h>

using namespace deditor::motox;

MotorbikeCMPT::MotorbikeCMPT(wxWindow* parent, const wxString& name,
							 StagePanel* editPanel)
	: wxgui::AbstractEditCMPT(parent, name, editPanel)
	, m_editPanel(editPanel)
{
	m_editOP = new wxgui::DragPhysicsOP(editPanel, editPanel->getWorld(), editPanel->getGround());
}

wxSizer* MotorbikeCMPT::initLayout()
{
	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(initControlPanel());
	sizer->AddSpacer(20);
	sizer->Add(initMotoSettingsPanel());
	sizer->AddSpacer(10);
	sizer->Add(initPlayerSettingsPanel());
	sizer->AddSpacer(10);
	sizer->Add(initTrackSettingsPanel());
	return sizer;
}

wxSizer* MotorbikeCMPT::initControlPanel()
{
	wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("系统"));
	wxBoxSizer* sizer = new wxStaticBoxSizer(bounding, wxVERTICAL);
	{
		wxButton* btnActive = new wxButton(this, wxID_ANY, wxT("激活摩托"));
		Connect(btnActive->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(MotorbikeCMPT::onActiveMotoBike));
		sizer->Add(btnActive);
	}
	sizer->AddSpacer(10);
	{
		wxCheckBox* cameraFocus = new wxCheckBox(this, wxID_ANY, wxT("跟随摩托"));
		cameraFocus->SetValue(Blackboard::isCameraFocusOnMotobike);
		Connect(cameraFocus->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(MotorbikeCMPT::onSetCameraFocus));
		sizer->Add(cameraFocus);
	}
	sizer->AddSpacer(10);
	{
		wxBoxSizer* gravitySizer = new wxBoxSizer(wxHORIZONTAL);
		gravitySizer->Add(new wxStaticText(this, wxID_ANY, wxT("重力加速度：")));

		wxSpinCtrl* gravityCtrl = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(70, -1), 
			wxSP_ARROW_KEYS, 10, 50, Blackboard::gravity);
		Connect(gravityCtrl->GetId(), wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(MotorbikeCMPT::onSetGravity));
		gravitySizer->Add(gravityCtrl);

		sizer->Add(gravitySizer);
	}
	return sizer;
}

wxSizer* MotorbikeCMPT::initMotoSettingsPanel()
{
	wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("摩托"));
	wxBoxSizer* settingSizer = new wxStaticBoxSizer(bounding, wxVERTICAL);
	{
		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		sizer->Add(new wxStaticText(this, wxID_ANY, wxT("摩擦：")));

		wxSpinCtrl* wheelFriction = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(70, -1), 
			wxSP_ARROW_KEYS, 0, 100, Blackboard::wheelFriction * 10);
		Connect(wheelFriction->GetId(), wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(MotorbikeCMPT::onWheelFrictionChanged));
		sizer->Add(wheelFriction);

		sizer->Add(new wxStaticText(this, wxID_ANY, wxT(" * 0.1")));

		settingSizer->Add(sizer);
	}
	{
		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		sizer->Add(new wxStaticText(this, wxID_ANY, wxT("密度：")));

		wxSpinCtrl* motoDensity = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(70, -1), 
			wxSP_ARROW_KEYS, 0, 100, Blackboard::motoDensity * 10);
		Connect(motoDensity->GetId(), wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(MotorbikeCMPT::onMotoDensityChanged));
		sizer->Add(motoDensity);

		sizer->Add(new wxStaticText(this, wxID_ANY, wxT(" * 0.1")));

		settingSizer->Add(sizer);
	}
	{
		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		sizer->Add(new wxStaticText(this, wxID_ANY, wxT("速度：")));

		wxSpinCtrl* speed = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(70, -1), 
			wxSP_ARROW_KEYS, 0, 100, Blackboard::speed);
		Connect(speed->GetId(), wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(MotorbikeCMPT::onSpeedChanged));
		sizer->Add(speed);

		settingSizer->Add(sizer);
	}
	{
		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		sizer->Add(new wxStaticText(this, wxID_ANY, wxT("加速度：")));

		wxSpinCtrl* acceleration = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(70, -1), 
			wxSP_ARROW_KEYS, 0, 50, Blackboard::acceleration);
		Connect(acceleration->GetId(), wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(MotorbikeCMPT::onAccelerationChanged));
		sizer->Add(acceleration);

		settingSizer->Add(sizer);
	}
	{
		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		sizer->Add(new wxStaticText(this, wxID_ANY, wxT("扭矩：")));

		wxSpinCtrl* motoTorque = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(70, -1), 
			wxSP_ARROW_KEYS, 400, 1000, Blackboard::motoTorque);
		Connect(motoTorque->GetId(), wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(MotorbikeCMPT::onMotorTorqueChanged));
		sizer->Add(motoTorque);

		settingSizer->Add(sizer);
	}
	return settingSizer;
}

wxSizer* MotorbikeCMPT::initPlayerSettingsPanel()
{
	wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("人"));
	wxBoxSizer* settingSizer = new wxStaticBoxSizer(bounding, wxVERTICAL);
	{
		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		sizer->Add(new wxStaticText(this, wxID_ANY, wxT("密度：")));

		wxSpinCtrl* playerDensity = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(70, -1), 
			wxSP_ARROW_KEYS, 0, 100, Blackboard::playerDensity * 10);
		Connect(playerDensity->GetId(), wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(MotorbikeCMPT::onPlayerDensityChanged));
		sizer->Add(playerDensity);

		sizer->Add(new wxStaticText(this, wxID_ANY, wxT(" * 0.1")));

		settingSizer->Add(sizer);
	}
	{
		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		sizer->Add(new wxStaticText(this, wxID_ANY, wxT("力矩：")));

		wxSpinCtrl* playerTorque = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(70, -1), 
			wxSP_ARROW_KEYS, 1000, 2000, Blackboard::playerTorque);
		Connect(playerTorque->GetId(), wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(MotorbikeCMPT::onPlayerTorqueChanged));
		sizer->Add(playerTorque);

		settingSizer->Add(sizer);
	}
	return settingSizer;
}

wxSizer* MotorbikeCMPT::initTrackSettingsPanel()
{
	wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("赛道"));
	wxBoxSizer* settingSizer = new wxStaticBoxSizer(bounding, wxVERTICAL);
	{
		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		sizer->Add(new wxStaticText(this, wxID_ANY, wxT("摩擦：")));

		wxSpinCtrl* trackFriction = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(70, -1), 
			wxSP_ARROW_KEYS, 0, 100, Blackboard::trackFriction * 10);
		Connect(trackFriction->GetId(), wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(MotorbikeCMPT::onTrackFrictionChanged));
		sizer->Add(trackFriction);

		sizer->Add(new wxStaticText(this, wxID_ANY, wxT(" * 0.1")));

		settingSizer->Add(sizer);
	}
	return settingSizer;
}

void MotorbikeCMPT::onActiveMotoBike(wxCommandEvent& event)
{
	Actor* actor = m_editPanel->getActor();
	if (actor)
	{
		actor->load();

		m_editPanel->getWorld()->SetGravity(b2Vec2(0.0f, -Blackboard::gravity));

		actor->setValue(Actor::e_SetWheelFriction, Blackboard::wheelFriction);
		actor->setValue(Actor::e_SetMotoDensity, Blackboard::motoDensity);
		actor->setValue(Actor::e_SetSpeed, Blackboard::speed);
		actor->setValue(Actor::e_SetAcc, Blackboard::acceleration);
		actor->setValue(Actor::e_SetMaxMotorTorque, Blackboard::motoTorque);

		actor->setValue(Actor::e_SetPlayerDensity, Blackboard::playerDensity);
		actor->setValue(Actor::e_SetTorque, Blackboard::playerTorque);

		m_editPanel->setTracksFriction(Blackboard::trackFriction);
	}
}

void MotorbikeCMPT::onSetCameraFocus(wxCommandEvent& event)
{
	Blackboard::isCameraFocusOnMotobike = event.IsChecked();
}

void MotorbikeCMPT::onSetGravity(wxSpinEvent& event)
{
	m_editPanel->getWorld()->SetGravity(b2Vec2(0.0f, -Blackboard::gravity));
}

void MotorbikeCMPT::onWheelFrictionChanged(wxSpinEvent& event)
{
	Actor* actor = m_editPanel->getActor();
	if (actor)
		actor->setValue(Actor::e_SetWheelFriction, event.GetValue() * 0.1f);
}

void MotorbikeCMPT::onMotoDensityChanged(wxSpinEvent& event)
{
	Actor* actor = m_editPanel->getActor();
	if (actor)
		actor->setValue(Actor::e_SetMotoDensity, event.GetValue() * 0.1f);
}

void MotorbikeCMPT::onSpeedChanged(wxSpinEvent& event)
{
	Actor* actor = m_editPanel->getActor();
	if (actor)
		actor->setValue(Actor::e_SetSpeed, event.GetInt());
}

void MotorbikeCMPT::onAccelerationChanged(wxSpinEvent& event)
{
	Actor* actor = m_editPanel->getActor();
	if (actor)
		actor->setValue(Actor::e_SetAcc, event.GetValue());
}

void MotorbikeCMPT::onMotorTorqueChanged(wxSpinEvent& event)
{
	Actor* actor = m_editPanel->getActor();
	if (actor)
		actor->setValue(Actor::e_SetMaxMotorTorque, event.GetValue());
}

void MotorbikeCMPT::onPlayerDensityChanged(wxSpinEvent& event)
{
	Actor* actor = m_editPanel->getActor();
	if (actor)
		actor->setValue(Actor::e_SetPlayerDensity, event.GetValue() * 0.1f);
}

void MotorbikeCMPT::onPlayerTorqueChanged(wxSpinEvent& event)
{
	Actor* actor = m_editPanel->getActor();
	if (actor)
		actor->setValue(Actor::e_SetTorque, event.GetValue());
}

void MotorbikeCMPT::onTrackFrictionChanged(wxSpinEvent& event)
{
	m_editPanel->setTracksFriction(event.GetValue() * 0.1f);
}