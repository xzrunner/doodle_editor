#include "Joints.h"
#include "Parts.h"
#include "Blackboard.h"
#include "../Utility.h"
#include "../../../Dataset/Sprite.h"
#include "../../../File/ActorMotionAdapter.h"
#include <Box2D/Box2D.h>

using namespace FEDITOR;
using namespace FEDITOR::MOTOX::JOINT;

const float Joints::JOINTS_PARAMS[][6] = {
	{	-2, 	2,		0.02f,		0.15f,		0.02f,	10	},
	{	-3,		3,		0.0f,		0.25f,		-0.32f,	10	},
	{	-5,		5,		-0.3f,		-0.036f,	0.28f,	10	},
	{	-3,		3,		-0.027f,	-0.036f,	-0.4f,	10	},
	{	-5,		5,		0.03f,		0.38f,		0.033f,	10	}
};

const bool Joints::JOINT_DIR_FLAG[][MOTOX::JOINTS_COUNT] = {
	{ true,	true, true, false, false, true, true, true, true,		true, true, true, true },
	{ false,true, true, false, false, true, true, false, false,		true, true, true, true }
};

Joints::Joints(b2World* world, MOTOX::JointParams* jointParams)
{
	m_world = world;
	m_jointParams = jointParams;

	memset(m_joints, 0, sizeof(int) * JOINTS_COUNT);
	m_frontWheelJoint = m_backWheelJoint = NULL;

	initJointsParams();

	m_state = e_PlayerStateMiddle;
}

void Joints::loadFromTextFile(std::ifstream& fin)
{
	for (size_t i = 0; i < JOINTS_TYPE_COUNT; ++i)
	{
		f2Vec2 anchor;
		fin >> m_jointParams[i] >> anchor;
	}
}

void Joints::storeToTextFile(std::ofstream& fout) const
{
	for (size_t i = 0; i < JOINTS_TYPE_COUNT; ++i)
	{
		size_t joint = i == 0 ? 0 : (i - 1) * 2 + 1;
		b2Vec2 anchor = m_joints[joint]->m_joint->GetAnchorA();
		fout << m_jointParams[i] << " " << anchor.x << " " << anchor.y << '\n';
	}
}

void Joints::loadFromFileAdapter(const ActorMotionAdapter& adapter)
{
	for (size_t i = 0; i < JOINTS_TYPE_COUNT; ++i)
		m_jointParams[i] = adapter.m_joints[i].params;
}

void Joints::createJoint(size_t jointType, Parts& parts, const f2Vec2& anchor)
{
 	switch (jointType)
 	{
 	case e_JointTypeNeck:
 		createPlayerJoint(e_JointNeck, e_JointTypeNeck, 
			parts.getPart(e_PartBody), parts.getPart(e_PartHead), anchor);
 		break;
 	case e_JointTypeShoulder:
 		createPlayerJoint(e_JointShoulderL, e_JointTypeShoulder, 
			parts.getPart(e_PartBody), parts.getPart(e_PartBigArmLeft), anchor);
 		createPlayerJoint(e_JointShoulderR, e_JointTypeShoulder, 
			parts.getPart(e_PartBody), parts.getPart(e_PartBigArmRight), anchor);
 		break;
 	case e_JointTypeElbow:
 		createPlayerJoint(e_JointElbowL, e_JointTypeElbow, 
			parts.getPart(e_PartBigArmLeft), parts.getPart(e_PartSmallArmLeft), anchor);
 		createPlayerJoint(e_JointElbowR, e_JointTypeElbow, 
			parts.getPart(e_PartBigArmRight), parts.getPart(e_PartSmallArmRight), anchor);
 		break;
 	case e_JointTypeHip:
 		createPlayerJoint(e_JointHipL, e_JointTypeHip, 
			parts.getPart(e_PartBody), parts.getPart(e_PartBigLegLeft), anchor);
 		createPlayerJoint(e_JointHipR, e_JointTypeHip, 
			parts.getPart(e_PartBody), parts.getPart(e_PartBigLegRight), anchor);
 		break;
 	case e_JointTypeKnee:
 		createPlayerJoint(e_JointKneeL, e_JointTypeKnee, 
			parts.getPart(e_PartBigLegLeft), parts.getPart(e_PartSmallLegLeft), anchor);
 		createPlayerJoint(e_JointKneeR, e_JointTypeKnee, 
			parts.getPart(e_PartBigLegRight), parts.getPart(e_PartSmallLegRight), anchor);
 		break;
 	case e_JointTypeHand:
 		createPlayerJoint(e_JointHandL, e_JointTypeHand, 
			parts.getPart(e_PartSmallArmLeft), parts.getPart(e_PartMotorBody), anchor);
 		createPlayerJoint(e_JointHandR, e_JointTypeHand, 
			parts.getPart(e_PartSmallArmRight), parts.getPart(e_PartMotorBody), anchor);
 		break;
 	case e_JointTypeFoot:
 		createPlayerJoint(e_JointFootL, e_JointTypeFoot, 
			parts.getPart(e_PartSmallLegLeft), parts.getPart(e_PartMotorBody), anchor);
 		createPlayerJoint(e_JointFootR, e_JointTypeFoot, 
			parts.getPart(e_PartSmallLegRight), parts.getPart(e_PartMotorBody), anchor);
 		break;
 	}
}

