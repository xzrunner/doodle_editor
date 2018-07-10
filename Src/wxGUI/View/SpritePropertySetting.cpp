#include "SpritePropertySetting.h"
#include "PropertySettingPanel.h"

#include "Dataset/ISprite.h"
#include "View/EditPanel.h"

using namespace wxgui;

SpritePropertySetting::SpritePropertySetting(EditPanel* editPanel, ISprite* sprite)
	: IPropertySetting(editPanel, wxT("ISprite"))
	, m_sprite(sprite)
{
}

void SpritePropertySetting::updatePanel(PropertySettingPanel* panel)
{
	wxPropertyGrid* pg = panel->getPG();

	if (getPGType(pg) == m_type)
	{
 		pg->GetProperty(wxT("X"))->SetValue(m_sprite->getPosition().x);
 		pg->GetProperty(wxT("Y"))->SetValue(m_sprite->getPosition().y);
 		pg->GetProperty(wxT("�Ƕ�"))->SetValue(m_sprite->getAngle());
 		pg->GetProperty(wxT("����"))->SetValue(m_sprite->getScale());
 
 		bool xMirror, yMirror;
 		m_sprite->getMirror(xMirror, yMirror);
 		pg->GetProperty(wxT("ˮƽ����"))->SetValue(xMirror);
 		pg->GetProperty(wxT("��ֱ����"))->SetValue(yMirror);
	}
	else
	{
		pg->Clear();

		pg->Append(new wxStringProperty(wxT("����"), wxPG_LABEL, m_type));

		pg->Append(new wxFloatProperty(wxT("X"), wxPG_LABEL, m_sprite->getPosition().x));
		pg->SetPropertyAttribute(wxT("X"), wxPG_ATTR_UNITS, wxT("����"));
		pg->SetPropertyAttribute(wxT("X"), "Precision", 1);

		pg->Append(new wxFloatProperty(wxT("Y"), wxPG_LABEL, m_sprite->getPosition().y));
		pg->SetPropertyAttribute(wxT("Y"), wxPG_ATTR_UNITS, wxT("����"));
		pg->SetPropertyAttribute(wxT("Y"), "Precision", 1);

		pg->Append(new wxFloatProperty(wxT("�Ƕ�"), wxPG_LABEL, m_sprite->getAngle()));
		pg->SetPropertyAttribute(wxT("�Ƕ�"), wxPG_ATTR_UNITS, wxT("����"));
		pg->SetPropertyAttribute(wxT("�Ƕ�"), "Precision", 2);

		pg->Append(new wxFloatProperty(wxT("����"), wxPG_LABEL, m_sprite->getScale()));
		pg->SetPropertyAttribute(wxT("����"), wxPG_ATTR_UNITS, wxT("��"));
		pg->SetPropertyAttribute(wxT("����"), "Precision", 2);

		bool xMirror, yMirror;
		m_sprite->getMirror(xMirror, yMirror);
		pg->Append(new wxBoolProperty(wxT("ˮƽ����"), wxPG_LABEL, xMirror));
		pg->Append(new wxBoolProperty(wxT("��ֱ����"), wxPG_LABEL, yMirror));
	}
}

void SpritePropertySetting::onPropertyGridChange(const wxString& name, const wxAny& value)
{
	if (value.IsNull())
		return;

	if (name == wxT("X"))
		m_sprite->setTransform(f2Vec2(wxANY_AS(value, float), m_sprite->getPosition().y), m_sprite->getAngle());
	else if (name == wxT("Y"))
		m_sprite->setTransform(f2Vec2(m_sprite->getPosition().x, wxANY_AS(value, float)), m_sprite->getAngle());
	else if (name == wxT("�Ƕ�"))
		m_sprite->setTransform(m_sprite->getPosition(), wxANY_AS(value, float));
	else if (name == wxT("����"))
		m_sprite->setScale(wxANY_AS(value, float));
	else if (name == wxT("ˮƽ����"))
	{
		bool xMirror, yMirror;
		m_sprite->getMirror(xMirror, yMirror);
		m_sprite->setMirror(wxANY_AS(value, bool), yMirror);
	}
	else if (name == wxT("��ֱ����"))
	{
		bool xMirror, yMirror;
		m_sprite->getMirror(xMirror, yMirror);
		m_sprite->setMirror(xMirror, wxANY_AS(value, bool));
	}

	m_editPanel->Refresh();
}

void SpritePropertySetting::updatePropertyGrid(PropertySettingPanel* panel)
{
	updatePanel(panel);
}

void SpritePropertySetting::enablePropertyGrid(PropertySettingPanel* panel, bool bEnable)
{
	wxPropertyGrid* pg = panel->getPG();

	if (getPGType(pg) != m_type)
	{
		pg->Clear();

		pg->Append(new wxStringProperty(wxT("����"), wxPG_LABEL, m_type));

		pg->Append(new wxFloatProperty(wxT("X"), wxPG_LABEL, m_sprite->getPosition().x));
		pg->SetPropertyAttribute(wxT("X"), wxPG_ATTR_UNITS, wxT("����"));
		pg->SetPropertyAttribute(wxT("X"), "Precision", 1);

		pg->Append(new wxFloatProperty(wxT("Y"), wxPG_LABEL, m_sprite->getPosition().y));
		pg->SetPropertyAttribute(wxT("Y"), wxPG_ATTR_UNITS, wxT("����"));
		pg->SetPropertyAttribute(wxT("Y"), "Precision", 1);

		pg->Append(new wxFloatProperty(wxT("�Ƕ�"), wxPG_LABEL, m_sprite->getAngle()));
		pg->SetPropertyAttribute(wxT("�Ƕ�"), wxPG_ATTR_UNITS, wxT("����"));
		pg->SetPropertyAttribute(wxT("�Ƕ�"), "Precision", 2);

		pg->Append(new wxFloatProperty(wxT("����"), wxPG_LABEL, m_sprite->getScale()));
		pg->SetPropertyAttribute(wxT("����"), wxPG_ATTR_UNITS, wxT("��"));
		pg->SetPropertyAttribute(wxT("����"), "Precision", 2);

		bool xMirror, yMirror;
		m_sprite->getMirror(xMirror, yMirror);
		pg->Append(new wxBoolProperty(wxT("ˮƽ����"), wxPG_LABEL, xMirror));
		pg->Append(new wxBoolProperty(wxT("��ֱ����"), wxPG_LABEL, yMirror));
	}

	pg->GetProperty(wxT("����"))->Enable(bEnable);
	pg->GetProperty(wxT("X"))->Enable(bEnable);
	pg->GetProperty(wxT("Y"))->Enable(bEnable);
	pg->GetProperty(wxT("�Ƕ�"))->Enable(bEnable);
	pg->GetProperty(wxT("����"))->Enable(bEnable);
	pg->GetProperty(wxT("ˮƽ����"))->Enable(bEnable);
	pg->GetProperty(wxT("��ֱ����"))->Enable(bEnable);
}
