#include "Scene.h"
#include "Actor.h"

using namespace ebuilder;

Scene::Scene()
{
	static int count = 0;
	m_name = wxString("scene") + wxString::FromDouble(count++);

	m_color = *wxWHITE;
}

Scene::~Scene()
{
	for_each(m_actors.begin(), m_actors.end(), DeletePointerFunctor<Actor>());
}

void Scene::insertActor(Actor* actor) 
{
	m_actors.push_back(actor);
}
void Scene::removeActor(Actor* actor)
{
	for (size_t i = 0, n = m_actors.size(); i < n; ++i)
	{
		if (m_actors[i] == actor)
		{
			m_actors[i]->release();
			m_actors.erase(m_actors.begin() + i);
			break;
		}
	}
}

void Scene::clear()
{
	for (size_t i = 0, n = m_actors.size(); i < n; ++i)
		m_actors[i]->release();
	m_actors.clear();
}