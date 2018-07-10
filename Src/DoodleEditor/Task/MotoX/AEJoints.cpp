#include "AEJoints.h"
#include "AEParts.h"
#include "AEJointsCMPT.h"
#include "LibraryActorItem.h"

using namespace deditor::motox;

const float AEJoints::JOINTS_PARAMS[][7] = {
	{	-2, 	2,		0.15f,		0.02f,		0.15f,		0.02f,		50	},
	{	-3,		3,		0.0f,		0.25f,		-0.32f,		0.25f,		50	},
	{	-5,		5,		-0.3f,		-0.036f,	-0.036f,	0.28f,		50	},
	{	-3,		3,		-0.036f,	-0.027f,	-0.4f,		-0.036f,	50	},
	{	-5,		5,		0.03f,		0.38f,		0.033f,		0.38f,		50	}
};

const bool AEJoints::JOINT_DIR_FLAG[][JOINTS_COUNT] = {
	{ true,	true, true, false, false, true, true, true, true,		true, true, true, true },
	{ false,true, true, false, false, true, true, false, false,		true, true, true, true }
};

AEJoints::AEJoints(b2World* world, LibraryActorItem& params, AEParts& parts)
	: m_params(params), m_parts(parts)
{
	m_world = world;

	memset(m_joints, 0, sizeof(int) * JOINTS_COUNT);
	m_frontWheelJoint = m_backWheelJoint = NULL;

	loadFromParams();

	m_state = e_PlayerStateMiddle;
}

void AEJoints::initFromParams()
{
	for (size_t i = 0; i < JOINTS_TYPE_COUNT; ++i)
	{
		if (i == 0)
		{
			if (!m_joints[0]) m_joints[0] = new Joint;
		}
		else
		{
			if (!m_joints[i * 2 - 1]) m_joints[i * 2 - 1] = new Joint;
			if (!m_joints[i * 2]) m_joints[i * 2] = new Joint;
		}
	}
}

void AEJoints::createJoint(size_t jointType, const f2Vec2& anchor)
{
	switch (jointType)
	{
	case e_JointTypeNeck:
		createPlayerJoint(e_JointNeck, e_JointTypeNeck, 
			m_parts.getPart(e_PartBody), m_parts.getPart(e_PartHead), anchor);
		break;
	case e_JointTypeShoulder:
		createPlayerJoint(e_JointShoulderL, e_JointTypeShoulder, 
			m_parts.getPart(e_PartBody), m_parts.getPart(e_PartBigArmLeft), anchor);
		createPlayerJoint(e_JointShoulderR, e_JointTypeShoulder, 
			m_parts.getPart(e_PartBody), m_parts.getPart(e_PartBigArmRight), anchor);
		break;
	case e_JointTypeElbow:
		createPlayerJoint(e_JointElbowL, e_JointTypeElbow, 
			m_parts.getPart(e_PartBigArmLeft), m_parts.getPart(e_PartSmallArmLeft), anchor);
		createPlayerJoint(e_JointElbowR, e_JointTypeElbow, 
			m_parts.getPart(e_PartBigArmRight), m_parts.getPart(e_PartSmallArmRight), anchor);
		break;
	case e_JointTypeHip:
		createPlayerJoint(e_JointHipL, e_JointTypeHip, 
			m_parts.getPart(e_PartBody), m_parts.getPart(e_PartBigLegLeft), anchor);
		createPlayerJoint(e_JointHipR, e_JointTypeHip, 
			m_parts.getPart(e_PartBody), m_parts.getPart(e_PartBigLegRight), anchor);
		break;
	case e_JointTypeKnee:
		createPlayerJoint(e_JointKneeL, e_JointTypeKnee, 
			m_parts.getPart(e_PartBigLegLeft), m_parts.getPart(e_PartSmallLegLeft), anchor);
		createPlayerJoint(e_JointKneeR, e_JointTypeKnee, 
			m_parts.getPart(e_PartBigLegRight), m_parts.getPart(e_PartSmallLegRight), anchor);
		break;
// 	case e_JointTypeHand:
// 		createPlayerJoint(e_JointHandL, e_JointTypeHand, 
// 			m_parts.getPart(e_PartSmallArmLeft), m_parts.getPart(e_PartMotorBody), anchor);
// 		createPlayerJoint(e_JointHandR, e_JointTypeHand, 
// 			m_parts.getPart(e_PartSmallArmRight), m_parts.getPart(e_PartMotorBody), anchor);
// 		break;
// 	case e_JointTypeFoot:
// 		createPlayerJoint(e_JointFootL, e_JointTypeFoot, 
// 			m_parts.getPart(e_PartSmallLegLeft), m_parts.getPart(e_PartMotorBody), anchor);
// 		createPlayerJoint(e_JointFootR, e_JointTypeFoot, 
// 			m_parts.getPart(e_PartSmallLegRight), m_parts.getPart(e_PartMotorBody), anchor);
// 		break;
	}
}

