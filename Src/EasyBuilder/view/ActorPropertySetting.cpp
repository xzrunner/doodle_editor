#include "ActorPropertySetting.h"

#include "dataset/Actor.h"
#include "view/Context.h"
#include "view/ActorItem.h"
#include "view/ActorsPage.h"
#include "view/StagePanel.h"
#include "output/DesignerPage.h"

using namespace ebuilder;

ActorPropertySetting::ActorPropertySetting(Actor* actor, 
										   wxgui::LibraryList* actorList)
	: IPropertySetting(Context::Instance()->stage->getDesignerPage(), wxT("Actor"))
	, m_actor(actor)
	, m_actorList(actorList)
{
}

void ActorPropertySetting::updatePanel(wxgui::PropertySettingPanel* panel)
{
	wxPropertyGrid* pg = panel->getPG();

	if (getPGType(pg) == m_type)
	{
		pg->GetProperty(wxT("����"))->SetValue(m_actor->m_name);
		pg->GetProperty(wxT("tag"))->SetValue(m_actor->m_tag);
		pg->GetProperty(wxT("X"))->SetValue(m_actor->getPosition().x);
		pg->GetProperty(wxT("Y"))->SetValue(m_actor->getPosition().y);
		pg->GetProperty(wxT("�Ƕ�"))->SetValue(m_actor->getAngle());
		pg->GetProperty(wxT("����"))->SetValue(m_actor->getScale());

		bool xMirror, yMirror;
		m_actor->getMirror(xMirror, yMirror);
		pg->GetProperty(wxT("ˮƽ����"))->SetValue(xMirror);
		pg->GetProperty(wxT("��ֱ����"))->SetValue(yMirror);

		pg->GetProperty(wxT("��Ϊ����"))->SetValue(m_actor->m_isBg);
	}
	else
	{
		pg->Clear();

		pg->Append(new wxStringProperty(wxT("����"), wxPG_LABEL, m_type));

		pg->Append(new wxStringProperty(wxT("����"), wxPG_LABEL, m_actor->m_name));

		pg->Append(new wxStringProperty(wxT("tag"), wxPG_LABEL, m_actor->m_tag));

		pg->Append(new wxFloatProperty(wxT("X"), wxPG_LABEL, m_actor->getPosition().x));
		pg->SetPropertyAttribute(wxT("X"), wxPG_ATTR_UNITS, wxT("pixels"));
		pg->SetPropertyAttribute(wxT("X"), "Precision", 1);

		pg->Append(new wxFloatProperty(wxT("Y"), wxPG_LABEL, m_actor->getPosition().y));
		pg->SetPropertyAttribute(wxT("Y"), wxPG_ATTR_UNITS, wxT("pixels"));
		pg->SetPropertyAttribute(wxT("Y"), "Precision", 1);

		pg->Append(new wxFloatProperty(wxT("�Ƕ�"), wxPG_LABEL, m_actor->getAngle()));
		pg->SetPropertyAttribute(wxT("�Ƕ�"), wxPG_ATTR_UNITS, wxT("rad"));
		pg->SetPropertyAttribute(wxT("�Ƕ�"), "Precision", 2);

		pg->Append(new wxFloatProperty(wxT("����"), wxPG_LABEL, m_actor->getScale()));
		pg->SetPropertyAttribute(wxT("����"), wxPG_ATTR_UNITS, wxT("multiple"));
		pg->SetPropertyAttribute(wxT("����"), "Precision", 2);

		bool xMirror, yMirror;
		m_actor->getMirror(xMirror, yMirror);
		pg->Append(new wxBoolProperty(wxT("ˮƽ����"), wxPG_LABEL, xMirror));
		pg->Append(new wxBoolProperty(wxT("��ֱ����"), wxPG_LABEL, yMirror));

		pg->Append(new wxBoolProperty(wxT("��Ϊ����"), wxPG_LABEL, m_actor->m_isBg));
	}
}

void ActorPropertySetting::onPropertyGridChange(const wxString& name, const wxAny& value)
{
	if (value.IsNull())
		return;

	if (name == wxT("����"))
		updateActorName(wxANY_AS(value, wxString));
	else if (name == wxT("tag"))
		m_actor->m_tag = wxANY_AS(value, wxString);
	else if (name == wxT("X"))
		m_actor->setTransform(f2Vec2(wxANY_AS(value, float), m_actor->getPosition().y), m_actor->getAngle());
	else if (name == wxT("Y"))
		m_actor->setTransform(f2Vec2(m_actor->getPosition().x, wxANY_AS(value, float)), m_actor->getAngle());
	else if (name == wxT("�Ƕ�"))
		m_actor->setTransform(m_actor->getPosition(), wxANY_AS(value, float));
	else if (name == wxT("����"))
		m_actor->setScale(wxANY_AS(value, float));
	else if (name == wxT("ˮƽ����"))
	{
		bool xMirror, yMirror;
		m_actor->getMirror(xMirror, yMirror);
		m_actor->setMirror(wxANY_AS(value, bool), yMirror);
	}
	else if (name == wxT("��ֱ����"))
	{
		bool xMirror, yMirror;
		m_actor->getMirror(xMirror, yMirror);
		m_actor->setMirror(xMirror, wxANY_AS(value, bool));
	}
	else if (name == wxT("��Ϊ����"))
		m_actor->m_isBg = wxANY_AS(value, bool);

	m_editPanel->Refresh();
}

