#include "ScenePropertySetting.h"
#include "Context.h"
#include "StagePanel.h"
#include "SceneItem.h"
#include "ScenesPage.h"
#include "ListObserver.h"

#include "output/DesignerPage.h"
#include "dataset/Scene.h"

#include <wx/propgrid/advprops.h>

using namespace ebuilder;

ScenePropertySetting::ScenePropertySetting(SceneItem* scene, ScenesPage* scenesPage)
	: IPropertySetting(Context::Instance()->stage->getDesignerPage(), wxT("Scene"))
	, m_scene(scene)
	, m_scenesPage(scenesPage)
{
}

void ScenePropertySetting::updatePanel(wxgui::PropertySettingPanel* panel)
{
	wxPropertyGrid* pg = panel->getPG();

	if (getPGType(pg) == m_type)
	{
		pg->GetProperty(wxT("名称"))->SetValue(m_scene->getName());

		pg->GetProperty(wxT("tag"))->SetValue(m_scene->getScene()->m_tag);

		wxString str = m_scene->getScene()->m_color.GetAsString(wxC2S_HTML_SYNTAX);
		pg->GetProperty(wxT("背景色"))->SetValueFromString(str);
	}
	else
	{
		pg->Clear();

		pg->Append(new wxStringProperty(wxT("类型"), wxPG_LABEL, m_type));

		pg->Append(new wxStringProperty(wxT("名称"), wxPG_LABEL, m_scene->getName()));

		pg->Append(new wxStringProperty(wxT("tag"), wxPG_LABEL, m_scene->getScene()->m_tag));

		pg->Append(new wxColourProperty(wxT("背景色"), wxPG_LABEL, *wxWHITE));
	}
}

void ScenePropertySetting::onPropertyGridChange(const wxString& name, const wxAny& value)
{
	if (value.IsNull())
		return;

	if (name == wxT("名称"))
		updateSceneName(wxANY_AS(value, wxString));
	else if (name == wxT("tag"))
		m_scene->getScene()->m_tag = wxANY_AS(value, wxString);
	else if (name == wxT("背景色"))
		m_scene->getScene()->m_color = (wxANY_AS(value, wxColour));
}

void ScenePropertySetting::updatePropertyGrid(wxgui::PropertySettingPanel* panel)
{
	updatePanel(panel);
}

void ScenePropertySetting::enablePropertyGrid(wxgui::PropertySettingPanel* panel, bool bEnable)
{
}

void ScenePropertySetting::updateSceneName(const wxString& name)
{
	m_scene->setName(name);
	m_scenesPage->traverse(UpdateNameVisitor(m_scene));
	m_scenesPage->getListObserver()->updateListeners();
	Context::Instance()->stage->updateCodePages(m_scene);
	m_scenesPage->Refresh();
}

//////////////////////////////////////////////////////////////////////////
// class ScenePropertySetting::UpdateNameVisitor
//////////////////////////////////////////////////////////////////////////

void ScenePropertySetting::UpdateNameVisitor::
visit(IObject* object, bool& bFetchNext)
{
	SceneItem* item = static_cast<SceneItem*>(object);
	if (item == m_scene)
	{
		item->setName(m_scene->getName());
		bFetchNext = false;
	}
	else
	{
		bFetchNext = true;
	}
}