void Joints::createWheelsJoint(Parts& parts)
{
	if (m_frontWheelJoint) m_world->DestroyJoint(m_frontWheelJoint);
	if (m_backWheelJoint) m_world->DestroyJoint(m_backWheelJoint);

	b2WheelJointDef jd;
	b2Vec2 axis(0.0f, 1.0f);

	b2Body *body = parts.getPart(e_PartMotorBody)->getBody()->getBody(),
		*back = parts.getPart(e_PartBackWheel)->getBody()->getBody(),
		*front = parts.getPart(e_PartFrontWheel)->getBody()->getBody();

	jd.Initialize(body, back, back->GetPosition(), axis);
	jd.motorSpeed = 0.0f;
	jd.maxMotorTorque = 20;
	jd.enableMotor = true;
	jd.frequencyHz = 14;
	jd.dampingRatio = 7;
	m_backWheelJoint = (b2WheelJoint*) m_world->CreateJoint(&jd);

	jd.Initialize(body, front, front->GetPosition(), axis);
	jd.motorSpeed = 0.0f;
	jd.maxMotorTorque = 10;
	jd.enableMotor = false;
	jd.frequencyHz = 14;
	jd.dampingRatio = 7;
	m_frontWheelJoint = (b2WheelJoint*) m_world->CreateJoint(&jd);
}

void Joints::setJointParams(size_t jointType)
{
	switch (jointType)
	{
	case e_JointTypeNeck:
		m_joints[e_JointNeck]->resetParams();
		break;
	case e_JointTypeShoulder:
		m_joints[e_JointShoulderL]->resetParams();
		m_joints[e_JointShoulderR]->resetParams();
		break;
	case e_JointTypeElbow:
		m_joints[e_JointElbowL]->resetParams();
		m_joints[e_JointElbowR]->resetParams();
		break;
	case e_JointTypeHip:
		m_joints[e_JointHipL]->resetParams();
		m_joints[e_JointHipR]->resetParams();
		break;
	case e_JointTypeKnee:
		m_joints[e_JointKneeL]->resetParams();
		m_joints[e_JointKneeR]->resetParams();
		break;
	case e_JointTypeHand:
		m_joints[e_JointHandL]->resetParams();
		m_joints[e_JointHandR]->resetParams();
		break;
	case e_JointTypeFoot:
		m_joints[e_JointFootL]->resetParams();
		m_joints[e_JointFootR]->resetParams();
		break;
	}
}

void Joints::setJointMotion(MOTOX::PLAYER_MOTION dir)
{
	switch (dir)
	{
	case e_PlayerToLeft:
		if (m_state == e_PlayerStateMiddle) 
		{
			doPlayerMotion(true, false);
			m_state = e_PlayerStateLeft;
		}
		else if (m_state == e_PlayerStateRight) 
		{
			doPlayerMotion(false, false);
			m_state = e_PlayerStateMiddle;
		}
		break;
	case e_PlayerToMiddle:
		if (m_state == e_PlayerStateLeft) 
		{
			doPlayerMotion(true, true);
			m_state = e_PlayerStateMiddle;
		}
		else if (m_state == e_PlayerStateRight)
		{
			doPlayerMotion(false, false);
			m_state = e_PlayerStateMiddle;
		}
		break;
	case e_PlayerToRight:
		if (m_state == e_PlayerStateLeft) 
		{
			doPlayerMotion(true, true);
			m_state = e_PlayerStateMiddle;
		}
		else if (m_state == e_PlayerStateMiddle) 
		{
			doPlayerMotion(false, true);
			m_state = e_PlayerStateRight;
		}
		break;
	}
}

const MOTOX::JointParams& Joints::getJointParams(size_t jointType) const
{
	return m_jointParams[jointType];
}

void Joints::setJointMotion(size_t jointType, bool isPositive)
{
	switch (jointType)
	{
	case e_JointTypeNeck:
		m_joints[e_JointNeck]->setMotorSpeed(isPositive);
		break;
	case e_JointTypeShoulder:
		m_joints[e_JointShoulderL]->setMotorSpeed(isPositive);
		m_joints[e_JointShoulderR]->setMotorSpeed(isPositive);
		break;
	case e_JointTypeElbow:
		m_joints[e_JointElbowL]->setMotorSpeed(isPositive);
		m_joints[e_JointElbowR]->setMotorSpeed(isPositive);
		break;
	case e_JointTypeHip:
		m_joints[e_JointHipL]->setMotorSpeed(isPositive);
		m_joints[e_JointHipR]->setMotorSpeed(isPositive);
		break;
	case e_JointTypeKnee:
		m_joints[e_JointKneeL]->setMotorSpeed(isPositive);
		m_joints[e_JointKneeR]->setMotorSpeed(isPositive);
		break;
	case e_JointTypeHand:
		m_joints[e_JointHandL]->setMotorSpeed(isPositive);
		m_joints[e_JointHandR]->setMotorSpeed(isPositive);
		break;
	case e_JointTypeFoot:
		m_joints[e_JointFootL]->setMotorSpeed(isPositive);
		m_joints[e_JointFootR]->setMotorSpeed(isPositive);
		break;
	}
}

