#include "ChangeScene.h"
#include "Game.h"
#include "Scene.h"

using namespace d2d;

ChangeScene::ChangeScene(Game* game, Scene* scene)
	: m_game(game)
	, m_scene(scene)
{
}

void ChangeScene::trigger()
{
	m_scene->load();
	m_game->setScene(m_scene);
}