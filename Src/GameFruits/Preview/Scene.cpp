#include "Scene.h"
#include "Sprite.h"
#include "Button.h"
#include "Dataset/Object.h"
#include "Dataset/Scene.h"
#include "Frame/Regulars/MousePress.h"
#include "Frame/Regulars/ChangeScene.h"
#include "Frame/Regulars/ScaleSize.h"
#include "Frame/Regulars/ChangeImage.h"

using namespace GAME_FRUITS::PREVIEW;

Scene::Scene(MainDialog* main, GAME_FRUITS::Scene* src)
{
	m_main = main;
	loadFromEditor(src);
}

Scene::~Scene()
{
}

void Scene::onPaint(wxDC& dc) const
{
   	dc.SetBackground(wxBrush(m_bgColor));	
   	dc.Clear();

	for (size_t i = 0, n = m_tiles.size(); i < n; ++i)
		m_tiles[i]->onPaint(dc);

	for (size_t i = 0, n = m_buttons.size(); i < n; ++i)
		m_buttons[i]->onPaint(dc);
}

void Scene::onMouseDown(int x, int y)
{
	for (size_t i = 0, n = m_buttons.size(); i < n; ++i)
		m_buttons[i]->onMouseDown(x, y);
}

void Scene::onMouseUp(int x, int y)
{
	for (size_t i = 0, n = m_buttons.size(); i < n; ++i)
		m_buttons[i]->onMouseUp(x, y);
}

void Scene::loadFromEditor(GAME_FRUITS::Scene* src)
{
	m_bgColor = src->getColor();
	const std::vector<Object*>& objects = src->getAllObjects();
	for (size_t i = 0, n = objects.size(); i < n; ++i)
		loadObject(objects[i]);
}

void Scene::loadObject(GAME_FRUITS::Object* obj)
{
	bool isButton = false;

	const std::vector<RegularListItem*>& regulars = obj->getAllRegulars();
	for (size_t i = 0, n = regulars.size(); i < n; ++i)
	{
		REGULAR::MousePress* mousePress = dynamic_cast<REGULAR::MousePress*>(regulars[i]);
		if (mousePress) 
		{
			isButton = true;
			break;
		}
	}

	if (isButton) loadButtonObject(obj);
	else loadTileObject(obj);
}

void Scene::loadTileObject(GAME_FRUITS::Object* obj)
{
	int x, y;
	obj->getPosition(x, y);
	m_tiles.push_back(new Sprite(obj->getBitmap(), x + 400, y + 240));
}

void Scene::loadButtonObject(GAME_FRUITS::Object* obj)
{
	int x, y;
	obj->getPosition(x, y);
	Button* button = new Button(m_main, obj->getBitmap(), x + 400, y + 240);

	const std::vector<RegularListItem*>& regulars = obj->getAllRegulars();
	for (size_t i = 0, n = regulars.size(); i < n; ++i)
	{
		REGULAR::MousePress* mousePress = dynamic_cast<REGULAR::MousePress*>(regulars[i]);
		if (mousePress) loadButtonObject(button, mousePress);
	}

	m_buttons.push_back(button);
}

void Scene::loadButtonObject(Button* button, GAME_FRUITS::REGULAR::MousePress* press)
{
	const std::vector<RegularListItem*>& regulars = press->getAllRegulars(true);
	for (size_t i = 0, n = regulars.size(); i < n; ++i)
	{
		REGULAR::ChangeScene* changeScene = dynamic_cast<REGULAR::ChangeScene*>(regulars[i]);
		if (changeScene) button->addChangeSceneAction(press->isDownChange(), changeScene->getSelectedScene());

		REGULAR::ScaleSize* scaleSize = dynamic_cast<REGULAR::ScaleSize*>(regulars[i]);
		if (scaleSize) button->addScaleSizeAction(press->isDownChange(), scaleSize->getScaleValue());

		REGULAR::ChangeImage* changeImage = dynamic_cast<REGULAR::ChangeImage*>(regulars[i]);
		if (changeImage) button->addChangeImageAction(press->isDownChange(), changeImage->getImagePath());
	}
}