void ActorPropertySetting::updatePropertyGrid(wxgui::PropertySettingPanel* panel)
{
	updatePanel(panel);
}

void ActorPropertySetting::enablePropertyGrid(wxgui::PropertySettingPanel* panel, bool bEnable)
{
	wxPropertyGrid* pg = panel->getPG();

	if (getPGType(pg) != m_type)
	{
		pg->Clear();

		pg->Append(new wxStringProperty(wxT("����"), wxPG_LABEL, m_type));

		pg->Append(new wxStringProperty(wxT("����"), wxPG_LABEL, m_actor->m_name));

		pg->Append(new wxStringProperty(wxT("tag"), wxPG_LABEL, m_actor->m_tag));

		pg->Append(new wxFloatProperty(wxT("X"), wxPG_LABEL, m_actor->getPosition().x));
		pg->SetPropertyAttribute(wxT("X"), wxPG_ATTR_UNITS, wxT("pixels"));
		pg->SetPropertyAttribute(wxT("X"), "Precision", 1);

		pg->Append(new wxFloatProperty(wxT("Y"), wxPG_LABEL, m_actor->getPosition().y));
		pg->SetPropertyAttribute(wxT("Y"), wxPG_ATTR_UNITS, wxT("pixels"));
		pg->SetPropertyAttribute(wxT("Y"), "Precision", 1);

		pg->Append(new wxFloatProperty(wxT("�Ƕ�"), wxPG_LABEL, m_actor->getAngle()));
		pg->SetPropertyAttribute(wxT("�Ƕ�"), wxPG_ATTR_UNITS, wxT("rad"));
		pg->SetPropertyAttribute(wxT("�Ƕ�"), "Precision", 2);

		pg->Append(new wxFloatProperty(wxT("����"), wxPG_LABEL, m_actor->getScale()));
		pg->SetPropertyAttribute(wxT("����"), wxPG_ATTR_UNITS, wxT("multiple"));
		pg->SetPropertyAttribute(wxT("����"), "Precision", 2);

		bool xMirror, yMirror;
		m_actor->getMirror(xMirror, yMirror);
		pg->Append(new wxBoolProperty(wxT("ˮƽ����"), wxPG_LABEL, xMirror));
		pg->Append(new wxBoolProperty(wxT("��ֱ����"), wxPG_LABEL, yMirror));

		pg->Append(new wxBoolProperty(wxT("��Ϊ����"), wxPG_LABEL, m_actor->m_isBg));
	}

	pg->GetProperty(wxT("����"))->Enable(bEnable);
	pg->GetProperty(wxT("����"))->Enable(bEnable);
	pg->GetProperty(wxT("tag"))->Enable(bEnable);
	pg->GetProperty(wxT("X"))->Enable(bEnable);
	pg->GetProperty(wxT("Y"))->Enable(bEnable);
	pg->GetProperty(wxT("�Ƕ�"))->Enable(bEnable);
	pg->GetProperty(wxT("����"))->Enable(bEnable);
	pg->GetProperty(wxT("ˮƽ����"))->Enable(bEnable);
	pg->GetProperty(wxT("��ֱ����"))->Enable(bEnable);
	pg->GetProperty(wxT("��Ϊ����"))->Enable(bEnable);
}

void ActorPropertySetting::updateActorName(const wxString& name)
{
	m_actor->m_name = name;
	m_actorList->traverse(UpdateNameVisitor(m_actor));
	Context::Instance()->stage->getDesignerPage()->updateCodePage();
	m_actorList->Refresh();
}

//////////////////////////////////////////////////////////////////////////
// class ActorPropertySetting::UpdateNameVisitor
//////////////////////////////////////////////////////////////////////////

void ActorPropertySetting::UpdateNameVisitor::
visit(IObject* object, bool& bFetchNext)
{
	ActorItem* item = static_cast<ActorItem*>(object);
	if (item->getActor() == m_actor)
	{
		item->setName(m_actor->m_name);
		bFetchNext = false;
	}
	else
	{
		bFetchNext = true;
	}
}