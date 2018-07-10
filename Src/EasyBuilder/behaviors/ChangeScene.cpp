#include "ChangeScene.h"

#include "view/ScenesPage.h"
#include "view/ListObserver.h"

using namespace ebuilder;

ChangeScene::ChangeScene(Actor* actor, wxgui::LibraryList* sceneList) 
	: Behavior(e_ChangeScene, actor, INT_MAX)
	, m_scenePage(NULL)
{
	selected = sceneList->getSymbol(0);
}

ChangeScene::~ChangeScene() 
{
	if (m_scenePage)
		m_scenePage->getListObserver()->removeListener(this);
}

void ChangeScene::update(const wxgui::LibraryList& list) 
{
	if (!isSymbolInList(selected, list))
		selected = list.getSymbol(0);
}

void ChangeScene::registerListener(ScenesPage* scenePage) 
{
	m_scenePage = scenePage;
	scenePage->getListObserver()->registerListener(this);
}

