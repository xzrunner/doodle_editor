#include "Player.h"
#include "DriveControl.h"

using namespace motox;

const bool Player::JOINT_DIR_FLAG[][JOINTS_COUNT] = {
	{ true,	true, true, false, false, true, true, true, true,		true, true, true, true },
	{ false,true, true, false, false, true, true, false, false,		true, true, true, true }
};

Player::Player(b2World* world)
	: m_world(world)
	, m_motorbike(NULL)
	, m_state(e_PlayerStateMiddle)
{
	for (size_t i = 0; i < PLAYER_PARTS_COUNT; ++i)
		m_parts[i] = new Sprite;
	memset(m_joints, 0, sizeof(int) * JOINTS_COUNT);
}

Player::~Player()
{
	clear();
}

void Player::update()
{
	for (size_t i = 0; i < PLAYER_PARTS_COUNT; ++i)
		m_parts[i]->update();
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