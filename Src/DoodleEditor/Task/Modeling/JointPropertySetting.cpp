#include "JointPropertySetting.h"
#include "RevoluteJoint.h"
#include "PrismaticJoint.h"
#include "DistanceJoint.h"
#include "WheelJoint.h"

using namespace deditor::modeling;

JointPropertySetting::JointPropertySetting(wxgui::EditPanel* editPanel, JointData* joint)
	: wxgui::IPropertySetting(editPanel, wxT("Joint"))
{
	m_joint = joint;
}

void JointPropertySetting::updatePanel(wxgui::PropertySettingPanel* panel)
{
	wxPropertyGrid* pg = panel->getPG();

	bool build;
	if (getPGType(pg) == m_type)
	{
		build = false;
		pg->GetProperty(wxT("Name"))->SetValue(m_joint->m_name);
		pg->GetProperty(wxT("collideConnected"))->SetValue(m_joint->collideConnected);
	}
	else
	{
		build = true;
		pg->Clear();
		pg->Append(new wxStringProperty(wxT("Name"), wxPG_LABEL, m_joint->m_name));
		pg->Append(new wxBoolProperty(wxT("collideConnected"), wxPG_LABEL, m_joint->collideConnected));
	}

	switch (m_joint->type)
	{
	case JointData::e_revoluteJoint:
		if (build) 
			createPropertyPanel(static_cast<RevoluteJoint*>(m_joint), pg);
		else
			updatePropertyPanel(static_cast<RevoluteJoint*>(m_joint), pg);
		break;
	case JointData::e_prismaticJoint:
		if (build) 
			createPropertyPanel(static_cast<PrismaticJoint*>(m_joint), pg);
		else
			updatePropertyPanel(static_cast<PrismaticJoint*>(m_joint), pg);
		break;
	case JointData::e_distanceJoint:
		if (build) 
			createPropertyPanel(static_cast<DistanceJoint*>(m_joint), pg);
		else
			updatePropertyPanel(static_cast<DistanceJoint*>(m_joint), pg);
		break;
	case JointData::e_wheelJoint:
		if (build) 
			createPropertyPanel(static_cast<WheelJoint*>(m_joint), pg);
		else
			updatePropertyPanel(static_cast<WheelJoint*>(m_joint), pg);
		break;
	}
}

void JointPropertySetting::onPropertyGridChange(const wxString& name, const wxAny& value)
{
	if (value.IsNull())
		return;

	if (name == wxT("Name"))
		m_joint->m_name = wxANY_AS(value, wxString);
	else if (name == wxT("collideConnected"))
		m_joint->collideConnected = wxANY_AS(value, bool);
	switch (m_joint->type)
	{
	case JointData::e_revoluteJoint:
		onPropertyGridChange(static_cast<RevoluteJoint*>(m_joint), name, value);
		break;
	case JointData::e_prismaticJoint:
		onPropertyGridChange(static_cast<PrismaticJoint*>(m_joint), name, value);
		break;
	case JointData::e_distanceJoint:
		onPropertyGridChange(static_cast<DistanceJoint*>(m_joint), name, value);
		break;
	case JointData::e_wheelJoint:
		onPropertyGridChange(static_cast<WheelJoint*>(m_joint), name, value);
		break;
	}

	m_editPanel->Refresh();
}

void JointPropertySetting::updatePropertyGrid(wxgui::PropertySettingPanel* panel)
{
	updatePanel(panel);
}

void JointPropertySetting::enablePropertyGrid(wxgui::PropertySettingPanel* panel, bool bEnable)
{
	// 
}

