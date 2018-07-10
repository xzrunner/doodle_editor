#include "Level1Scene.h"
#include "MainScene.h"
#include "PlayScene.h"

using namespace motox;

Level1Scene::Level1Scene(d2d::Game* game, d2d::Context* pContext)
	: d2d::Scene(game, pContext)
{
}

void Level1Scene::load()
{
	d2d::GraphicsSprite* bg = loadSprite("ui_13.png");
	bg->setTransform(d2d::Vector(400.0f ,240.0f), 0.00f);
	m_backgrounds.push_back(new d2d::Actor(bg));
	
	d2d::GraphicsSprite* actor1 = loadSprite("ui_02.png");
	actor1->setTransform(d2d::Vector(400.0f ,240.0f), 0.00f);
	m_foregrounds.push_back(new d2d::Actor(actor1));

	d2d::GraphicsSprite* actor2 = loadSprite("ui_05.png");
	actor2->setTransform(d2d::Vector(727.5f ,408.0f), 0.00f);
	d2d::Button* btn_actor2 = new d2d::Button(actor2);
	btn_actor2->addBehavior(new d2d::ScaleSize(actor2, 1.0f), false);
	btn_actor2->addBehavior(new d2d::ScaleSize(actor2, 1.1f), true);
	btn_actor2->addBehavior(new d2d::ChangeScene(m_game, new MainScene(m_game, m_pContext)), true);
	m_foregrounds.push_back(btn_actor2);
	
	{
		d2d::GraphicsSprite* level4 = loadSprite("ui_04.png");
		level4->setTransform(d2d::Vector(224.8f ,229.8f), 0.00f);
		d2d::Button* btn_level4 = new d2d::Button(level4);

		d2d::Scene* nextScene = new PlayScene(m_game, m_pContext, 1, 6);
		nextScene->setParent(new Level1Scene(m_game, m_pContext));
		btn_level4->addBehavior(new d2d::ChangeScene(m_game, nextScene), false);

		m_foregrounds.push_back(btn_level4);
	}
	{
		d2d::GraphicsSprite* level5 = loadSprite("ui_04.png");
		level5->setTransform(d2d::Vector(322.5f ,253.8f), 0.00f);
		d2d::Button* btn_level5 = new d2d::Button(level5);

		d2d::Scene* nextScene = new PlayScene(m_game, m_pContext, 1, 2);
		nextScene->setParent(new Level1Scene(m_game, m_pContext));
		btn_level5->addBehavior(new d2d::ChangeScene(m_game, nextScene), false);

		m_foregrounds.push_back(btn_level5);
	}
	{
		d2d::GraphicsSprite* level6 = loadSprite("ui_04.png");
		level6->setTransform(d2d::Vector(468.3f ,220.8f), 0.00f);
		d2d::Button* btn_level6 = new d2d::Button(level6);

		d2d::Scene* nextScene = new PlayScene(m_game, m_pContext, 1, 7);
		nextScene->setParent(new Level1Scene(m_game, m_pContext));
		btn_level6->addBehavior(new d2d::ChangeScene(m_game, nextScene), false);

		m_foregrounds.push_back(btn_level6);
	}	
	{
		d2d::GraphicsSprite* level3 = loadSprite("ui_04.png");
		level3->setTransform(d2d::Vector(377.3f ,182.7f), 0.00f);
		d2d::Button* btn_level3 = new d2d::Button(level3);

		d2d::Scene* nextScene = new PlayScene(m_game, m_pContext, 1, 3);
		nextScene->setParent(new Level1Scene(m_game, m_pContext));
		btn_level3->addBehavior(new d2d::ChangeScene(m_game, nextScene), false);

		m_foregrounds.push_back(btn_level3);
	}
	{
		d2d::GraphicsSprite* level2 = loadSprite("ui_04.png");
		level2->setTransform(d2d::Vector(280.1f ,139.0f), 0.00f);
		d2d::Button* btn_level2 = new d2d::Button(level2);

		d2d::Scene* nextScene = new PlayScene(m_game, m_pContext, 1, 4);
		nextScene->setParent(new Level1Scene(m_game, m_pContext));
		btn_level2->addBehavior(new d2d::ChangeScene(m_game, nextScene), false);

		m_foregrounds.push_back(btn_level2);
	}
	{
		d2d::GraphicsSprite* level1 = loadSprite("ui_04.png");
		level1->setTransform(d2d::Vector(135.9f ,129.9f), 0.00f);
		d2d::Button* btn_level1 = new d2d::Button(level1);

		d2d::Scene* nextScene = new PlayScene(m_game, m_pContext, 1, 5);
		nextScene->setParent(new Level1Scene(m_game, m_pContext));
		btn_level1->addBehavior(new d2d::ChangeScene(m_game, nextScene), false);

		m_foregrounds.push_back(btn_level1);
	}
	{
		d2d::GraphicsSprite* level7 = loadSprite("ui_04.png");
		level7->setTransform(d2d::Vector(533.1f ,286.3f), 0.00f);
		d2d::Button* btn_level7 = new d2d::Button(level7);

		d2d::Scene* nextScene = new PlayScene(m_game, m_pContext, 1, 1);
		nextScene->setParent(new Level1Scene(m_game, m_pContext));
		btn_level7->addBehavior(new d2d::ChangeScene(m_game, nextScene), false);

		m_foregrounds.push_back(btn_level7);
	}
	{
		d2d::GraphicsSprite* level8 = loadSprite("ui_04.png");
		level8->setTransform(d2d::Vector(614.5f ,314.4f), 0.00f);
		d2d::Button* btn_level8 = new d2d::Button(level8);

		d2d::Scene* nextScene = new PlayScene(m_game, m_pContext, 1, 8);
		nextScene->setParent(new Level1Scene(m_game, m_pContext));
		btn_level8->addBehavior(new d2d::ChangeScene(m_game, nextScene), false);

		m_foregrounds.push_back(btn_level8);
	}

// 	d2d::GraphicsSprite* actor32 = loadSprite("ui_14.png");
// 	actor32->setTransform(d2d::Vector(765.0f ,240.0f), 0.00f);
// 	d2d::Button* btn_actor32 = new d2d::Button(actor32);
// 	btn_actor32->addBehavior(new d2d::ChangeScene(m_game, new Level2Scene(m_game, m_pContext)), false);
// 	btn_actor32->addBehavior(new d2d::ScaleSize(actor32, 1.0f), false);
// 	btn_actor32->addBehavior(new d2d::ScaleSize(actor32, 1.1f), true);
// 	m_buttons.push_back(btn_actor32);
// 
// 	d2d::GraphicsSprite* actor33 = loadSprite("ui_14.png");
// 	actor33->setTransform(d2d::Vector(37.0f ,240.0f), 0.00f);
// 	d2d::Button* btn_actor33 = new d2d::Button(actor33);
// 	btn_actor33->addBehavior(new d2d::ChangeScene(m_game, new Level5Scene(m_game, m_pContext)), false);
// 	btn_actor33->addBehavior(new d2d::ScaleSize(actor33, 1.0f), false);
// 	btn_actor33->addBehavior(new d2d::ScaleSize(actor33, 1.1f), true);
// 	m_buttons.push_back(btn_actor33);
}
