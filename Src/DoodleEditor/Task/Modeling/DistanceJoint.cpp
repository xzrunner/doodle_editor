#include "DistanceJoint.h"
#include "BodyData.h"

using namespace deditor::modeling;

DistanceJoint::DistanceJoint(BodyData* b0, BodyData* b1)
	: JointData(b0, b1, e_distanceJoint)
	, length(1.0f)
	, frequencyHz(0.0f)
	, dampingRatio(0.0f)
{
}

bool DistanceJoint::isContain(const f2Vec2& pos) const
{
	return f2Math::getDistance(getWorldAnchorA(), pos) < JOINT_RADIUS_OUT
		|| f2Math::getDistance(getWorldAnchorB(), pos) < JOINT_RADIUS_OUT;
}

void DistanceJoint::draw(DrawType type) const
{
	const f2Vec2 anchorA = getWorldAnchorA(),
		anchorB = getWorldAnchorB();

	if (type == e_selected || type == e_mouseOn)
	{
		wxgui::PrimitiveDraw::drawDashLine(anchorA, bodyA->m_sprite->getPosition(), f2Colorf(0.4f, 0.8f, 0.4f), 2);
		wxgui::PrimitiveDraw::drawDashLine(anchorB, bodyB->m_sprite->getPosition(), f2Colorf(0.4f, 0.4f, 0.8f), 2);

		drawBodyFlag();
	}

	drawAnchor(anchorA, type);
	drawAnchor(anchorB, type);
	drawConnection(anchorA, anchorB, type);
}


f2Vec2 DistanceJoint::getWorldAnchorA() const
{
	return transLocalToWorld(localAnchorA, bodyA->m_sprite);
}

f2Vec2 DistanceJoint::getWorldAnchorB() const
{
	return transLocalToWorld(localAnchorB, bodyB->m_sprite);
}

void DistanceJoint::setLocalAnchorA(const f2Vec2& world)
{
	localAnchorA = transWorldToLocal(world, bodyA->m_sprite);
}

void DistanceJoint::setLocalAnchorB(const f2Vec2& world)
{
	localAnchorB = transWorldToLocal(world, bodyB->m_sprite);
}

void DistanceJoint::drawAnchor(const f2Vec2& pos, DrawType type) const
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

void DistanceJoint::drawConnection(const f2Vec2& worldAnchorA, const f2Vec2& worldAnchorB,
								   DrawType type) const
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

	wxgui::PrimitiveDraw::drawLine(worldAnchorA, worldAnchorB, color, 1);
}