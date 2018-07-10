#include "Scene.h"
#include "Button.h"

#include "common/tools.h"
#include "modules/graphics/GraphicsSprite.h"

using namespace d2d;

Scene::Scene(Game* game, d2d::Context* pContext)
	: m_game(game)
	, m_pContext(pContext)
	, m_parent(NULL)
{
}

Scene::~Scene()
{
	for_each(m_backgrounds.begin(), m_backgrounds.end(), DeletePointerFunctor<Item>());
	for_each(m_foregrounds.begin(), m_foregrounds.end(), DeletePointerFunctor<Item>());
}

void Scene::draw() const
{
	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	for (size_t i = 0, n = m_backgrounds.size(); i < n; ++i)
		m_backgrounds[i]->onDraw();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	for (size_t i = 0, n = m_foregrounds.size(); i < n; ++i)
		m_foregrounds[i]->onDraw();
	glDisable(GL_BLEND);
}

void Scene::update()
{
 	d2d::EventList& list = m_pContext->m_inputService->getEventList();
 	while (!list.empty())
 	{
 		d2d::Event e = list.pop();
 		switch (e.type)
 		{
		case e_touch_down:
			{
				Button* btn = queryButtonByPos(transInputPosToWorld(e.pos));
				if (btn) btn->triggerBehaviors(true);
			}
			break;
		case e_touch_up:
			{
				Button* btn = queryButtonByPos(transInputPosToWorld(e.pos));
				if (btn) btn->triggerBehaviors(false);
			}
			break;
		case d2d::e_key_back_down:
			if (m_parent) m_parent->load();
			m_game->setScene(m_parent);
			break;
		case d2d::e_key_menu_down:
			break;
 		}
 	}	
}

GraphicsSprite* Scene::loadSprite(const std::string& filename) const
{
	d2d::Texture* texture = m_pContext->m_graphicsService->registerTexture(
		d2d::FileSystem::Instance()->getAbsolutePath(filename));
	status s = texture->load();
	assert(s == STATUS_OK);

	return new d2d::GraphicsSprite(texture);
}

d2d::Vector Scene::transInputPosToWorld(const Vector& pos) const
{
	d2d::Vector world;

	float height = m_pContext->m_graphicsService->getHeight();
	float scale = m_pContext->m_graphicsService->getScale();

	world.x = pos.x / scale;
	world.y = (height - pos.y) / scale;

	return world;
}

Button* Scene::queryButtonByPos(const Vector& pos) const
{
	for (size_t i = 0, n = m_foregrounds.size(); i < n; ++i)
	{
		if (m_foregrounds[i]->type() == Item::e_button)
		{
			Button* btn = static_cast<Button*>(m_foregrounds[i]);
			if (btn->isContain(pos))
				return btn;
		}
	}
	return NULL;
}