void AEJoints::createWheelsJoint()
{
	if (m_frontWheelJoint) m_world->DestroyJoint(m_frontWheelJoint);
	if (m_backWheelJoint) m_world->DestroyJoint(m_backWheelJoint);

	b2WheelJointDef jd;
	b2Vec2 axis(0.0f, 1.0f);

	b2Body *body = m_parts.getPart(e_PartMotorBody)->getBody()->getBody(),
		*back = m_parts.getPart(e_PartBackWheel)->getBody()->getBody(),
		*front = m_parts.getPart(e_PartFrontWheel)->getBody()->getBody();

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

void AEJoints::createAllJoints()
{
	for (size_t i = 0; i < JOINTS_TYPE_COUNT; ++i)
		createJoint(i, m_params.m_joints[i].anchor);
	createWheelsJoint();
}

void AEJoints::setJointParams(size_t jointType)
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

void AEJoints::setJointMotion(PLAYER_MOTION dir)
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

const LibraryActorItem::JointDef& AEJoints::getJointParams(size_t jointType) const
{
	return m_params.m_joints[jointType];
}

void AEJoints::onDraw() const
{
	for (size_t i = 0; i < JOINTS_TYPE_COUNT; ++i)
	{
		const f2Vec2& pos = m_params.m_joints[i].anchor;
		wxgui::PrimitiveDraw::drawSquare(pos, 1, f2Colorf(1.0f, 0.0f, 0.0f));
		wxgui::PrimitiveDraw::drawRing(pos, 2, f2Colorf(0.0f, 1.0f, 0.0f));
	}
}

void AEJoints::clear()
{
	for (size_t i = 0; i < JOINTS_COUNT; ++i)
		delete m_joints[i], m_joints[i] = NULL;
	if (m_frontWheelJoint) 
		m_world->DestroyJoint(m_frontWheelJoint), m_frontWheelJoint = NULL;
	if (m_backWheelJoint) 
		m_world->DestroyJoint(m_backWheelJoint), m_backWheelJoint = NULL;
}

void AEJoints::setJointMotion(size_t jointType, bool isPositive)
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

void AEJoints::loadFromParams()
{
	bool already = true;
	for (size_t i = 0; i < JOINTS_TYPE_COUNT - 2; ++i)
	{
		if (m_params.m_joints[i].anchor.isValid())
			continue;

		already = false;
		m_params.m_joints[i].negative_speed = JOINTS_PARAMS[i][0];
		m_params.m_joints[i].positive_speed = JOINTS_PARAMS[i][1];
		m_params.m_joints[i].left_angle_small = JOINTS_PARAMS[i][2];
		m_params.m_joints[i].left_angle_large = JOINTS_PARAMS[i][3];
		m_params.m_joints[i].right_angle_small = JOINTS_PARAMS[i][4];
		m_params.m_joints[i].right_angle_large = JOINTS_PARAMS[i][5];
		m_params.m_joints[i].max_torque = JOINTS_PARAMS[i][6];
	}

	if (already)
	{
		createAllJoints();
	}
}

void AEJoints::createPlayerJoint(size_t jointID, size_t jointTypeID, const wxgui::ISprite* p0, 
								 const wxgui::ISprite* p1, const f2Vec2& anchor)
{
	if (!p0 || !p1 || !p0->getBody() || !p1->getBody()) return;

	b2RevoluteJointDef rjd;
	rjd.Initialize(p0->getBody()->getBody(), p1->getBody()->getBody(), b2Vec2(anchor.x / BOX2D_SCALE_FACTOR, anchor.y / BOX2D_SCALE_FACTOR));
	rjd.collideConnected = false;
	if (jointTypeID == e_JointTypeHand || jointTypeID == e_JointTypeFoot)
	{
		rjd.enableLimit = false;
		rjd.enableMotor = false;
		m_params.m_joints[jointTypeID].enableLimit = false;
		m_params.m_joints[jointTypeID].enableMotor = false;
	}
 	else
 	{
 		rjd.enableLimit = true;
 		rjd.enableMotor = true;
		m_params.m_joints[jointTypeID].enableLimit = true;
		m_params.m_joints[jointTypeID].enableMotor = true;
 	}
	m_params.m_joints[jointTypeID].anchor = anchor;

	if (m_joints[jointID])
	{
		if (m_joints[jointID]->m_joint) m_world->DestroyJoint(m_joints[jointID]->m_joint);
	}
	else
	{
		m_joints[jointID] = new Joint();	
	}
	m_joints[jointID]->m_joint = (b2RevoluteJoint*)m_world->CreateJoint(&rjd);
	m_joints[jointID]->m_params = &m_params.m_joints[jointTypeID];
	m_joints[jointID]->resetParams();
}

void AEJoints::doPlayerMotion(bool isLeftSide, bool turnRight)
{
	for (size_t i = 0; i < JOINTS_COUNT; ++i)
	{
		if (!m_joints[i] ||
			i == e_JointHandL || i == e_JointHandR || 
			i == e_JointFootL || i == e_JointFootR) 
			continue;

		m_joints[i]->setJointLimites(isLeftSide);
		const size_t index = isLeftSide ? 0 : 1;
		if (turnRight) m_joints[i]->setMotorSpeed(!JOINT_DIR_FLAG[index][i]);
		else m_joints[i]->setMotorSpeed(JOINT_DIR_FLAG[index][i]);
	}
}

//////////////////////////////////////////////////////////////////////////
// class AEJoints::Joint
//////////////////////////////////////////////////////////////////////////

AEJoints::Joint::Joint()
{
	m_joint = NULL;
	m_params = NULL;
	m_useLeftLimites = true;
}

void AEJoints::Joint::setMotorSpeed(bool positive)
{
	if (positive) m_joint->SetMotorSpeed(m_params->positive_speed);
	else m_joint->SetMotorSpeed(m_params->negative_speed);
}

void AEJoints::Joint::setJointLimites(bool isLeft) 
{ 
	m_useLeftLimites = isLeft; 

	float lower, upper;
	if (m_useLeftLimites)
	{
		lower = std::min(m_params->left_angle_small, m_params->left_angle_large);
		upper = std::max(m_params->left_angle_small, m_params->left_angle_large);
	}
	else
	{
		lower = std::min(m_params->right_angle_small, m_params->right_angle_large);
		upper = std::max(m_params->right_angle_small, m_params->right_angle_large);
	}
	lower *= PI;
	upper *= PI;

	m_joint->SetLimits(lower, upper);
}

void AEJoints::Joint::resetParams()
{
	m_joint->EnableLimit(m_params->enableLimit);
	m_joint->EnableMotor(m_params->enableMotor);

	float lower, upper;
	if (m_useLeftLimites)
	{
 		lower = std::min(m_params->left_angle_small, m_params->left_angle_large);
 		upper = std::max(m_params->left_angle_small, m_params->left_angle_large);
	}
	else
	{
 		lower = std::min(m_params->right_angle_small, m_params->right_angle_large);
 		upper = std::max(m_params->right_angle_small, m_params->right_angle_large);
	}
	lower *= PI;
	upper *= PI;

	m_joint->SetLimits(lower, upper);
	m_joint->SetMaxMotorTorque(m_params->max_torque);
}