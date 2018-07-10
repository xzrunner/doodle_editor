#include "ArrangeSpriteCommonOp.h"
#include "ArrangeSpriteOp.h"
#include "ArrangeSpritePhysOp.h"
#include "../../Dataset/Sprite.h"
#include "../../Dataset/Layer.h"

using namespace FEDITOR;

ArrangeSpriteCommonOp::ArrangeSpriteCommonOp(AbstractControl* task, Layer* editable, b2World* world, b2Body* ground, 
											 int physQueryType/* = ArrangeSpritePhysOp::e_MouseOn*/, AbstractArrangeSpriteCB* callback/* = NULL*/,
											 AbstractOp* supplement/* = NULL*/)
	: AbstractOp(task)
{
	m_editable = editable;

	m_world = world;
	m_ground = ground;
	m_queryType = physQueryType;

	m_callback = callback;
	m_supplement = supplement;

	m_noPhysOp = NULL;
	m_physOp = NULL;
}

void ArrangeSpriteCommonOp::onKeyboard(unsigned char key)
{
	if (m_noPhysOp) m_noPhysOp->onKeyboard(key);
	else if (m_supplement) m_supplement->onKeyboard(key);
}

void ArrangeSpriteCommonOp::onMouseLeftDown(int x, int y)
{
	initOp(getMousePos(x, y));

	if (m_noPhysOp) m_noPhysOp->onMouseLeftDown(x, y);
	else if (m_physOp) m_physOp->onMouseLeftDown(x, y);
}

void ArrangeSpriteCommonOp::onMouseLeftUp(int x, int y)
{
	if (m_noPhysOp) m_noPhysOp->onMouseLeftUp(x, y);
	else if (m_physOp) m_physOp->onMouseLeftUp(x, y);
}

bool ArrangeSpriteCommonOp::onMouseRightDown(int x, int y)
{
	if (m_noPhysOp) return m_noPhysOp->onMouseRightDown(x, y);
	else return false;
}

bool ArrangeSpriteCommonOp::onMouseRightUp(int x, int y)
{
	if (m_noPhysOp) return m_noPhysOp->onMouseRightUp(x, y);
	else return false;
}

void ArrangeSpriteCommonOp::onMouseDrag(int x, int y)
{
	if (m_noPhysOp) m_noPhysOp->onMouseDrag(x, y);
	else if (m_physOp) m_physOp->onMouseDrag(x, y);
}

b2World* ArrangeSpriteCommonOp::getWorld() const
{
	return m_world;
}

void ArrangeSpriteCommonOp::initOp(const f2Vec2& pos)
{
	Sprite* sprite = m_editable->queryByPos(pos);
	if (sprite && sprite->getBody() && sprite->getBody()->isAlive())
	{
		if (m_physOp)
			delete m_noPhysOp, m_noPhysOp = NULL;
		else
			m_physOp = new ArrangeSpritePhysOp(m_task, m_world, m_ground, m_queryType);
	}
	else
	{
		if (m_noPhysOp)
			delete m_physOp, m_physOp = NULL;
		else
			m_noPhysOp = new ArrangeSpriteOp(m_task, m_editable, false, m_callback, m_supplement);
	}
}