void JointPropertySetting::createPropertyPanel(RevoluteJoint* joint, wxPropertyGrid* pg)
{
	wxPGProperty* localAnchorAProp = pg->Append(new wxStringProperty(wxT("localAnchorA"),
		wxPG_LABEL, wxT("<composed>")));
	pg->AppendIn(localAnchorAProp, new wxFloatProperty(wxT("x"), wxPG_LABEL, joint->localAnchorA.x));
	pg->SetPropertyAttribute(wxT("localAnchorA.x"), "Precision", 2);
	pg->AppendIn(localAnchorAProp, new wxFloatProperty(wxT("y"), wxPG_LABEL, joint->localAnchorA.y));
	pg->SetPropertyAttribute(wxT("localAnchorA.y"), "Precision", 2);

	wxPGProperty* localAnchorBProp = pg->Append(new wxStringProperty(wxT("localAnchorB"),
		wxPG_LABEL, wxT("<composed>")));
	pg->AppendIn(localAnchorBProp, new wxFloatProperty(wxT("x"), wxPG_LABEL, joint->localAnchorB.x));
	pg->SetPropertyAttribute(wxT("localAnchorB.x"), "Precision", 2);
	pg->AppendIn(localAnchorBProp, new wxFloatProperty(wxT("y"), wxPG_LABEL, joint->localAnchorB.y));
	pg->SetPropertyAttribute(wxT("localAnchorB.y"), "Precision", 2);

	pg->Append(new wxFloatProperty(wxT("referenceAngle"), wxPG_LABEL, joint->referenceAngle));
	pg->SetPropertyAttribute(wxT("referenceAngle"), "Precision", 2);

	pg->Append(new wxBoolProperty(wxT("enableLimit"), wxPG_LABEL, joint->enableLimit));

	pg->Append(new wxFloatProperty(wxT("lowerAngle"), wxPG_LABEL, joint->lowerAngle));
	pg->SetPropertyAttribute(wxT("lowerAngle"), "Precision", 2);

	pg->Append(new wxFloatProperty(wxT("upperAngle"), wxPG_LABEL, joint->upperAngle));
	pg->SetPropertyAttribute(wxT("upperAngle"), "Precision", 2);

	pg->Append(new wxBoolProperty(wxT("enableMotor"), wxPG_LABEL, joint->enableMotor));

	pg->Append(new wxFloatProperty(wxT("maxMotorTorque"), wxPG_LABEL, joint->maxMotorTorque));
	pg->SetPropertyAttribute(wxT("maxMotorTorque"), "Precision", 2);

	pg->Append(new wxFloatProperty(wxT("motorSpeed"), wxPG_LABEL, joint->motorSpeed));
	pg->SetPropertyAttribute(wxT("motorSpeed"), "Precision", 2);
}

void JointPropertySetting::updatePropertyPanel(RevoluteJoint* joint, wxPropertyGrid* pg)
{
	pg->GetProperty(wxT("localAnchorA.x"))->SetValue(joint->localAnchorA.x);
	pg->GetProperty(wxT("localAnchorA.y"))->SetValue(joint->localAnchorA.y);

	pg->GetProperty(wxT("localAnchorB.x"))->SetValue(joint->localAnchorB.x);
	pg->GetProperty(wxT("localAnchorB.y"))->SetValue(joint->localAnchorB.y);

	pg->GetProperty(wxT("referenceAngle"))->SetValue(joint->referenceAngle);

	pg->GetProperty(wxT("enableLimit"))->SetValue(joint->enableLimit);

	pg->GetProperty(wxT("lowerAngle"))->SetValue(joint->lowerAngle);
	pg->GetProperty(wxT("upperAngle"))->SetValue(joint->upperAngle);

	pg->GetProperty(wxT("enableMotor"))->SetValue(joint->enableMotor);

	pg->GetProperty(wxT("maxMotorTorque"))->SetValue(joint->maxMotorTorque);

	pg->GetProperty(wxT("motorSpeed"))->SetValue(joint->motorSpeed);
}

void JointPropertySetting::onPropertyGridChange(RevoluteJoint* joint, 
												const wxString& name, 
												const wxAny& value)
{
	if (name == wxT("localAnchorA.x"))
		joint->localAnchorA.x = wxANY_AS(value, float);
	else if (name == wxT("localAnchorA.y"))
		joint->localAnchorA.y = wxANY_AS(value, float);
	else if (name == wxT("localAnchorB.x"))
		joint->localAnchorB.x = wxANY_AS(value, float);
	else if (name == wxT("localAnchorB.y"))
		joint->localAnchorB.y = wxANY_AS(value, float);
	else if (name == wxT("referenceAngle"))
		joint->referenceAngle = wxANY_AS(value, float);
	else if (name == wxT("enableLimit"))
		joint->enableLimit = wxANY_AS(value, bool);
	else if (name == wxT("lowerAngle"))
		joint->lowerAngle = wxANY_AS(value, float);
	else if (name == wxT("upperAngle"))
		joint->upperAngle = wxANY_AS(value, float);
	else if (name == wxT("enableMotor"))
		joint->enableMotor = wxANY_AS(value, bool);
	else if (name == wxT("maxMotorTorque"))
		joint->maxMotorTorque = wxANY_AS(value, float);
	else if (name == wxT("motorSpeed"))
		joint->motorSpeed = wxANY_AS(value, float);
}

