#include "WheelJoint.h"
#include "BodyData.h"

using namespace deditor::modeling;

WheelJoint::WheelJoint(BodyData* b0, BodyData* b1)
	: JointData(b0, b1, e_wheelJoint)
	, localAxisA(1, 0)
	, enableMotor(false)
	, maxMotorTorque(0.0f)
	, motorSpeed(0.0f)
	, frequencyHz(2.0f)
	, dampingRatio(0.7f)
{
}

bool WheelJoint::isContain(const f2Vec2& pos) const
{
	return f2Math::getDistance(getWorldAnchorA(), pos) < JOINT_RADIUS_OUT
		|| f2Math::getDistance(getWorldAnchorB(), pos) < JOINT_RADIUS_OUT;
}

void WheelJoint::draw(DrawType type) const
{
	const f2Vec2 anchorA = getWorldAnchorA(),
		anchorB = getWorldAnchorB();

	if (type == e_selected || type == e_mouseOn)
	{
		wxgui::PrimitiveDraw::drawDashLine(anchorA, bodyA->m_sprite->getPosition(), f2Colorf(0.4f, 0.8f, 0.4f), 2);
		wxgui::PrimitiveDraw::drawDashLine(anchorB, bodyB->m_sprite->getPosition(), f2Colorf(0.4f, 0.4f, 0.8f), 2);

		drawAxisALine(anchorA);
		drawFootBLine(anchorA, anchorB);
		drawBodyFlag();
	}

	drawAnchorA(anchorA, type);
	drawAnchorB(anchorB, type);
}

f2Vec2 WheelJoint::getWorldAnchorA() const
{
	return transLocalToWorld(localAnchorA, bodyA->m_sprite);
}

f2Vec2 WheelJoint::getWorldAnchorB() const
{
	return transLocalToWorld(localAnchorB, bodyB->m_sprite);
}

void WheelJoint::setLocalAnchorA(const f2Vec2& world)
{
	localAnchorA = transWorldToLocal(world, bodyA->m_sprite);
}

void WheelJoint::setLocalAnchorB(const f2Vec2& world)
{
	localAnchorB = transWorldToLocal(world, bodyB->m_sprite);
}

void WheelJoint::drawAxisALine(const f2Vec2& worldAnchorA) const
{
	f2Vec2 unit = localAxisA;
	unit.normalize();

	const f2Vec2 start = worldAnchorA + unit * 150,
		end = worldAnchorA - unit * 150;

	wxgui::PrimitiveDraw::drawDotDashLine(start, end, f2Colorf(0.4f, 0.6f, 0.4f), 1);
}

void WheelJoint::drawFootBLine(const f2Vec2& worldAnchorA, const f2Vec2& worldAnchorB) const
{
	f2Vec2 otherA = worldAnchorA + localAxisA;

	f2Vec2 foot;
	f2Math::getFootOfPerpendicular(worldAnchorA, otherA, worldAnchorB, &foot);

	wxgui::PrimitiveDraw::drawDashLine(worldAnchorB, foot, f2Colorf(1, 0, 0), 1);
	wxgui::PrimitiveDraw::drawCircle(foot, JOINT_RADIUS_IN, f2Colorf(1, 0, 0));
}

void WheelJoint::drawAnchorA(const f2Vec2& pos, DrawType type) const
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
	wxgui::PrimitiveDraw::drawSquare(pos, JOINT_RADIUS_OUT, color);
}

void WheelJoint::drawAnchorB(const f2Vec2& pos, DrawType type) const
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