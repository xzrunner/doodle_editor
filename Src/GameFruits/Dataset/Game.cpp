#include "Game.h"
#include "Scene.h"

using namespace GAME_FRUITS;

Game::Game()
{
	m_name = wxT("My Game");

	m_width = 800;
	m_height = 480;

	Scene* scene = new Scene(m_width, m_height);
	m_scenes.push_back(scene);
}

Game::~Game()
{
	for_each(m_scenes.begin(), m_scenes.end(), DeletePointerFunctor<Scene>());
}

Scene* Game::queryScene(const wxString& name) const
{
	for (size_t i = 0, n = m_scenes.size(); i < n; ++i)
	{
		Scene* scene = m_scenes[i];
		if (scene->getName() == name) return scene;
	}
	return NULL;
}

void Game::deleteScene(const wxString& name)
{
	for (size_t i = 0, n = m_scenes.size(); i < n; ++i)
	{
		Scene* scene = m_scenes[i];
		if (scene->getName() == name)
		{
			m_scenes.erase(m_scenes.begin() + i);
			delete scene;
			break;
		}
	}
}