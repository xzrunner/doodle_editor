#include "Joint.h"
#include "../Edit/MotoX/ActorDefs.h"
#include <Box2D/Box2D.h>

using namespace FEDITOR;

Joint::Joint(b2World* world, const MOTOX::JointParams& params, const f2Vec2& anchor, 
			 b2Body* b0, b2Body* b1, bool isMotor, float scale)
	: m_world(world), m_joint(NULL)
{
	m_scale = scale;
	initialize(params, anchor, b0, b1, isMotor);
}

Joint::~Joint()
{
	if (m_joint)
	{
		m_world->DestroyJoint(m_joint);
		m_joint = NULL;
	}
}

void Joint::setMotorSpeed(bool isPositive)
{
	if (isPositive) m_joint->SetMotorSpeed(m_positiveSpeed);
	else m_joint->SetMotorSpeed(m_negativeSpeed);
}

void Joint::setAngleLimit(bool isLeft)
{
	float lower, upper;
	if (isLeft)
	{
		lower = std::min(m_leftAngle, m_midAngle);
		upper = std::max(m_leftAngle, m_midAngle);
	}
	else
	{
		lower = std::min(m_midAngle, m_rightAngle);
		upper = std::max(m_midAngle, m_rightAngle);
	}
	lower *= PI;
	upper *= PI;

	m_joint->SetLimits(lower, upper);
}

void Joint::initialize(const MOTOX::JointParams& params, const f2Vec2& anchor, b2Body* b0, b2Body* b1, bool isMotor)
{
	m_negativeSpeed = params.negative_speed;
	m_positiveSpeed = params.positive_speed;
	m_leftAngle = params.left_angle;
	m_midAngle = params.mid_angle;
	m_rightAngle = params.right_angle;

	b2RevoluteJointDef rjd;
	b2Vec2 b2_anchor(anchor.x, anchor.y);
	rjd.Initialize(b0, b1, b2_anchor);
	rjd.collideConnected = false;
	rjd.maxMotorTorque = params.max_torque;
	if (isMotor)
	{
		rjd.enableLimit = true;
		rjd.enableMotor = true;
	}
	else
	{
		rjd.enableLimit = false;
		rjd.enableMotor = false;
	}

	if (m_joint) m_world->DestroyJoint(m_joint);

	m_joint = (b2RevoluteJoint*) m_world->CreateJoint(&rjd);
}