#include "ArrangeSpritePhysOp.h"
#include "SelectSpritesOp.h"
#include "../QueryStrategy/PhysOnQst.h"
#include "../QueryStrategy/PhysNearQst.h"
#include <Box2D/Box2D.h>

using namespace FEDITOR;

ArrangeSpritePhysOp::ArrangeSpritePhysOp(AbstractControl* task, b2World* world, 
										 b2Body* ground, int type/* = e_MouseOn*/)
	: AbstractOp(task)
{
//	m_selectOp = NULL;

	m_world = world;
	m_ground = ground;

	m_queryType = type;

	m_mouseJoint = NULL;
}

// ArrangeSpritePhysOp::ArrangeSpritePhysOp(AbstractControl* task, Layer* editable, 
// 										 b2World* world, b2Body* ground, 
// 										 int type/* = e_MouseOn*/)
// 	: AbstractOp(task)
// {
// 	m_selectOp = new SelectSpritesOp(task, editable);
// 	
// 	m_world = world;
// 	m_ground = ground;
// 
// 	m_queryType = type;
// 
// 	m_mouseJoint = NULL;
// }

ArrangeSpritePhysOp::~ArrangeSpritePhysOp()
{
//	if (m_selectOp) delete m_selectOp;
}

void ArrangeSpritePhysOp::onMouseLeftDown(int x, int y)
{
//	if (m_selectOp) m_selectOp->onMouseLeftDown(x, y);

	if (m_mouseJoint) return;

	const f2Vec2 pos = getMousePos(x, y);

	b2Body* body = NULL;
	switch (m_queryType)
	{
	case e_MouseOn:
		{
			PhysOnQst query(m_world);
			body = query.query(pos);
		}
		break;
	case e_MouseNear:
		{
			PhysNearQst query(m_world);
			body = query.query(pos);
		}
		break;
	}

	if (body && body != m_ground)
	{
		b2MouseJointDef md;
		md.bodyA = m_ground;
		md.bodyB = body;
		md.target = b2Vec2(pos.x, pos.y);
		md.maxForce = 1000.0f * body->GetMass();
		m_mouseJoint = (b2MouseJoint*)m_world->CreateJoint(&md);
		body->SetAwake(true);
	}
}

void ArrangeSpritePhysOp::onMouseLeftUp(int x, int y)
{
//	if (m_selectOp) m_selectOp->onMouseLeftUp(x, y);

	if (m_mouseJoint)
	{
		m_world->DestroyJoint(m_mouseJoint);
		m_mouseJoint = NULL;
	}
}

void ArrangeSpritePhysOp::onMouseDrag(int x, int y)
{
	if (m_mouseJoint)
	{
		const f2Vec2 pos = getMousePos(x, y);
		m_mouseJoint->SetTarget(b2Vec2(pos.x, pos.y));
	}
}