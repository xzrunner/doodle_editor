#include "Game.h"
#include "Scene.h"

using namespace d2d;

Game::Game()
	: m_scene(NULL)
{
}

void Game::setScene(Scene* scene)
{
	if (m_scene != scene)
	{
		delete m_scene;
		m_scene = scene;
	}
}

Scene* Game::getScene()
{
	return m_scene;
}

void Game::load()
{
	if (m_scene) m_scene->load();
}

void Game::draw() const
{
	if (m_scene) m_scene->draw();
}

void Game::update()
{
	if (m_scene) m_scene->update();
}

bool Game::isAlive() const 
{
	return m_scene != NULL;
}