void JointPropertySetting::createPropertyPanel(PrismaticJoint* joint, wxPropertyGrid* pg)
{
	wxPGProperty* localAnchorAProp = pg->Append(new wxStringProperty(wxT("localAnchorA"),
		wxPG_LABEL, wxT("<composed>")));
	pg->AppendIn(localAnchorAProp, new wxFloatProperty(wxT("x"), wxPG_LABEL, joint->localAnchorA.x));
	pg->SetPropertyAttribute(wxT("localAnchorA.x"), "Precision", 2);
	pg->AppendIn(localAnchorAProp, new wxFloatProperty(wxT("y"), wxPG_LABEL, joint->localAnchorA.y));
	pg->SetPropertyAttribute(wxT("localAnchorA.y"), "Precision", 2);

	wxPGProperty* localAnchorBProp = pg->Append(new wxStringProperty(wxT("localAnchorB"),
		wxPG_LABEL, wxT("<composed>")));
	pg->AppendIn(localAnchorBProp, new wxFloatProperty(wxT("x"), wxPG_LABEL, joint->localAnchorB.x));
	pg->SetPropertyAttribute(wxT("localAnchorB.x"), "Precision", 2);
	pg->AppendIn(localAnchorBProp, new wxFloatProperty(wxT("y"), wxPG_LABEL, joint->localAnchorB.y));
	pg->SetPropertyAttribute(wxT("localAnchorB.y"), "Precision", 2);

	wxPGProperty* localAxisAProp = pg->Append(new wxStringProperty(wxT("localAxisA"),
		wxPG_LABEL, wxT("<composed>")));
	pg->AppendIn(localAxisAProp, new wxFloatProperty(wxT("x"), wxPG_LABEL, joint->localAxisA.x));
	pg->SetPropertyAttribute(wxT("localAxisA.x"), "Precision", 2);
	pg->AppendIn(localAxisAProp, new wxFloatProperty(wxT("y"), wxPG_LABEL, joint->localAxisA.y));
	pg->SetPropertyAttribute(wxT("localAxisA.y"), "Precision", 2);

	pg->Append(new wxFloatProperty(wxT("referenceAngle"), wxPG_LABEL, joint->referenceAngle));
	pg->SetPropertyAttribute(wxT("referenceAngle"), "Precision", 2);

	pg->Append(new wxBoolProperty(wxT("enableLimit"), wxPG_LABEL, joint->enableLimit));

	pg->Append(new wxFloatProperty(wxT("lowerTranslation"), wxPG_LABEL, joint->lowerTranslation));
	pg->SetPropertyAttribute(wxT("lowerTranslation"), "Precision", 2);

	pg->Append(new wxFloatProperty(wxT("upperTranslation"), wxPG_LABEL, joint->upperTranslation));
	pg->SetPropertyAttribute(wxT("upperTranslation"), "Precision", 2);

	pg->Append(new wxBoolProperty(wxT("enableMotor"), wxPG_LABEL, joint->enableMotor));

	pg->Append(new wxFloatProperty(wxT("maxMotorForce"), wxPG_LABEL, joint->maxMotorForce));
	pg->SetPropertyAttribute(wxT("maxMotorForce"), "Precision", 2);

	pg->Append(new wxFloatProperty(wxT("motorSpeed"), wxPG_LABEL, joint->motorSpeed));
	pg->SetPropertyAttribute(wxT("motorSpeed"), "Precision", 2);
}

