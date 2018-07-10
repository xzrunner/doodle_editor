#include "RevoluteJoint.h"
#include "BodyData.h"

using namespace deditor::modeling;

RevoluteJoint::RevoluteJoint(BodyData* b0, BodyData* b1)
	: JointData(b0, b1, e_revoluteJoint)
	, referenceAngle(0.0f)
	, enableLimit(false)
	, lowerAngle(0.0f)
	, upperAngle(0.0f)
	, enableMotor(false)
	, maxMotorTorque(0.0f)
	, motorSpeed(0.0f)
{
	f2Vec2 center = (b0->m_sprite->getPosition() + b1->m_sprite->getPosition()) * 0.5f;
	setLocalAnchorA(center);
	setLocalAnchorB(center);
}

bool RevoluteJoint::isContain(const f2Vec2& pos) const
{
	return f2Math::getDistance(getWorldAnchorA(), pos) < JOINT_RADIUS_OUT
		|| f2Math::getDistance(getWorldAnchorB(), pos) < JOINT_RADIUS_OUT;
}

void RevoluteJoint::draw(DrawType type) const
{
	const f2Vec2 anchorA = getWorldAnchorA(),
		anchorB = getWorldAnchorB();

	if (type == e_selected || type == e_mouseOn)
	{
		wxgui::PrimitiveDraw::drawDashLine(anchorA, anchorB, f2Colorf(1, 0, 0), 2);
		wxgui::PrimitiveDraw::drawDashLine(anchorA, bodyA->m_sprite->getPosition(), f2Colorf(0.4f, 0.8f, 0.4f), 2);
		wxgui::PrimitiveDraw::drawDashLine(anchorB, bodyB->m_sprite->getPosition(), f2Colorf(0.4f, 0.4f, 0.8f), 2);

		drawBodyFlag();
	}

	drawAnchor(anchorA, type);
	drawAnchor(anchorB, type);
}

f2Vec2 RevoluteJoint::getWorldAnchorA() const
{
	return transLocalToWorld(localAnchorA, bodyA->m_sprite);
}

f2Vec2 RevoluteJoint::getWorldAnchorB() const
{
	return transLocalToWorld(localAnchorB, bodyB->m_sprite);
}

void RevoluteJoint::setLocalAnchorA(const f2Vec2& world)
{
	localAnchorA = transWorldToLocal(world, bodyA->m_sprite);
}

void RevoluteJoint::setLocalAnchorB(const f2Vec2& world)
{
	localAnchorB = transWorldToLocal(world, bodyB->m_sprite);
}

void RevoluteJoint::drawAnchor(const f2Vec2& pos, DrawType type) const
{
	f2Colorf color;
	switch (type)
	{
	case e_default:
		color.set(0.8f, 0.8f, 0.8f);
		break;
	case e_mouseOn:
		color.set(1, 1, 1);
		break;
	case e_selected:
		color.set(1, 1, 0);
		break;
	}

	wxgui::PrimitiveDraw::drawCircle(pos, JOINT_RADIUS_IN, color);
	wxgui::PrimitiveDraw::drawRing(pos, JOINT_RADIUS_OUT, color);
}
