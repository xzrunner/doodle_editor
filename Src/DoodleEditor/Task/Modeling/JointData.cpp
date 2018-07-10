#include "JointData.h"
#include "BodyData.h"

using namespace deditor::modeling;

const float JointData::JOINT_RADIUS_OUT = 1.0f;
const float JointData::JOINT_RADIUS_IN = 0.2f;
const float JointData::JOINT_RADIUS_SELECT = JOINT_RADIUS_OUT * 3;

JointData::JointData(BodyData* b0, BodyData* b1, Type type)
	: bodyA(b0)
	, bodyB(b1)
	, type(type)
	, collideConnected(false)
{
	static int count = 0;
	m_name = wxT("joint") + wxString::FromDouble(count++);
}

void JointData::drawBodyFlag() const
{
	drawBodyFlag(bodyA->m_sprite->getPosition());
	drawBodyFlag(bodyB->m_sprite->getPosition());
}

f2Vec2 JointData::transWorldToLocal(const f2Vec2& world, 
									const wxgui::ISprite* sprite)
{
	return f2Math::rotateVector(world - sprite->getPosition(), -sprite->getAngle());
}

f2Vec2 JointData::transLocalToWorld(const f2Vec2& local, 
									const wxgui::ISprite* sprite)
{
	return f2Math::rotateVector(local, sprite->getAngle()) + sprite->getPosition();
}

void JointData::drawBodyFlag(const f2Vec2& pos) const
{
	const float edge = 2.5f;

	std::vector<f2Vec2> vertices(4, pos);
	vertices[0].x -= edge;
	vertices[1].x += edge;
	vertices[2].y -= edge;
	vertices[3].y += edge;
	wxgui::PrimitiveDraw::drawLines(vertices, f2Colorf(0.4f, 0.8f, 0.8f), 1);
}
