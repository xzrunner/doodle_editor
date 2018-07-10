#include "ArrangeSpriteOp.h"
#include "AbstractArrangeSpriteCB.h"
#include "../KeyboardTest.h"
#include "../AbstractControl.h"
#include "../../Dataset/Sprite.h"
#include "../../Dataset/Layer.h"
#include "../../Dataset/LayersMgr.h"

using namespace FEDITOR;

ArrangeSpriteOp::ArrangeSpriteOp(AbstractControl* task, Layer* editable, bool toInteger/* = false*/,
								 AbstractArrangeSpriteCB* callback/* = NULL*/, AbstractOp* supplement/* = NULL*/)
	: AbstractOp(task, supplement), m_selectOp(task, editable), m_selection(m_selectOp.getSelection())
{
	m_callback = callback;
	assert(editable);
	m_layer = editable;
	m_bRightPress = false;
	m_rightDownPos.setInvalid();

	m_xScaleInit, m_yScaleInit = 1.0f;

	m_toInteger = toInteger;
}

ArrangeSpriteOp::~ArrangeSpriteOp()
{
	if (m_callback) delete m_callback;
}

void ArrangeSpriteOp::onKeyboard(unsigned char key)
{
	switch (key)
	{
	case KEY_DELETE:
		if (m_layer)
		{
			const std::set<Sprite*>& selection = m_selection.getAll();
			std::set<Sprite*>::const_iterator itr = selection.begin();
			for ( ; itr != selection.end(); ++itr)
			{
				m_layer->deleteSprite(*itr);
				if (m_callback) m_callback->deleteSprite(*itr);
			}
			m_selection.clear();
		}
		break;
	default:
		if (m_supplement) m_supplement->onKeyboard(key);
	}
}

void ArrangeSpriteOp::onKeyboardSpecial(int key)
{
	const float delta = 1.0f * m_task->getScale();

	switch (key)
	{
	case KEY_LEFT:
		translateSprite(f2Vec2(-delta, 0.0f));
		break;
	case KEY_RIGHT:
		translateSprite(f2Vec2(delta, 0.0f));
		break;
	case KEY_UP:
		translateSprite(f2Vec2(0.0f, delta));
		break;
	case KEY_DOWN:
		translateSprite(f2Vec2(0.0f, -delta));
		break;
	}
}

void ArrangeSpriteOp::onMouseLeftDown(int x, int y)
{
	m_selectOp.onMouseLeftDown(x, y);
	m_lastPos = getMousePos(x, y);
	if (m_toInteger) m_lastPos.toInteger();
	if (m_callback) m_callback->afterMouseLeftDown(m_lastPos);
}

void ArrangeSpriteOp::onMouseLeftUp(int x, int y)
{
	m_selectOp.onMouseLeftUp(x, y);
	if (m_callback) m_callback->afterMouseLeftUp(getMousePos(x, y));
}

bool ArrangeSpriteOp::onMouseRightDown(int x, int y)
{
	m_selectOp.onMouseRightDown(x, y);
	m_lastPos = getMousePos(x, y);

	Sprite* single = m_selection.getSingle();
	if (single)
	{
		m_bRightPress = true;
//		if (single->isContain(m_lastPos))
			m_rightDownPos.set(x, y);
		m_xScaleInit = single->getXScale();
		m_yScaleInit = single->getYScale();
		return true;
	}
	else
	{
		return false;
	}
}

bool ArrangeSpriteOp::onMouseRightUp(int x, int y)
{
	if (m_bRightPress)
	{
		m_bRightPress = false;
		if (m_rightDownPos.isValid() && f2Math::getDistance(m_rightDownPos, f2Vec2(x, y)) < DELETE_DIS)
		{
			Sprite* single = m_selection.getSingle();
			if (single)
			{
				m_layer->deleteSprite(single);
				if (m_callback) m_callback->deleteSprite(single);
				m_selection.clear();
			}
			m_rightDownPos.setInvalid();
		}
		return true;
	}
	else
	{
		return false;
	}
}

void ArrangeSpriteOp::onMouseDrag(int x, int y)
{
	m_selectOp.onMouseDrag(x, y);

	if (m_selection.empty()) return;

	f2Vec2 curr = getMousePos(x, y);
	if (m_bRightPress)
	{
		if (KeyBoardTest::isCtrlPress())
			scaleSpriteTo(curr);
		else
			rotateSpriteTo(curr);
	}
	else
	{
		if (m_toInteger) curr.toInteger();
		translateSpriteTo(curr);
	}
	m_lastPos = curr;
}

void ArrangeSpriteOp::translateSprite(const f2Vec2& delta)
{
	const std::set<Sprite*>& sprites = m_selection.getAll();
	std::set<Sprite*>::const_iterator itr = sprites.begin();
	for ( ; itr != sprites.end(); ++itr)
	{
		(*itr)->translate(delta);
		if (m_callback) m_callback->afterMoveSprite(*itr);
	}
}

void ArrangeSpriteOp::translateSpriteTo(const f2Vec2& dst)
{
	const std::set<Sprite*>& sprites = m_selection.getAll();
	std::set<Sprite*>::const_iterator itr = sprites.begin();
	for ( ; itr != sprites.end(); ++itr)
	{
		(*itr)->translate(dst - m_lastPos);
		if (m_callback) m_callback->afterMoveSprite(*itr);
	}
}

void ArrangeSpriteOp::rotateSpriteTo(const f2Vec2& dst)
{
	Sprite* sprite = m_selection.getSingle();
	if (sprite)
	{
		float angle = f2Math::getAngleInDirection(sprite->getPosition(), m_lastPos, dst);
		sprite->rotate(angle);
		if (m_callback) m_callback->afterMoveSprite(sprite);
	}
}

void ArrangeSpriteOp::scaleSpriteTo(const f2Vec2& dst)
{
	Sprite* sprite = m_selection.getSingle();
	if (sprite)
	{
		const float beginDis = f2Math::getDistance(getMousePos(m_rightDownPos.x, m_rightDownPos.y), sprite->getPosition()),
			currDis = f2Math::getDistance(dst, sprite->getPosition());
		const float scale = currDis / beginDis;
		sprite->setScale(m_xScaleInit * scale, m_yScaleInit * scale, true);
	}
}