#include "ScenesList.h"
#include "ScenesPage.h"
#include "SceneItem.h"
#include "PropertySettingPanel.h"
#include "ScenePropertySetting.h"

#include "dataset/Scene.h"
#include "output/DesignerPage.h"
#include "view/Context.h"
#include "view/StagePanel.h"

using namespace ebuilder;

ScenesList::ScenesList(ScenesPage* scenesPage)
	: wxgui::LibraryList(scenesPage)
	, m_scenesPage(scenesPage)
{
}

void ScenesList::loadFromTextFile(std::ifstream& fin)
{
}

void ScenesList::storeToTextFile(std::ofstream& fout) const
{
}

void ScenesList::onListSelected(wxCommandEvent& event)
{
	if (m_items.empty()) return;

	Context* context = Context::Instance();

	// property panel
	SceneItem* item = static_cast<SceneItem*>(m_items[event.GetInt()]);
	wxgui::IPropertySetting* setting 
		= new ScenePropertySetting(item, m_scenesPage);
	context->property->setPropertySetting(setting);

	// stage panel
	DesignerPage* stage = context->stage->getDesignerPage();
	stage->setScene(item);
	stage->getEditOP()->clear();
	stage->Refresh();
}