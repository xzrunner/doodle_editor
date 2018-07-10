#include "Motorbike.h"
#include "DriveControl.h"
#include "ActorSettings.h"

#include "Tools/Sprite.h"

using namespace motox;

Motorbike::Motorbike(d2d::Context* pContext)
	: m_pContext(pContext)
	, m_frontJoint(NULL)
	, m_backJoint(NULL)
	, m_joint3(NULL)
	, m_joint4(NULL)
{
	m_backWheel = new Sprite;
	m_frontWheel = new Sprite;
	m_body = new Sprite;
	m_backDamping = new Sprite;
	m_frontDamping = new Sprite;
}

Motorbike::~Motorbike()
{
	clear();
}

void Motorbike::update()
{
	m_frontWheel->update();
	m_backWheel->update();
	m_body->update();

	updateDamping();
}

void Motorbike::driving(const DriveControl& control, ActorSettings& settings)
{
//	d2d::Log::debug("speed: %f", settings.currSpeed);

#ifdef D2D_WINDOWS
	const float maxAngularVelocity = 3.0f;
#elif defined D2D_ANDROID_NATIVE
	const float maxAngularVelocity = 1.0f;
#elif defined D2D_ANDROID_JNI
	const float maxAngularVelocity = 1.0f;
#endif

	b2Body* body = m_body->m_physics->getBody();

	switch (control.speed) 
	{
	case DriveControl::FORWARD:
		if (settings.lastTime == 0)
		{
			settings.lastTime = m_pContext->m_timeService->now();
		}
		else
		{
			settings.currSpeed += (m_pContext->m_timeService->now() - settings.lastTime) * settings.accSpeed;
 			if (settings.currSpeed > settings.maxSpeed) settings.currSpeed = settings.maxSpeed;
			settings.lastTime = m_pContext->m_timeService->now();
		}

		m_backJoint->SetMotorSpeed(-settings.currSpeed);
		m_frontJoint->SetMotorSpeed(-settings.currSpeed);

		// 		{
		// 			const float rad = m_parts[TYPE_BODY]->getBody()->GetAngle();
		// 			const f2Vec2 force = f2Math::rotateVector(b2Vec2(settings.maxSpeed * 0.01f, 0.0f), rad);
		// 			m_parts[TYPE_BODY]->getBody()->ApplyForceToCenter(b2Vec2(force.x, force.y));
		// 		}
		if (std::abs(body->GetAngularVelocity()) > maxAngularVelocity)
			body->SetAngularVelocity(0.0f);

//		std::cout << "speed up" << std::endl;

		break;
	case DriveControl::BACK:
 		if (settings.lastTime == 0)
 		{
 			settings.lastTime = m_pContext->m_timeService->now();
 		}
 		else
 		{
 			settings.currSpeed -= (m_pContext->m_timeService->now() - settings.lastTime) * settings.accSpeed * 0.5f;
 			if (settings.currSpeed < 0) settings.currSpeed = 0;
 			settings.lastTime = m_pContext->m_timeService->now();
 		}
 
 		m_backJoint->SetMotorSpeed(-settings.currSpeed);
		m_frontJoint->SetMotorSpeed(-settings.currSpeed);
		// 		if (std::abs(m_parts[TYPE_BODY]->getBody()->GetAngularVelocity()) > maxAngularVelocity)
		// 			m_parts[TYPE_BODY]->getBody()->SetAngularVelocity(0.0f);

//		std::cout << "back" << std::endl;

		break;
	case DriveControl::STOP:
		m_backJoint->SetMotorSpeed(0);
		m_frontJoint->SetMotorSpeed(0);
		settings.currSpeed = 0;
		body->SetAngularVelocity(0.0f);
		break;
	}

	switch (control.tilt) 
	{
	case DriveControl::LEFT:
 		if (std::abs(body->GetAngularVelocity()) < 4.0f)
 			body->ApplyTorque(settings.angularImpulse - g_motoTorque * 2);
		break;
	case DriveControl::MIDDLE:
//		body->SetAngularVelocity(0);
		body->SetAngularVelocity(body->GetAngularVelocity() * 0.999f);
		break;
	case DriveControl::RIGHT:
 		if (std::abs(body->GetAngularVelocity()) < 4.0f)
 			body->ApplyTorque(-(settings.angularImpulse - g_motoTorque * 1.2f));
		break;
	}
}

void Motorbike::clear()
{
	b2World* world = m_pContext->m_physicsService->getWorld();

	if (m_frontJoint)
	{
		world->DestroyJoint(m_frontJoint);
		m_frontJoint = NULL;
	}
	if (m_backJoint)
	{
		world->DestroyJoint(m_backJoint);
		m_backJoint = NULL;
	}
	if (m_joint3)
	{
		world->DestroyJoint(m_joint3);
		m_joint3 = NULL;
	}
	if (m_joint4)
	{
		world->DestroyJoint(m_joint4);
		m_joint4 = NULL;
	}

	delete m_backWheel, m_backWheel = NULL;
	delete m_frontWheel, m_frontWheel = NULL;
	delete m_body, m_body = NULL;
	delete m_backDamping, m_backDamping = NULL;
	delete m_frontDamping, m_frontDamping = NULL;
}

void Motorbike::updateDamping()
{
	{
		const float angle = m_body->m_graphics->getAngle() + m_frontDelta;

		d2d::Vector angleOffset;
		d2d::rotateVector(m_frontOffset, m_body->m_graphics->getAngle(), angleOffset);
		d2d::Vector position = m_frontWheel->m_graphics->getLocation() + angleOffset;

		m_frontDamping->m_graphics->setTransform(position, angle);
	}
	{
 		const d2d::Vector& left = m_backWheel->m_graphics->getLocation();
 
 		d2d::Vector right;
 		d2d::rotateVector(m_backBodyLocal, m_body->m_graphics->getAngle(), right);
 		right += m_body->m_graphics->getLocation();
 
 		float angle = d2d::getLineAngle(left, right);
 
 		d2d::Vector position;
 		d2d::rotateVector(m_backDampingLocal, angle, position);
 		position = m_backWheel->m_graphics->getLocation() - position;
 
 		m_backDamping->m_graphics->setTransform(position, angle);
	}
}