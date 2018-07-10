#include "Actor.h"
#include "ActorDefs.h"
#include "Motorbike.h"
#include "Player.h"
#include "DriveControl.h"
#include "../KeyboardTest.h"
#include "../../Dataset/Body.h"
#include "../../Dataset/Sprite.h"
#include "../../File/ActorMotionAdapter.h"
#include <Box2D/Box2D.h>

using namespace FEDITOR;
using namespace FEDITOR::MOTOX;

Actor::Actor(b2World* world, Layer* layer, const std::string& filename)
{
	m_bike = NULL;
	m_player = NULL;

	ActorMotionAdapter adapter;
	adapter.load(filename);
	m_bike = new Motorbike(world, layer);
	m_bike->loadFromAdapterFile(adapter);
	m_player = new Player(world, layer, m_bike->getBody());
	m_player->loadFromAdapterFile(adapter);

	setCollisionFilter();
}

Actor::~Actor()
{
	delete m_player;
	delete m_bike;
}

void Actor::driving()
{
	DriveControl control;
	control.tilt = DriveControl::MIDDLE;
	control.speed = DriveControl::BACK;

	if (KeyBoardTest::isLeftPress())
		control.tilt = DriveControl::LEFT;
	if (KeyBoardTest::isRightPress())
		control.tilt = DriveControl::RIGHT;

	if (KeyBoardTest::isUpPress())
		control.speed = DriveControl::FORWARD;
	if (KeyBoardTest::isDownPress())
		control.speed = DriveControl::STOP;

	if (m_bike) m_bike->driving(control, m_settings);
	if (m_player) m_player->driving(control, m_settings);
}

void Actor::setValue(int type, float val)
{
	switch (type)
	{
	case e_SetWheelFriction:
		if (m_bike) m_bike->m_backWheel->getBody()->setFriction(val);
		if (m_bike) m_bike->m_frontWheel->getBody()->setFriction(val);
		break;
	case e_SetMotoDensity:
		if (m_bike) m_bike->m_frontWheel->getBody()->setDensity(val);
		//		m_car->m_parts[Car::TYPE_BACK_WHEEL]->setDensity(val);
		//		m_car->m_parts[Car::TYPE_BODY]->setDensity(val);
		if (m_bike) m_bike->m_body->getBody()->getBody()->GetFixtureList()->GetNext()->SetDensity(val);
		break;
	case e_SetPlayerDensity:
		if (m_player)
		{
			for (size_t i = 0; i < PLAYER_PARTS_COUNT; ++i)
				m_player->m_parts[i]->getBody()->setDensity(val);
		}
		break;
	case e_SetSpeed:
		m_settings.maxSpeed = val;
		break;
	case e_SetAcc:
		m_settings.accSpeed = val;
		break;
	case e_SetTorque:
		m_settings.angularImpulse = val;
		break;
// 	case e_SetDamping:
// 		if (m_bike) m_bike->m_jointFront->SetSpringDampingRatio(val);
// 		if (m_bike) m_bike->m_jointBack->SetSpringDampingRatio(val);
// 		break;
// 	case e_SetHz:
// 		if (m_bike) m_bike->m_jointFront->SetSpringFrequencyHz(val);
// 		if (m_bike) m_bike->m_jointBack->SetSpringFrequencyHz(val);
// 		break;
// 	case e_SetMaxMotorTorque:
// 		if (m_bike) m_bike->m_jointBack->SetMaxMotorTorque(val);
// 		break;
	}
}

void Actor::translate(const f2Vec2& offset)
{
	if (m_player)
	{
		for (size_t i = 0; i < PLAYER_PARTS_COUNT; ++i)
		{
			b2Body* body = m_player->m_parts[i]->getBody()->getBody();
			b2Vec2 p(body->GetPosition());
			p.x += offset.x;
			p.y += offset.y;
			body->SetTransform(p, body->GetAngle());
		}
	}
	if (m_bike)
	{
		{
			b2Body* body = m_bike->m_frontWheel->getBody()->getBody();
			b2Vec2 p(body->GetPosition());
			p.x += offset.x;
			p.y += offset.y;
			body->SetTransform(p, body->GetAngle());
		}
		{
			b2Body* body = m_bike->m_backWheel->getBody()->getBody();
			b2Vec2 p(body->GetPosition());
			p.x += offset.x;
			p.y += offset.y;
			body->SetTransform(p, body->GetAngle());
		}
		{
			b2Body* body = m_bike->m_body->getBody()->getBody();
			b2Vec2 p(body->GetPosition());
			p.x += offset.x;
			p.y += offset.y;
			body->SetTransform(p, body->GetAngle());
		}
	}
}

f2Vec2 Actor::getCenterPos() const
{
	f2Vec2 pos;
	if (m_bike)
	{
		b2Vec2 p = m_bike->getBody()->getBody()->getBody()->GetPosition();
		pos.x = p.x;
		pos.y = p.y;
	}
	else
	{
		pos.x = 4.0f;
		pos.y = 2.4f;
	}
	return pos;
}

void Actor::getCollisionFilterSetting(b2Filter& motoFilter, b2Filter& playerCollFilter, 
									  b2Filter& playerNoCollFilter)
{
	motoFilter.categoryBits = MOTO_CATEGORY;
	motoFilter.maskBits = MOTO_MASK;
	motoFilter.groupIndex = MOTO_GROUP;

	playerCollFilter.maskBits = DEFAULT_MASK;
	playerNoCollFilter.categoryBits = PLAYER_CATEGORY;
	playerNoCollFilter.maskBits = PLAYER_MASK;
	playerCollFilter.groupIndex = playerNoCollFilter.groupIndex = PLAYER_GROUP;
}

void Actor::setCollisionFilter()
{
	b2Filter motoFilter, playerCollFilter, playerNoCollFilter;
	getCollisionFilterSetting(motoFilter, playerCollFilter, playerNoCollFilter);

	if (m_bike) m_bike->setCollisionFilter(motoFilter);
	if (m_player) m_player->setCollisionFilter(playerCollFilter, playerNoCollFilter);
}