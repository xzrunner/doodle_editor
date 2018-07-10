#include "Player.h"
#include "Utility.h"
#include "DriveControl.h"
#include "../../Dataset/Body.h"
#include "../../Dataset/Joint.h"
#include "../../Dataset/Sprite.h"
#include "../../Dataset/Layer.h"
#include "../../File/ActorMotionAdapter.h"

using namespace FEDITOR;
using namespace FEDITOR::MOTOX;

const bool Player::JOINT_DIR_FLAG[][JOINTS_COUNT] = {
	{ true,	true, true, false, false, true, true, true, true,		true, true, true, true },
	{ false,true, true, false, false, true, true, false, false,		true, true, true, true }
};

Player::Player(b2World* world, Layer* layer, Sprite* motorbike)
{
	m_world = world;
	m_layer = layer;
	m_motorbike = motorbike;

	memset(m_parts, 0, sizeof(int) * PLAYER_PARTS_COUNT);
	memset(m_joints, 0, sizeof(int) * JOINTS_COUNT);

	m_state = e_PlayerStateMiddle;
}

Player::~Player()
{
	clear();
}

void Player::loadFromAdapterFile(const ActorMotionAdapter& adapter)
{
 	clear();
 
	loadPartsFromAdapterFile(adapter);
	loadJointsFromAdapterFile(adapter);
 
 	for (size_t i = 0; i < PLAYER_PARTS_COUNT; ++i)
 		m_parts[i]->getBody()->setAlive(true);
}

void Player::setCollisionFilter(const b2Filter& collision, const b2Filter& noCollision)
{
	for (size_t i = 0; i < PLAYER_PARTS_COUNT; ++i)
	{
		Body* body = m_parts[i]->getBody();
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
	{
		delete m_joints[i];
		m_joints[i] = NULL;
	}
	for (size_t i = 0; i < PLAYER_PARTS_COUNT; ++i)
	{
		m_layer->deleteSprite(m_parts[i]);
		m_parts[i] = NULL;
	}
}

void Player::loadPartsFromAdapterFile(const ActorMotionAdapter& adapter)
{
	for (size_t i = 0; i < PLAYER_PARTS_COUNT; ++i)
	{
		const ActorMotionAdapter::Part& src = adapter.m_parts[i];

		Sprite* part = new Sprite(SCALE_SCREEN_TO_PHYSICS);
		part->loadFromUnknownFile(src.filename);
		part->getBody()->setTransform(src.pos, src.angle);
		m_layer->addSprite(part);

		m_parts[i] = part;
	}
}

void Player::loadJointsFromAdapterFile(const ActorMotionAdapter& adapter)
{
	m_joints[e_JointNeck] = new Joint(m_world, adapter.m_joints[e_JointTypeNeck].params, adapter.m_joints[e_JointTypeNeck].anchor, 
		m_parts[e_PartBody]->getBody()->getBody(), m_parts[e_PartHead]->getBody()->getBody(), true, SCALE_SCREEN_TO_PHYSICS);
	m_joints[e_JointShoulderL] = new Joint(m_world, adapter.m_joints[e_JointTypeShoulder].params, adapter.m_joints[e_JointTypeShoulder].anchor, 
		m_parts[e_PartBody]->getBody()->getBody(), m_parts[e_PartBigArmLeft]->getBody()->getBody(), true, SCALE_SCREEN_TO_PHYSICS);
	m_joints[e_JointShoulderR] = new Joint(m_world, adapter.m_joints[e_JointTypeShoulder].params, adapter.m_joints[e_JointTypeShoulder].anchor, 
		m_parts[e_PartBody]->getBody()->getBody(), m_parts[e_PartBigArmRight]->getBody()->getBody(), true, SCALE_SCREEN_TO_PHYSICS);
	m_joints[e_JointElbowL] = new Joint(m_world, adapter.m_joints[e_JointTypeElbow].params, adapter.m_joints[e_JointTypeElbow].anchor, 
		m_parts[e_PartBigArmLeft]->getBody()->getBody(), m_parts[e_PartSmallArmLeft]->getBody()->getBody(), true, SCALE_SCREEN_TO_PHYSICS);
	m_joints[e_JointElbowR] = new Joint(m_world, adapter.m_joints[e_JointTypeElbow].params, adapter.m_joints[e_JointTypeElbow].anchor, 
		m_parts[e_PartBigArmRight]->getBody()->getBody(), m_parts[e_PartSmallArmRight]->getBody()->getBody(), true, SCALE_SCREEN_TO_PHYSICS);
	m_joints[e_JointHipL] = new Joint(m_world, adapter.m_joints[e_JointTypeHip].params, adapter.m_joints[e_JointTypeHip].anchor, 
		m_parts[e_PartBody]->getBody()->getBody(), m_parts[e_PartBigLegLeft]->getBody()->getBody(), true, SCALE_SCREEN_TO_PHYSICS);
	m_joints[e_JointHipR] = new Joint(m_world, adapter.m_joints[e_JointTypeHip].params, adapter.m_joints[e_JointTypeHip].anchor, 
		m_parts[e_PartBody]->getBody()->getBody(), m_parts[e_PartBigLegRight]->getBody()->getBody(), true, SCALE_SCREEN_TO_PHYSICS);
	m_joints[e_JointKneeL] = new Joint(m_world, adapter.m_joints[e_JointTypeKnee].params, adapter.m_joints[e_JointTypeKnee].anchor, 
		m_parts[e_PartBigLegLeft]->getBody()->getBody(), m_parts[e_PartSmallLegLeft]->getBody()->getBody(), true, SCALE_SCREEN_TO_PHYSICS);
	m_joints[e_JointKneeR] = new Joint(m_world, adapter.m_joints[e_JointTypeKnee].params, adapter.m_joints[e_JointTypeKnee].anchor, 
		m_parts[e_PartBigLegRight]->getBody()->getBody(), m_parts[e_PartSmallLegRight]->getBody()->getBody(), true, SCALE_SCREEN_TO_PHYSICS);

	m_joints[e_JointHandL] = new Joint(m_world, adapter.m_joints[e_JointTypeHand].params, adapter.m_joints[e_JointTypeHand].anchor, 
		m_parts[e_PartSmallArmLeft]->getBody()->getBody(), m_motorbike->getBody()->getBody(), false, SCALE_SCREEN_TO_PHYSICS);
	m_joints[e_JointHandR] = new Joint(m_world, adapter.m_joints[e_JointTypeHand].params, adapter.m_joints[e_JointTypeHand].anchor, 
		m_parts[e_PartSmallArmRight]->getBody()->getBody(), m_motorbike->getBody()->getBody(), false, SCALE_SCREEN_TO_PHYSICS);
	m_joints[e_JointFootL] = new Joint(m_world, adapter.m_joints[e_JointTypeFoot].params, adapter.m_joints[e_JointTypeFoot].anchor, 
		m_parts[e_PartSmallLegLeft]->getBody()->getBody(), m_motorbike->getBody()->getBody(), false, SCALE_SCREEN_TO_PHYSICS);
	m_joints[e_JointFootR] = new Joint(m_world, adapter.m_joints[e_JointTypeFoot].params, adapter.m_joints[e_JointTypeFoot].anchor, 
		m_parts[e_PartSmallLegRight]->getBody()->getBody(), m_motorbike->getBody()->getBody(), false, SCALE_SCREEN_TO_PHYSICS);
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