void JointPropertySetting::updatePropertyPanel(PrismaticJoint* joint, wxPropertyGrid* pg)
{
	pg->GetProperty(wxT("localAnchorA.x"))->SetValue(joint->localAnchorA.x);
	pg->GetProperty(wxT("localAnchorA.y"))->SetValue(joint->localAnchorA.y);

	pg->GetProperty(wxT("localAnchorB.x"))->SetValue(joint->localAnchorB.x);
	pg->GetProperty(wxT("localAnchorB.y"))->SetValue(joint->localAnchorB.y);

	pg->GetProperty(wxT("localAxisA.x"))->SetValue(joint->localAxisA.x);
	pg->GetProperty(wxT("localAxisA.y"))->SetValue(joint->localAxisA.y);

	pg->GetProperty(wxT("referenceAngle"))->SetValue(joint->referenceAngle);

	pg->GetProperty(wxT("enableLimit"))->SetValue(joint->enableLimit);

	pg->GetProperty(wxT("lowerTranslation"))->SetValue(joint->lowerTranslation);
	pg->GetProperty(wxT("upperTranslation"))->SetValue(joint->upperTranslation);

	pg->GetProperty(wxT("enableMotor"))->SetValue(joint->enableMotor);

	pg->GetProperty(wxT("maxMotorForce"))->SetValue(joint->maxMotorForce);

	pg->GetProperty(wxT("motorSpeed"))->SetValue(joint->motorSpeed);
}

void JointPropertySetting::onPropertyGridChange(PrismaticJoint* joint, 
												const wxString& name, 
												const wxAny& value)
{
	if (name == wxT("localAnchorA.x"))
		joint->localAnchorA.x = wxANY_AS(value, float);
	else if (name == wxT("localAnchorA.y"))
		joint->localAnchorA.y = wxANY_AS(value, float);
	else if (name == wxT("localAnchorB.x"))
		joint->localAnchorB.x = wxANY_AS(value, float);
	else if (name == wxT("localAnchorB.y"))
		joint->localAnchorB.y = wxANY_AS(value, float);
	else if (name == wxT("localAxisA.x"))
		joint->localAxisA.x = wxANY_AS(value, float);
	else if (name == wxT("localAxisA.y"))
		joint->localAxisA.y = wxANY_AS(value, float);
	else if (name == wxT("referenceAngle"))
		joint->referenceAngle = wxANY_AS(value, float);
	else if (name == wxT("enableLimit"))
		joint->enableLimit = wxANY_AS(value, bool);
	else if (name == wxT("lowerTranslation"))
		joint->lowerTranslation = wxANY_AS(value, float);
	else if (name == wxT("upperTranslation"))
		joint->upperTranslation = wxANY_AS(value, float);
	else if (name == wxT("enableMotor"))
		joint->enableMotor = wxANY_AS(value, bool);
	else if (name == wxT("maxMotorForce"))
		joint->maxMotorForce = wxANY_AS(value, float);
	else if (name == wxT("motorSpeed"))
		joint->motorSpeed = wxANY_AS(value, float);
}

void JointPropertySetting::createPropertyPanel(DistanceJoint* joint, wxPropertyGrid* pg)
{
	wxPGProperty* localAnchorAProp = pg->Append(new wxStringProperty(wxT("localAnchorA"),
		wxPG_LABEL, wxT("<composed>")));
	pg->AppendIn(localAnchorAProp, new wxFloatProperty(wxT("x"), wxPG_LABEL, joint->localAnchorA.x));
	pg->SetPropertyAttribute(wxT("localAnchorA.x"), "Precision", 2);
	pg->AppendIn(localAnchorAProp, new wxFloatProperty(wxT("y"), wxPG_LABEL, joint->localAnchorA.y));
	pg->SetPropertyAttribute(wxT("localAnchorA.y"), "Precision", 2);

	wxPGProperty* localAnchorBProp = pg->Append(new wxStringProperty(wxT("localAnchorB"),
		wxPG_LABEL, wxT("<composed>")));
	pg->AppendIn(localAnchorBProp, new wxFloatProperty(wxT("x"), wxPG_LABEL, joint->localAnchorB.x));
	pg->SetPropertyAttribute(wxT("localAnchorB.x"), "Precision", 2);
	pg->AppendIn(localAnchorBProp, new wxFloatProperty(wxT("y"), wxPG_LABEL, joint->localAnchorB.y));
	pg->SetPropertyAttribute(wxT("localAnchorB.y"), "Precision", 2);

	pg->Append(new wxFloatProperty(wxT("length"), wxPG_LABEL, joint->length));
	pg->SetPropertyAttribute(wxT("length"), "Precision", 2);

	pg->Append(new wxFloatProperty(wxT("frequencyHz"), wxPG_LABEL, joint->frequencyHz));
	pg->SetPropertyAttribute(wxT("frequencyHz"), "Precision", 2);

	pg->Append(new wxFloatProperty(wxT("dampingRatio"), wxPG_LABEL, joint->dampingRatio));
	pg->SetPropertyAttribute(wxT("dampingRatio"), "Precision", 2);
}

