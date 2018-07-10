#include "SelectSpritesOp.h"
#include "../KeyboardTest.h"
#include "../AbstractControl.h"
#include "../../Dataset/Sprite.h"
#include "../../Dataset/ChainShape.h"
#include "../../Dataset/Layer.h"
#include "../../Dataset/LayersMgr.h"

using namespace FEDITOR;

SelectSpritesOp::SelectSpritesOp(AbstractControl* task, Layer* editable, bool isAccurate/* = false*/)
	: AbstractOp(task), m_selection(task->getLayersMgr().getSelection())
{
	m_isAccurate = isAccurate;

	assert(m_dataLayer);
	m_dataLayer = editable;

	m_firstPos.setInvalid();
	prepareSelectDraw();
}

SelectSpritesOp::~SelectSpritesOp()
{
	m_tmpLayer->deleteSprite(m_tmpSprite);
}

void SelectSpritesOp::onKeyboard(unsigned char key)
{
	switch (key)
	{
	case KEY_DELETE:
		if (m_dataLayer)
		{
			const std::set<Sprite*>& selection = m_selection.getAll();
			std::set<Sprite*>::const_iterator itr = selection.begin();
			for ( ; itr != selection.end(); ++itr)
				m_dataLayer->deleteSprite(*itr);
			m_selection.clear();
		}
		break;
	}
}

void SelectSpritesOp::onMouseLeftDown(int x, int y)
{
	f2Vec2 pos = getMousePos(x, y);
	Sprite* selected = m_dataLayer->queryByPos(pos, m_isAccurate);
	if (selected)
	{
		if (KeyBoardTest::isCtrlPress())
		{
			m_selection.add(selected);
		}
		else
		{
			if (!m_selection.exist(selected))
			{
				m_selection.clear();
				m_selection.add(selected);
			}
		}
	}
	else
	{
		m_firstPos = pos;
		m_selection.clear();
	}
}

void SelectSpritesOp::onMouseLeftUp(int x, int y)
{
	if (!m_firstPos.isValid()) return;

	f2AABB aabb(m_firstPos, getMousePos(x, y));
	std::vector<Sprite*> sprites;
	m_dataLayer->queryByAABB(aabb, sprites);
	for (size_t i = 0, n = sprites.size(); i < n; ++i)
		m_selection.add(sprites[i]);

	ChainShape* shape = dynamic_cast<ChainShape*>(m_tmpSprite->popShape());
	assert(shape);
	shape->m_vertices.clear();
	m_tmpSprite->pushShape(shape);

	m_firstPos.setInvalid();
}

bool SelectSpritesOp::onMouseRightDown(int x, int y)
{
	Sprite* selected = m_dataLayer->queryByPos(getMousePos(x, y), m_isAccurate);
	if (selected)
	{
		m_selection.clear();
		m_selection.add(selected);
		return true;
	}
	else
	{
		return false;
	}
}

void SelectSpritesOp::onMouseDrag(int x, int y)
{
	if (!m_firstPos.isValid()) return;

	f2Vec2 p = getMousePos(x, y);
	m_tmpShape->m_vertices.clear();
	m_tmpShape->pushBack(m_firstPos);
	m_tmpShape->pushBack(f2Vec2(m_firstPos.x, p.y));
	m_tmpShape->pushBack(p);
	m_tmpShape->pushBack(f2Vec2(p.x, m_firstPos.y));
}

void SelectSpritesOp::prepareSelectDraw()
{
	m_tmpLayer = m_task->getLayersMgr().getLayer(Layer::e_uppermost);
	assert(m_tmpLayer);
	m_tmpLayer->m_style.m_bDrawCtlPos = false;
	m_tmpSprite = new Sprite;
	m_tmpLayer->addSprite(m_tmpSprite);
	m_tmpShape = new ChainShape;
	m_tmpShape->m_isLoop = true;
	m_tmpSprite->pushShape(m_tmpShape);
}