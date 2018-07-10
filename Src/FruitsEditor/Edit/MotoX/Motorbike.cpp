#include "Motorbike.h"
#include "Utility.h"
#include "DriveControl.h"
#include "ActorSettings.h"
#include "../../Dataset/Sprite.h"
#include "../../Dataset/Layer.h"
#include "../../Dataset/Body.h"
#include "../../File/ActorMotionAdapter.h"
#include <Box2D/Box2D.h>

using namespace FEDITOR;
using namespace FEDITOR::MOTOX;

Motorbike::Motorbike(b2World* world, Layer* layer)
{
	m_world = world;
	m_layer = layer;

	m_frontWheel = m_backWheel = m_body = NULL;
	m_jointFront = m_jointBack = NULL;
}

Motorbike::~Motorbike()
{
	clear();
}

void Motorbike::loadFromAdapterFile(const ActorMotionAdapter& adapter)
{
	clear();

	loadPartsFromAdapterFile(adapter);
	loadJointsFromAdapterFile();

	m_frontWheel->getBody()->setAlive(true);
	m_backWheel->getBody()->setAlive(true);
	m_body->getBody()->setAlive(true);
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
			body->ApplyTorque(settings.angularImpulse);
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

	m_layer->deleteSprite(m_frontWheel);
	m_frontWheel = NULL;
	m_layer->deleteSprite(m_backWheel);
	m_backWheel = NULL;
	m_layer->deleteSprite(m_body);
	m_body = NULL;
}

void Motorbike::loadPartsFromAdapterFile(const ActorMotionAdapter& adapter)
{
	const ActorMotionAdapter::Part& frontWheel = adapter.m_parts[e_PartFrontWheel];
	m_frontWheel = new Sprite(SCALE_SCREEN_TO_PHYSICS);
	m_frontWheel->loadFromUnknownFile(frontWheel.filename);
	m_frontWheel->getBody()->setTransform(frontWheel.pos, frontWheel.angle);
	m_layer->addSprite(m_frontWheel);

	const ActorMotionAdapter::Part& backWheel = adapter.m_parts[e_PartBackWheel];
	m_backWheel = new Sprite(SCALE_SCREEN_TO_PHYSICS);
	m_backWheel->loadFromUnknownFile(backWheel.filename);
	m_backWheel->getBody()->setTransform(backWheel.pos, backWheel.angle);
	m_layer->addSprite(m_backWheel);

	const ActorMotionAdapter::Part& body = adapter.m_parts[e_PartMotorBody];
	m_body = new Sprite(SCALE_SCREEN_TO_PHYSICS);
	m_body->loadFromUnknownFile(body.filename);
	m_body->getBody()->setTransform(body.pos, body.angle);
	m_layer->addSprite(m_body);
}

void Motorbike::loadJointsFromAdapterFile()
{
	b2WheelJointDef jd;
	b2Vec2 axis(0.0f, 1.0f);

	b2Body *frontWheel = m_frontWheel->getBody()->getBody(),
		*backWheel = m_backWheel->getBody()->getBody(),
		*body = m_body->getBody()->getBody();

	jd.Initialize(body, backWheel, backWheel->GetPosition(), axis);
	jd.motorSpeed = 0.0f;
	jd.maxMotorTorque = 20;
	jd.enableMotor = true;
	jd.frequencyHz = 14;
	jd.dampingRatio = 7;
	m_jointBack = (b2WheelJoint*) m_world->CreateJoint(&jd);

	jd.Initialize(body, frontWheel, frontWheel->GetPosition(), axis);
	jd.motorSpeed = 0.0f;
	jd.maxMotorTorque = 10;
	jd.enableMotor = false;
	jd.frequencyHz = 14;
	jd.dampingRatio = 7;
	m_jointFront = (b2WheelJoint*) m_world->CreateJoint(&jd);
}