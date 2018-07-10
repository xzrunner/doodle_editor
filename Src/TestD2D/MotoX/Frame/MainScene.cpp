#include "MainScene.h"
#include "Level1Scene.h"

using namespace motox;

MainScene::MainScene(d2d::Game* game, d2d::Context* pContext)
	: d2d::Scene(game, pContext)
{
}

void MainScene::load()
{
	d2d::GraphicsSprite* bg = loadSprite("ui_1_01.jpg");
	bg->setTransform(d2d::Vector(400.0f ,240.0f), 0.00f);
	m_backgrounds.push_back(new d2d::Actor(bg));

 	d2d::GraphicsSprite* actor12 = loadSprite("ui_08.png");
 	actor12->setTransform(d2d::Vector(575.5f ,59.9f), 0.00f);
 	m_foregrounds.push_back(new d2d::Actor(actor12));
 
	{
		d2d::GraphicsSprite* actor13 = loadSprite("ui_08.png");
		actor13->setTransform(d2d::Vector(620.9f ,158.2f), 0.00f);
		d2d::Button* btn_actor13 = new d2d::Button(actor13);
		btn_actor13->addBehavior(new d2d::ScaleSize(actor13, 1.0f), false);
		btn_actor13->addBehavior(new d2d::ScaleSize(actor13, 1.1f), true);
		
		d2d::Scene* nextScene = new Level1Scene(m_game, m_pContext);
		nextScene->setParent(new MainScene(m_game, m_pContext));
		btn_actor13->addBehavior(new d2d::ChangeScene(m_game, nextScene), false);

		m_foregrounds.push_back(btn_actor13);
	}
 
	{
		d2d::GraphicsSprite* actor14 = loadSprite("ui_08.png");
		actor14->setTransform(d2d::Vector(178.1f ,159.9f), -0.1f);
		d2d::Button* btn_actor14 = new d2d::Button(actor14);

		btn_actor14->addBehavior(new d2d::ScaleSize(actor14, 1.0f), false);
		btn_actor14->addBehavior(new d2d::ScaleSize(actor14, 1.1f), true);

		d2d::Scene* nextScene = new Level1Scene(m_game, m_pContext);
		nextScene->setParent(new MainScene(m_game, m_pContext));
		btn_actor14->addBehavior(new d2d::ChangeScene(m_game, nextScene), false);

		m_foregrounds.push_back(btn_actor14);
	}
 
 	d2d::GraphicsSprite* actor15 = loadSprite("ui_08.png");
 	actor15->setTransform(d2d::Vector(213.7f ,62.7f), -0.1f);
 	m_foregrounds.push_back(new d2d::Actor(actor15));
 
 	d2d::GraphicsSprite* actor16 = loadSprite("ui_07.png");
 	actor16->setTransform(d2d::Vector(681.9f ,65.4f), 0.00f);
 	actor16->setMirror(true ,false);
 	m_foregrounds.push_back(new d2d::Actor(actor16));
 
 	d2d::GraphicsSprite* actor17 = loadSprite("ui_06.png");
 	actor17->setTransform(d2d::Vector(78.3f ,163.6f), 0.00f);
 	actor17->setMirror(true ,false);
 	m_foregrounds.push_back(new d2d::Actor(actor17));
 
 	d2d::GraphicsSprite* actor18 = loadSprite("ui_07.png");
 	actor18->setTransform(d2d::Vector(100.1f ,68.1f), 0.00f);
 	m_foregrounds.push_back(new d2d::Actor(actor18));
 
 	d2d::GraphicsSprite* actor19 = loadSprite("ui_06.png");
 	actor19->setTransform(d2d::Vector(724.0f ,164.0f), 0.00f);
 	m_foregrounds.push_back(new d2d::Actor(actor19));
}
