#include "Player.h"
#include "DriveControl.h"
#include "TypesDef.h"

using namespace deditor::motox;

const bool Player::JOINT_DIR_FLAG[][JOINTS_COUNT] = {
	{ true,	true, true, false, false, true, true, true, true,		true, true, true, true },
	{ false,true, true, false, false, true, true, false, false,		true, true, true, true }
};

Player::Player(b2World* world, wxgui::ISprite* motorbike)
	: m_bActive(false)
{
	m_world = world;
	m_motorbike = motorbike;

	memset(m_parts, 0, sizeof(int) * PLAYER_PARTS_COUNT);
	memset(m_joints, 0, sizeof(int) * JOINTS_COUNT);

	m_state = e_PlayerStateMiddle;
}

Player::~Player()
{
	clear();
}

void Player::loadParts(const LibraryActorItem& params)
{
	clear();

	for (size_t i = 0; i < PLAYER_PARTS_COUNT; ++i)
	{
		m_parts[i] = params.m_parts[i].loadBodySprite();
		m_parts[i]->getBody()->getBody()->SetUserData(new int(ACTOR_ID));
		m_parts[i]->getSymbol().reloadTexture();
	}
}

void Player::loadJoints(const LibraryActorItem& params)
{
	if (m_bActive) return;

 	for (size_t i = 0; i < PLAYER_PARTS_COUNT; ++i)
 		m_parts[i]->getBody()->setAlive(true);

	createJoint(params.m_joints, e_JointNeck, e_JointTypeNeck, e_PartBody, e_PartHead);

	createJoint(params.m_joints, e_JointShoulderL, e_JointTypeShoulder, e_PartBody, e_PartBigArmLeft);
	createJoint(params.m_joints, e_JointShoulderR, e_JointTypeShoulder, e_PartBody, e_PartBigArmRight);

	createJoint(params.m_joints, e_JointElbowL, e_JointTypeElbow, e_PartBigArmLeft, e_PartSmallArmLeft);
	createJoint(params.m_joints, e_JointElbowR, e_JointTypeElbow, e_PartBigArmRight, e_PartSmallArmRight);

	createJoint(params.m_joints, e_JointHipL, e_JointTypeHip, e_PartBody, e_PartBigLegLeft);
	createJoint(params.m_joints, e_JointHipR, e_JointTypeHip, e_PartBody, e_PartBigLegRight);

	createJoint(params.m_joints, e_JointKneeL, e_JointTypeKnee, e_PartBigLegLeft, e_PartSmallLegLeft);
	createJoint(params.m_joints, e_JointKneeR, e_JointTypeKnee, e_PartBigLegRight, e_PartSmallLegRight);

	createJointWithMotorbike(params.m_joints, e_JointHandL, e_JointTypeHand, e_PartSmallArmLeft);
	createJointWithMotorbike(params.m_joints, e_JointHandR, e_JointTypeHand, e_PartSmallArmRight);

 	createJointWithMotorbike(params.m_joints, e_JointFootL, e_JointTypeFoot, e_PartSmallLegLeft);
 	createJointWithMotorbike(params.m_joints, e_JointFootR, e_JointTypeFoot, e_PartSmallLegRight);

	m_bActive = true;
}

void Player::setCollisionFilter(const b2Filter& collision, const b2Filter& noCollision)
{
	for (size_t i = 0; i < PLAYER_PARTS_COUNT; ++i)
	{
		wxgui::IBody* body = m_parts[i]->getBody();
		if (i == e_PartHead || i == e_PartBody)
			body->setCollisionFilter(collision);
		else
			body->setCollisionFilter(noCollision);
	}
}

void Player::driving(const DriveControl& control, ActorSettings& settings)
{
	switch (control.tilt) {
	case DriveControl::LEFT:
		if (m_state == e_PlayerStateMiddle) 
		{
			doPlayerMotion(true, false);
			m_state = e_PlayerStateLeft;
		}
		break;
	case DriveControl::MIDDLE:
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
	case DriveControl::RIGHT:
		if (m_state == e_PlayerStateMiddle) 
		{
			doPlayerMotion(false, true);
			m_state = e_PlayerStateRight;
		}
		break;
	}
}

void Player::clear()
{
	for (size_t i = 0; i < JOINTS_COUNT; ++i)
		delete m_joints[i], m_joints[i] = NULL;
	for (size_t i = 0; i < PLAYER_PARTS_COUNT; ++i)
		delete m_parts[i], m_parts[i] = NULL;
}

void Player::createJoint(const LibraryActorItem::JointDef* joints, int jointID, int jointTypeID, int part0, int part1)
{
	m_joints[jointID] = new wxgui::Joint(m_world, joints[jointTypeID], joints[jointTypeID].anchor,
		m_parts[part0]->getBody()->getBody(), m_parts[part1]->getBody()->getBody(), true, 1.0f);
}

void Player::createJointWithMotorbike(const LibraryActorItem::JointDef* joints, int jointID, int jointTypeID, int part)
{
	m_joints[jointID] = new wxgui::Joint(m_world, joints[jointTypeID], joints[jointTypeID].anchor, 
		m_parts[part]->getBody()->getBody(), m_motorbike->getBody()->getBody(), false, 1.0f);
}

void Player::doPlayerMotion(bool isLeftSide, bool turnRight)
{
	for (size_t i = 0; i < JOINTS_COUNT; ++i)
	{
		if (i == e_JointHandL || i == e_JointHandR || 
			i == e_JointFootL || i == e_JointFootR) 
			continue;

		m_joints[i]->setAngleLimit(isLeftSide);
		const size_t index = isLeftSide ? 0 : 1;
		if (turnRight) m_joints[i]->setMotorSpeed(!JOINT_DIR_FLAG[index][i]);
		else m_joints[i]->setMotorSpeed(JOINT_DIR_FLAG[index][i]);
	}
}