void Joints::initJointsParams()
{
	for (size_t i = 0; i < JOINTS_TYPE_COUNT - 2; ++i)
	{
		m_jointParams[i].negative_speed = JOINTS_PARAMS[i][0];
		m_jointParams[i].positive_speed = JOINTS_PARAMS[i][1];
		m_jointParams[i].left_angle = JOINTS_PARAMS[i][2];
		m_jointParams[i].mid_angle = JOINTS_PARAMS[i][3];
		m_jointParams[i].right_angle = JOINTS_PARAMS[i][4];
		m_jointParams[i].max_torque = JOINTS_PARAMS[i][5];
	}
}

void Joints::createPlayerJoint(size_t jointID, size_t jointTypeID, const Sprite* p0, 
							   const Sprite* p1, const f2Vec2& anchor)
{
 	b2RevoluteJointDef rjd;
 	rjd.Initialize(p0->getBody()->getBody(), p1->getBody()->getBody(), b2Vec2(anchor.x, anchor.y));
 	rjd.collideConnected = false;
 	if (jointTypeID == e_JointTypeHand || jointTypeID == e_JointTypeFoot)
 	{
 		rjd.enableLimit = false;
 		rjd.enableMotor = false;
 	}
 	else
 	{
  		rjd.enableLimit = true;
  		rjd.enableMotor = true;
 	}
 
 	if (m_joints[jointID])
 	{
 		if (m_joints[jointID]->m_joint) m_world->DestroyJoint(m_joints[jointID]->m_joint);
 	}
 	else
 	{
 		m_joints[jointID] = new Joint();	
 	}
 	m_joints[jointID]->m_joint = (b2RevoluteJoint*)m_world->CreateJoint(&rjd);
 	m_joints[jointID]->m_params = &m_jointParams[jointTypeID];
}

void Joints::doPlayerMotion(bool isLeftSide, bool turnRight)
{
	for (size_t i = 0; i < JOINTS_COUNT; ++i)
	{
		if (!m_joints[i] ||
			i == e_JointHandL || i == e_JointHandR || 
			i == e_JointFootL || i == e_JointFootR) 
			continue;

		m_joints[i]->setJointLimitesType(isLeftSide);
		const size_t index = isLeftSide ? 0 : 1;
		if (turnRight) m_joints[i]->setMotorSpeed(!JOINT_DIR_FLAG[index][i]);
		else m_joints[i]->setMotorSpeed(JOINT_DIR_FLAG[index][i]);
	}
}

//////////////////////////////////////////////////////////////////////////
// class Joints::Joint
//////////////////////////////////////////////////////////////////////////

Joints::Joint::Joint()
{
	m_joint = NULL;
	m_params = NULL;
	m_useLeftLimites = true;
}

void Joints::Joint::setMotorSpeed(bool positive)
{
	if (positive) m_joint->SetMotorSpeed(m_params->positive_speed);
	else m_joint->SetMotorSpeed(m_params->negative_speed);
}

void Joints::Joint::outputJointParams(std::ofstream& fout) const
{
	b2Vec2 anchor = m_joint->GetAnchorA();
	anchor *= SCALE_PHYSICS_TO_SCREEN;
	fout << m_params->negative_speed << " " << m_params->positive_speed << " "
		<< m_params->left_angle << " " << m_params->mid_angle << " " << m_params->right_angle << " "
		<< m_params->max_torque << " "
		<< anchor.x << " " << anchor.y << std::endl;
}

void Joints::Joint::setJointLimitesType(bool isLeft) 
{ 
	m_useLeftLimites = isLeft; 
}

void Joints::Joint::resetParams()
{
	m_joint->EnableLimit(m_params->enableLimit == 1);
	m_joint->EnableMotor(m_params->enableMotor == 1);

	float lower, upper;
	if (m_useLeftLimites)
	{
		lower = std::min(m_params->left_angle, m_params->mid_angle);
		upper = std::max(m_params->left_angle, m_params->mid_angle);
	}
	else
	{
		lower = std::min(m_params->mid_angle, m_params->right_angle);
		upper = std::max(m_params->mid_angle, m_params->right_angle);
	}
	lower *= PI;
	upper *= PI;

	m_joint->SetLimits(lower, upper);
	m_joint->SetMaxMotorTorque(m_params->max_torque);
}