void JointPropertySetting::updatePropertyPanel(DistanceJoint* joint, wxPropertyGrid* pg)
{
	pg->GetProperty(wxT("localAnchorA.x"))->SetValue(joint->localAnchorA.x);
	pg->GetProperty(wxT("localAnchorA.y"))->SetValue(joint->localAnchorA.y);

	pg->GetProperty(wxT("localAnchorB.x"))->SetValue(joint->localAnchorB.x);
	pg->GetProperty(wxT("localAnchorB.y"))->SetValue(joint->localAnchorB.y);

	pg->GetProperty(wxT("length"))->SetValue(joint->length);

	pg->GetProperty(wxT("frequencyHz"))->SetValue(joint->frequencyHz);

	pg->GetProperty(wxT("dampingRatio"))->SetValue(joint->dampingRatio);
}

void JointPropertySetting::onPropertyGridChange(DistanceJoint* joint, const wxString& name, const wxAny& value)
{
	if (name == wxT("localAnchorA.x"))
		joint->localAnchorA.x = wxANY_AS(value, float);
	else if (name == wxT("localAnchorA.y"))
		joint->localAnchorA.y = wxANY_AS(value, float);
	else if (name == wxT("localAnchorB.x"))
		joint->localAnchorB.x = wxANY_AS(value, float);
	else if (name == wxT("localAnchorB.y"))
		joint->localAnchorB.y = wxANY_AS(value, float);
	else if (name == wxT("length"))
		joint->length = wxANY_AS(value, float);
	else if (name == wxT("frequencyHz"))
		joint->frequencyHz = wxANY_AS(value, float);
	else if (name == wxT("dampingRatio"))
		joint->dampingRatio = wxANY_AS(value, float);
}

void JointPropertySetting::createPropertyPanel(WheelJoint* joint, wxPropertyGrid* pg)
{
	wxPGProperty* localAnchorAProp = pg->Append(new wxStringProperty(wxT("localAnchorA"),
		wxPG_LABEL, wxT("<composed>")));
	pg->AppendIn(localAnchorAProp, new wxFloatProperty(wxT("x"), wxPG_LABEL, joint->localAnchorA.x));
	pg->SetPropertyAttribute(wxT("localAnchorA.x"), "Precision", 2);
	pg->AppendIn(localAnchorAProp, new wxFloatProperty(wxT("y"), wxPG_LABEL, joint->localAnchorA.y));
	pg->SetPropertyAttribute(wxT("localAnchorA.y"), "Precision", 2);

	wxPGProperty* localAnchorBProp = pg->Append(new wxStringProperty(wxT("localAnchorB"),
		wxPG_LABEL, wxT("<composed>")));
	pg->AppendIn(localAnchorBProp, new wxFloatProperty(wxT("x"), wxPG_LABEL, joint->localAnchorB.x));
	pg->SetPropertyAttribute(wxT("localAnchorB.x"), "Precision", 2);
	pg->AppendIn(localAnchorBProp, new wxFloatProperty(wxT("y"), wxPG_LABEL, joint->localAnchorB.y));
	pg->SetPropertyAttribute(wxT("localAnchorB.y"), "Precision", 2);

	wxPGProperty* localAxisAProp = pg->Append(new wxStringProperty(wxT("localAxisA"),
		wxPG_LABEL, wxT("<composed>")));
	pg->AppendIn(localAxisAProp, new wxFloatProperty(wxT("x"), wxPG_LABEL, joint->localAxisA.x));
	pg->SetPropertyAttribute(wxT("localAxisA.x"), "Precision", 2);
	pg->AppendIn(localAxisAProp, new wxFloatProperty(wxT("y"), wxPG_LABEL, joint->localAxisA.y));
	pg->SetPropertyAttribute(wxT("localAxisA.y"), "Precision", 2);

	pg->Append(new wxBoolProperty(wxT("enableMotor"), wxPG_LABEL, joint->enableMotor));

	pg->Append(new wxFloatProperty(wxT("maxMotorTorque"), wxPG_LABEL, joint->maxMotorTorque));
	pg->SetPropertyAttribute(wxT("maxMotorTorque"), "Precision", 2);

	pg->Append(new wxFloatProperty(wxT("motorSpeed"), wxPG_LABEL, joint->motorSpeed));
	pg->SetPropertyAttribute(wxT("motorSpeed"), "Precision", 2);

	pg->Append(new wxFloatProperty(wxT("frequencyHz"), wxPG_LABEL, joint->frequencyHz));
	pg->SetPropertyAttribute(wxT("frequencyHz"), "Precision", 2);

	pg->Append(new wxFloatProperty(wxT("dampingRatio"), wxPG_LABEL, joint->dampingRatio));
	pg->SetPropertyAttribute(wxT("dampingRatio"), "Precision", 2);
}

