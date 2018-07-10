#include "Model.h"
#include "Blackboard.h"
#include "Render.h"
#include "Dataset/Sprite.h"

using namespace FEDITOR;
using namespace FEDITOR::TEST_RENDERING;

Model::Model(const AbstractBlackboard* blackboard, AbstractView* view)
{
	m_blackboard = static_cast<Blackboard*>(const_cast<AbstractBlackboard*>(blackboard));
	Render::m_bb = m_blackboard;
	m_view = view;
}

Model::~Model()
{
}

void Model::handleEvent(const Event& event)
{
	switch (event.getID())
	{
	case Blackboard::e_Open:
		m_filename = event.getInfo();
		break;
	case Blackboard::e_Step:
		if (m_filename != "" && m_blackboard->m_num != m_sprites.size())
			initData();
		renderData();
		break;
	}
}

void Model::initData()
{
	for_each(m_sprites.begin(), m_sprites.end(), DeletePointerFunctor<Sprite>());
	m_sprites.clear();
	for (size_t i = 0; i < m_blackboard->m_num; ++i)
	{
		Sprite* sprite = new Sprite;
		sprite->loadFromUnknownFile(m_filename);
		f2Vec2 pos;
		pos.x = - 1000 + Random::getNum0To1() * 2000;
		pos.y = - 500 + Random::getNum0To1() * 1000;
		sprite->setTransform(pos, 0);
		m_sprites.push_back(sprite);
	}
}

void Model::renderData()
{
	switch (m_blackboard->m_renderType)
	{
	case 0:
		Render::immediateMode(m_sprites, m_view);
		break;
	case 1:
		Render::bindOneTime(m_sprites, m_view);
		break;
	case 2:
		Render::bindOneTime_strip(m_sprites, m_view);
		break;
	case 3:
		Render::bindOneTime_strip_death(m_sprites, m_view);
		break;
	case 4:
		Render::drawArrays(m_sprites, m_view);
		break;
	case 5:
		Render::drawElements(m_sprites, m_view);
		break;
	case 6:
		Render::drawElements_interleave(m_sprites, m_view);
		break;
	case 7:
		Render::drawRangeElements(m_sprites, m_view);
		break;
	case 8:
		Render::displayList(m_sprites, m_view);
		break;
	case 9:
		Render::vbo(m_sprites, m_view);
		break;
	}
}