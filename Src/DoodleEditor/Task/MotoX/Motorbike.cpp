#include "Motorbike.h"
#include "LibraryActorItem.h"
#include "DriveControl.h"
#include "ActorSettings.h"
#include "Blackboard.h"
#include "TypesDef.h"

using namespace deditor::motox;

Motorbike::Motorbike(b2World* world)
	: m_bActive(false)
{
	m_world = world;

	m_frontWheel = m_backWheel = m_body = NULL;
	m_jointFront = m_jointBack = NULL;
}

Motorbike::~Motorbike()
{
	clear();
}

void Motorbike::loadParts(const LibraryActorItem& params)
{
	clear();

	m_frontWheel = params.m_parts[e_PartFrontWheel].loadBodySprite();
	m_backWheel = params.m_parts[e_PartBackWheel].loadBodySprite();
	m_body = params.m_parts[e_PartMotorBody].loadBodySprite();

	m_frontWheel->getBody()->getBody()->SetUserData(new int(ACTOR_ID));
	m_backWheel->getBody()->getBody()->SetUserData(new int(ACTOR_ID));
	m_body->getBody()->getBody()->SetUserData(new int(ACTOR_ID));

	m_frontWheel->getSymbol().reloadTexture();
	m_backWheel->getSymbol().reloadTexture();
	m_body->getSymbol().reloadTexture();
}

void Motorbike::loadJoints(const LibraryActorItem& params)
{
	if (m_bActive) return;

  	m_frontWheel->getBody()->setAlive(true);
  	m_backWheel->getBody()->setAlive(true);
  	m_body->getBody()->setAlive(true);

	b2WheelJointDef jd;
	b2Vec2 axis(0.0f, 1.0f);

	b2Body *body = m_body->getBody()->getBody(),
		*back = m_backWheel->getBody()->getBody(),
		*front = m_frontWheel->getBody()->getBody();

	jd.Initialize(body, back, back->GetPosition(), axis);
	jd.motorSpeed = 0.0f;
	jd.maxMotorTorque = 200;
	jd.enableMotor = true;
	jd.frequencyHz = 14;
	jd.dampingRatio = 7;
	m_jointBack = (b2WheelJoint*) m_world->CreateJoint(&jd);

	jd.Initialize(body, front, front->GetPosition(), axis);
	jd.motorSpeed = 0.0f;
	jd.maxMotorTorque = 100;
	jd.enableMotor = /*false*/true;
	jd.frequencyHz = 14;
	jd.dampingRatio = 7;
	m_jointFront = (b2WheelJoint*) m_world->CreateJoint(&jd);

	m_bActive = true;
}

void Motorbike::setCollisionFilter(const b2Filter& filter)
{
	m_frontWheel->getBody()->setCollisionFilter(filter);
	m_backWheel->getBody()->setCollisionFilter(filter);
	m_body->getBody()->setCollisionFilter(filter);
}

void Motorbike::driving(const DriveControl& control, ActorSettings& settings)
{
	b2Body* body = m_body->getBody()->getBody();

	switch (control.speed) 
	{
	case DriveControl::FORWARD:
		if (settings.lastTime == 0)
		{
			settings.lastTime = clock();
		}
		else
		{
			settings.currSpeed += (clock() - settings.lastTime) / 1000.0f * settings.accSpeed;
			if (settings.currSpeed > settings.maxSpeed) settings.currSpeed = settings.maxSpeed;
			settings.lastTime = clock();
		}

		m_jointBack->SetMotorSpeed(-settings.currSpeed);
		m_jointFront->SetMotorSpeed(-settings.currSpeed * Blackboard::frontWheelSpeedScale);

		// 		{
		// 			const float rad = m_parts[TYPE_BODY]->getBody()->GetAngle();
		// 			const f2Vec2 force = f2Math::rotateVector(b2Vec2(settings.maxSpeed * 0.01f, 0.0f), rad);
		// 			m_parts[TYPE_BODY]->getBody()->ApplyForceToCenter(b2Vec2(force.x, force.y));
		// 		}
		if (std::abs(body->GetAngularVelocity()) > 2.0f)
			body->SetAngularVelocity(0.0f);

//		std::cout << "speed up" << std::endl;

		break;
	case DriveControl::BACK:
		if (settings.lastTime == 0)
		{
			settings.lastTime = clock();
		}
		else
		{
			settings.currSpeed -= (clock() - settings.lastTime) / 1000.0f * settings.accSpeed * 0.5f;
			if (settings.currSpeed < 0) settings.currSpeed = 0;
			settings.lastTime = clock();
		}

		m_jointBack->SetMotorSpeed(-settings.currSpeed);
		m_jointFront->SetMotorSpeed(-settings.currSpeed * Blackboard::frontWheelSpeedScale);
		// 		if (std::abs(m_parts[TYPE_BODY]->getBody()->GetAngularVelocity()) > 2.0f)
		// 			m_parts[TYPE_BODY]->getBody()->SetAngularVelocity(0.0f);

//		std::cout << "back" << std::endl;

		break;
	case DriveControl::STOP:
		m_jointFront->SetMotorSpeed(0);
		m_jointBack->SetMotorSpeed(0);
		settings.currSpeed = 0;
		body->SetAngularVelocity(0.0f);
		break;
	}

	switch (control.tilt) 
	{
	case DriveControl::LEFT:
		if (std::abs(body->GetAngularVelocity()) < 6.0f)
			body->ApplyTorque(settings.angularImpulse - Blackboard::motoTorque * (1 + Blackboard::frontWheelTorqueScale));
		break;
	case DriveControl::MIDDLE:
		body->SetAngularVelocity(0);
		break;
	case DriveControl::RIGHT:
		if (std::abs(body->GetAngularVelocity()) < 6.0f)
			body->ApplyTorque(-settings.angularImpulse);
		break;
	}
}

void Motorbike::clear()
{
	if (m_jointFront)
	{
		m_world->DestroyJoint(m_jointFront);
		m_jointFront = NULL;
	}
	if (m_jointBack)
	{
		m_world->DestroyJoint(m_jointBack);
		m_jointBack = NULL;
	}

	if (m_frontWheel) 
		delete m_frontWheel, m_frontWheel = NULL;
	if (m_backWheel) 
		delete m_backWheel, m_backWheel = NULL;
	if (m_body) 
		delete m_body, m_body = NULL;
}