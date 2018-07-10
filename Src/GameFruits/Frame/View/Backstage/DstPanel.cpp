#include "DstPanel.h"
#include "ProjectPage.h"
#include "ScenePage.h"
#include "ObjectPage.h"
#include "BackstagePanel.h"
#include "Dataset/Object.h"
#include "Dataset/Scene.h"
#include "Dataset/DataConnection.h"

using namespace GAME_FRUITS;
using namespace GAME_FRUITS::VIEW::BACKSTAGE;

DstPanel::DstPanel(wxWindow* parent)
	: wxNotebook(parent, wxID_ANY)
{
	AddPage(new ProjectPage(this), DataConnection::m_game.m_name);
	AddPage(new ScenePage(this, DataConnection::m_currScene), DataConnection::m_currScene->getName());
}

void DstPanel::setScenePage(Scene* scene)
{
	assert(GetPageCount() >= 2);

	if (GetPageCount() == 3)
		RemovePage(2);

	ScenePage* page = dynamic_cast<ScenePage*>(GetPage(1));
	assert(page);
	page->initData(scene);
	SetPageText(1, scene->getName());
	SetSelection(1);
}

void DstPanel::setObjectPage(Object* object)
{
	if (object && DataConnection::m_currScene != object->getScene())
	{
		DataConnection::m_currScene = object->getScene();
		setScenePage(DataConnection::m_currScene);
	}

	if (GetPageCount() == 3 && object == DataConnection::m_currObject)
	{
		dynamic_cast<ObjectPage*>(GetPage(2))->initData(object, false);
		SetPageText(2, object->getName());
	}
	else
	{
		if (GetPageCount() == 3) RemovePage(2);
		AddPage(object->createTabPage(this), object->getName());
	}

	SetSelection(2);
}