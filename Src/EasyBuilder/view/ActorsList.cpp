#include "ActorsList.h"
#include "ActorsPage.h"
#include "ActorItem.h"
#include "PropertySettingPanel.h"
#include "StagePanel.h"
#include "ActorPropertySetting.h"
#include "Context.h"

#include "dataset/Actor.h"
#include "output/DesignerPage.h"

using namespace ebuilder;

ActorsList::ActorsList(wxWindow* parent)
	: wxgui::LibraryList(parent)
{
}

void ActorsList::loadFromTextFile(std::ifstream& fin)
{
}

void ActorsList::storeToTextFile(std::ofstream& fout) const
{
}

void ActorsList::onListSelected(wxCommandEvent& event)
{
	if (m_items.empty()) return;

	// property panel
	ActorItem* item = static_cast<ActorItem*>(m_items[event.GetInt()]);
	wxgui::IPropertySetting* setting 
		= new ActorPropertySetting(item->getActor(), this);
	Context::Instance()->property->setPropertySetting(setting);

	// stage panel
	StagePanel* stage = Context::Instance()->stage;
	wxgui::SpriteSelection* selection = stage->getDesignerPage()->getSpriteSelection();
	selection->clear();
	selection->insert(item->getActor());
	stage->getDesignerPage()->Refresh();
}
