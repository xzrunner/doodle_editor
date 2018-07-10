#include "BodyPropertySetting.h"
#include "BodyData.h"

using namespace deditor::modeling;

BodyPropertySetting::BodyPropertySetting(wxgui::EditPanel* editPanel, wxgui::ISprite* sprite)
	: wxgui::IPropertySetting(editPanel, wxT("Body"))
{
	m_body = static_cast<BodyData*>(sprite->getUserData());
	assert(m_body);
}

void BodyPropertySetting::updatePanel(wxgui::PropertySettingPanel* panel)
{
	wxPropertyGrid* pg = panel->getPG();

	if (getPGType(pg) == m_type)
	{
		pg->GetProperty(wxT("Name"))->SetValue(m_body->m_name);
		pg->GetProperty(wxT("Type"))->SetValue((int) m_body->m_type);
		pg->GetProperty(wxT("GravityScale"))->SetValue(m_body->m_gravityScale);
	}
	else
	{
		pg->Clear();

		pg->Append(new wxStringProperty(wxT("Name"), wxPG_LABEL, m_body->m_name));

 		wxPGChoices eech;
 		eech.Add(wxT("static"));
 		eech.Add(wxT("kinematic"));
 		eech.Add(wxT("dynamic"));
		wxEnumProperty* typeChoice = new wxEnumProperty(wxT("Type"), wxPG_LABEL, eech);
		typeChoice->SetChoiceSelection((int)m_body->m_type);
 		pg->Append(typeChoice);

		pg->Append(new wxFloatProperty(wxT("GravityScale"), wxPG_LABEL, m_body->m_gravityScale));
	}
}

void BodyPropertySetting::onPropertyGridChange(const wxString& name, const wxAny& value)
{
	if (value.IsNull())
		return;

	if (name == wxT("Name"))
		m_body->m_name = wxANY_AS(value, wxString);
	else if (name == wxT("Type"))
		m_body->m_type = BodyData::Type(wxANY_AS(value, int));
	else if (name == wxT("GravityScale"))
		m_body->m_gravityScale = wxANY_AS(value, float);

	m_editPanel->Refresh();
}

void BodyPropertySetting::updatePropertyGrid(wxgui::PropertySettingPanel* panel)
{
	updatePanel(panel);
}

void BodyPropertySetting::enablePropertyGrid(wxgui::PropertySettingPanel* panel, bool bEnable)
{
	// 
}