void JointPropertySetting::updatePropertyPanel(WheelJoint* joint, wxPropertyGrid* pg)
{
	pg->GetProperty(wxT("localAnchorA.x"))->SetValue(joint->localAnchorA.x);
	pg->GetProperty(wxT("localAnchorA.y"))->SetValue(joint->localAnchorA.y);

	pg->GetProperty(wxT("localAnchorB.x"))->SetValue(joint->localAnchorB.x);
	pg->GetProperty(wxT("localAnchorB.y"))->SetValue(joint->localAnchorB.y);

	pg->GetProperty(wxT("localAxisA.x"))->SetValue(joint->localAxisA.x);
	pg->GetProperty(wxT("localAxisA.y"))->SetValue(joint->localAxisA.y);

	pg->GetProperty(wxT("enableMotor"))->SetValue(joint->enableMotor);
	pg->GetProperty(wxT("maxMotorTorque"))->SetValue(joint->maxMotorTorque);

	pg->GetProperty(wxT("motorSpeed"))->SetValue(joint->motorSpeed);

	pg->GetProperty(wxT("frequencyHz"))->SetValue(joint->frequencyHz);
	pg->GetProperty(wxT("dampingRatio"))->SetValue(joint->dampingRatio);
}

void JointPropertySetting::onPropertyGridChange(WheelJoint* joint, const wxString& name, 
												const wxAny& value)
{
	if (name == wxT("localAnchorA.x"))
		joint->localAnchorA.x = wxANY_AS(value, float);
	else if (name == wxT("localAnchorA.y"))
		joint->localAnchorA.y = wxANY_AS(value, float);
	else if (name == wxT("localAnchorB.x"))
		joint->localAnchorB.x = wxANY_AS(value, float);
	else if (name == wxT("localAnchorB.y"))
		joint->localAnchorB.y = wxANY_AS(value, float);
	else if (name == wxT("localAxisA.x"))
		joint->localAxisA.x = wxANY_AS(value, float);
	else if (name == wxT("localAxisA.y"))
		joint->localAxisA.y = wxANY_AS(value, float);
	else if (name == wxT("enableMotor"))
		joint->enableMotor = wxANY_AS(value, bool);
	else if (name == wxT("maxMotorTorque"))
		joint->maxMotorTorque = wxANY_AS(value, float);
	else if (name == wxT("motorSpeed"))
		joint->motorSpeed = wxANY_AS(value, float);
	else if (name == wxT("frequencyHz"))
		joint->frequencyHz = wxANY_AS(value, float);
	else if (name == wxT("dampingRatio"))
		joint->dampingRatio = wxANY_AS(value, float);
}