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
		pg->GetProperty(wxT("名称"))->SetValue(m_actor->m_name);
		pg->GetProperty(wxT("tag"))->SetValue(m_actor->m_tag);
		pg->GetProperty(wxT("X"))->SetValue(m_actor->getPosition().x);
		pg->GetProperty(wxT("Y"))->SetValue(m_actor->getPosition().y);
		pg->GetProperty(wxT("角度"))->SetValue(m_actor->getAngle());
		pg->GetProperty(wxT("缩放"))->SetValue(m_actor->getScale());

		bool xMirror, yMirror;
		m_actor->getMirror(xMirror, yMirror);
		pg->GetProperty(wxT("水平镜像"))->SetValue(xMirror);
		pg->GetProperty(wxT("竖直镜像"))->SetValue(yMirror);

		pg->GetProperty(wxT("做为背景"))->SetValue(m_actor->m_isBg);
	}
	else
	{
		pg->Clear();

		pg->Append(new wxStringProperty(wxT("类型"), wxPG_LABEL, m_type));

		pg->Append(new wxStringProperty(wxT("名称"), wxPG_LABEL, m_actor->m_name));

		pg->Append(new wxStringProperty(wxT("tag"), wxPG_LABEL, m_actor->m_tag));

		pg->Append(new wxFloatProperty(wxT("X"), wxPG_LABEL, m_actor->getPosition().x));
		pg->SetPropertyAttribute(wxT("X"), wxPG_ATTR_UNITS, wxT("pixels"));
		pg->SetPropertyAttribute(wxT("X"), "Precision", 1);

		pg->Append(new wxFloatProperty(wxT("Y"), wxPG_LABEL, m_actor->getPosition().y));
		pg->SetPropertyAttribute(wxT("Y"), wxPG_ATTR_UNITS, wxT("pixels"));
		pg->SetPropertyAttribute(wxT("Y"), "Precision", 1);

		pg->Append(new wxFloatProperty(wxT("角度"), wxPG_LABEL, m_actor->getAngle()));
		pg->SetPropertyAttribute(wxT("角度"), wxPG_ATTR_UNITS, wxT("rad"));
		pg->SetPropertyAttribute(wxT("角度"), "Precision", 2);

		pg->Append(new wxFloatProperty(wxT("缩放"), wxPG_LABEL, m_actor->getScale()));
		pg->SetPropertyAttribute(wxT("缩放"), wxPG_ATTR_UNITS, wxT("multiple"));
		pg->SetPropertyAttribute(wxT("缩放"), "Precision", 2);

		bool xMirror, yMirror;
		m_actor->getMirror(xMirror, yMirror);
		pg->Append(new wxBoolProperty(wxT("水平镜像"), wxPG_LABEL, xMirror));
		pg->Append(new wxBoolProperty(wxT("竖直镜像"), wxPG_LABEL, yMirror));

		pg->Append(new wxBoolProperty(wxT("做为背景"), wxPG_LABEL, m_actor->m_isBg));
	}
}

void ActorPropertySetting::onPropertyGridChange(const wxString& name, const wxAny& value)
{
	if (value.IsNull())
		return;

	if (name == wxT("名称"))
		updateActorName(wxANY_AS(value, wxString));
	else if (name == wxT("tag"))
		m_actor->m_tag = wxANY_AS(value, wxString);
	else if (name == wxT("X"))
		m_actor->setTransform(f2Vec2(wxANY_AS(value, float), m_actor->getPosition().y), m_actor->getAngle());
	else if (name == wxT("Y"))
		m_actor->setTransform(f2Vec2(m_actor->getPosition().x, wxANY_AS(value, float)), m_actor->getAngle());
	else if (name == wxT("角度"))
		m_actor->setTransform(m_actor->getPosition(), wxANY_AS(value, float));
	else if (name == wxT("缩放"))
		m_actor->setScale(wxANY_AS(value, float));
	else if (name == wxT("水平镜像"))
	{
		bool xMirror, yMirror;
		m_actor->getMirror(xMirror, yMirror);
		m_actor->setMirror(wxANY_AS(value, bool), yMirror);
	}
	else if (name == wxT("竖直镜像"))
	{
		bool xMirror, yMirror;
		m_actor->getMirror(xMirror, yMirror);
		m_actor->setMirror(xMirror, wxANY_AS(value, bool));
	}
	else if (name == wxT("做为背景"))
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

		pg->Append(new wxStringProperty(wxT("类型"), wxPG_LABEL, m_type));

		pg->Append(new wxStringProperty(wxT("名称"), wxPG_LABEL, m_actor->m_name));

		pg->Append(new wxStringProperty(wxT("tag"), wxPG_LABEL, m_actor->m_tag));

		pg->Append(new wxFloatProperty(wxT("X"), wxPG_LABEL, m_actor->getPosition().x));
		pg->SetPropertyAttribute(wxT("X"), wxPG_ATTR_UNITS, wxT("pixels"));
		pg->SetPropertyAttribute(wxT("X"), "Precision", 1);

		pg->Append(new wxFloatProperty(wxT("Y"), wxPG_LABEL, m_actor->getPosition().y));
		pg->SetPropertyAttribute(wxT("Y"), wxPG_ATTR_UNITS, wxT("pixels"));
		pg->SetPropertyAttribute(wxT("Y"), "Precision", 1);

		pg->Append(new wxFloatProperty(wxT("角度"), wxPG_LABEL, m_actor->getAngle()));
		pg->SetPropertyAttribute(wxT("角度"), wxPG_ATTR_UNITS, wxT("rad"));
		pg->SetPropertyAttribute(wxT("角度"), "Precision", 2);

		pg->Append(new wxFloatProperty(wxT("缩放"), wxPG_LABEL, m_actor->getScale()));
		pg->SetPropertyAttribute(wxT("缩放"), wxPG_ATTR_UNITS, wxT("multiple"));
		pg->SetPropertyAttribute(wxT("缩放"), "Precision", 2);

		bool xMirror, yMirror;
		m_actor->getMirror(xMirror, yMirror);
		pg->Append(new wxBoolProperty(wxT("水平镜像"), wxPG_LABEL, xMirror));
		pg->Append(new wxBoolProperty(wxT("竖直镜像"), wxPG_LABEL, yMirror));

		pg->Append(new wxBoolProperty(wxT("做为背景"), wxPG_LABEL, m_actor->m_isBg));
	}

	pg->GetProperty(wxT("类型"))->Enable(bEnable);
	pg->GetProperty(wxT("名称"))->Enable(bEnable);
	pg->GetProperty(wxT("tag"))->Enable(bEnable);
	pg->GetProperty(wxT("X"))->Enable(bEnable);
	pg->GetProperty(wxT("Y"))->Enable(bEnable);
	pg->GetProperty(wxT("角度"))->Enable(bEnable);
	pg->GetProperty(wxT("缩放"))->Enable(bEnable);
	pg->GetProperty(wxT("水平镜像"))->Enable(bEnable);
	pg->GetProperty(wxT("竖直镜像"))->Enable(bEnable);
	pg->GetProperty(wxT("做为背景"))->Enable(bEnable);
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