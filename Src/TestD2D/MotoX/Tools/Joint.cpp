#include "Joint.h"

using namespace motox;

Joint::Joint(b2World* world, const JointDef& params, const d2d::Vector& anchor, 
			 b2Body* b0, b2Body* b1, bool isMotor)
	: m_world(world)
	, m_joint(NULL)
	, m_params(params)
{
	b2RevoluteJointDef rjd;
	rjd.Initialize(b0, b1, b2Vec2(anchor.x * d2d::BOX2D_SCALE_FACTOR_INVERSE, 
		anchor.y * d2d::BOX2D_SCALE_FACTOR_INVERSE));
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

	m_joint = (b2RevoluteJoint*)m_world->CreateJoint(&rjd);

	if (isMotor)
		setAngleLimit(true);
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
	if (isPositive) m_joint->SetMotorSpeed(m_params.positive_speed);
	else m_joint->SetMotorSpeed(m_params.negative_speed);
}

void Joint::setAngleLimit(bool isLeft)
{
	float lower, upper;
	if (isLeft)
	{
		lower = std::min(m_params.left_angle_small, m_params.left_angle_large);
		upper = std::max(m_params.left_angle_small, m_params.left_angle_large);
	}
	else
	{
		lower = std::min(m_params.right_angle_small, m_params.right_angle_large);
		upper = std::max(m_params.right_angle_small, m_params.right_angle_large);
	}
	lower *= d2d::PI;
	upper *= d2d::PI;

	m_joint->SetLimits(lower, upper);
}