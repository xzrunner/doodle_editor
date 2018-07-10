#include "MotorbikeNew.h"
#include "DriveControl.h"
#include "ActorSettings.h"
#include "Blackboard.h"

#include "Task/Modeling/ResolveToB2.h"
#include "Task/Modeling/FileAdapter.h"
#include "Task/Modeling/BodyData.h"

using namespace deditor::motox;

MotorbikeNew::MotorbikeNew(b2World* world)
	: m_bActive(false)
	, m_world(world)
{
	m_frontWheel = m_backWheel = m_body = m_frontDamping = m_backDamping = NULL;
	m_frontJoint = NULL;
	m_backJoint = NULL;
}

MotorbikeNew::~MotorbikeNew()
{
	clear();
}

void MotorbikeNew::loadFromFile(const wxString& filepath)
{
	m_bActive = true;

	clear();

	deditor::modeling::FileApapter adapter;
	adapter.resolve(filepath);

	deditor::modeling::BodyData* frontWheel = adapter.queryBody(wxT("front_wheel"));
	deditor::modeling::BodyData* backWheel = adapter.queryBody(wxT("back_wheel"));
	deditor::modeling::BodyData* body = adapter.queryBody(wxT("body"));
	deditor::modeling::BodyData* frontDamping = adapter.queryBody(wxT("front_damping"));
	deditor::modeling::BodyData* backDamping = adapter.queryBody(wxT("back_damping"));

	m_frontWheel = frontWheel->m_sprite;
	m_backWheel = backWheel->m_sprite;
	m_body = body->m_sprite;
	m_frontDamping = frontDamping->m_sprite;
	m_backDamping = backDamping->m_sprite;

	m_delta = frontDamping->m_sprite->getAngle() - body->m_sprite->getAngle();
	m_offset = frontDamping->m_sprite->getPosition() - frontWheel->m_sprite->getPosition();

	m_frontWheel->loadBodyFromFile();
	m_backWheel->loadBodyFromFile();
	m_body->loadBodyFromFile();
	m_backDamping->loadBodyFromFile();

	std::map<deditor::modeling::BodyData*, b2Body*> bodyMap;
	bodyMap.insert(std::make_pair(frontWheel, m_frontWheel->getBody()->getBody()));
	bodyMap.insert(std::make_pair(backWheel, m_backWheel->getBody()->getBody()));
	bodyMap.insert(std::make_pair(body, m_body->getBody()->getBody()));
	bodyMap.insert(std::make_pair(backDamping, m_backDamping->getBody()->getBody()));

	deditor::modeling::JointData* frontJoint = adapter.queryJoint(wxT("front_joint"));
	m_frontJoint = static_cast<b2WheelJoint*>(deditor::modeling::ResolveToB2::createJoint(*frontJoint, m_world, bodyMap));

	deditor::modeling::JointData* backJoint = adapter.queryJoint(wxT("back_joint"));
//	m_backJoint = static_cast<b2RevoluteJoint*>(deditor::modeling::ResolveToB2::createJoint(*backJoint, m_world, bodyMap));
	m_backJoint = static_cast<b2WheelJoint*>(deditor::modeling::ResolveToB2::createJoint(*backJoint, m_world, bodyMap));

	deditor::modeling::JointData* joint3 = adapter.queryJoint(wxT("joint3"));
	deditor::modeling::ResolveToB2::createJoint(*joint3, m_world, bodyMap);

	deditor::modeling::JointData* joint4 = adapter.queryJoint(wxT("joint4"));
	deditor::modeling::ResolveToB2::createJoint(*joint4, m_world, bodyMap);
}

void MotorbikeNew::active()
{
	m_frontWheel->getBody()->setAlive(true);
	m_backWheel->getBody()->setAlive(true);
	m_body->getBody()->setAlive(true);
	m_backDamping->getBody()->setAlive(true);
}

void MotorbikeNew::setCollisionFilter(const b2Filter& filter)
{
	m_frontWheel->getBody()->setCollisionFilter(filter);
	m_backWheel->getBody()->setCollisionFilter(filter);
	m_body->getBody()->setCollisionFilter(filter);
	m_backDamping->getBody()->setCollisionFilter(filter);
}

void MotorbikeNew::driving(const DriveControl& control, ActorSettings& settings)
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

		m_backJoint->SetMotorSpeed(-settings.currSpeed);
		m_frontJoint->SetMotorSpeed(-settings.currSpeed * Blackboard::frontWheelSpeedScale);

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

		m_backJoint->SetMotorSpeed(-settings.currSpeed);
		m_frontJoint->SetMotorSpeed(-settings.currSpeed * Blackboard::frontWheelSpeedScale);
		// 		if (std::abs(m_parts[TYPE_BODY]->getBody()->GetAngularVelocity()) > 2.0f)
		// 			m_parts[TYPE_BODY]->getBody()->SetAngularVelocity(0.0f);

		//		std::cout << "back" << std::endl;

		break;
	case DriveControl::STOP:
		m_frontJoint->SetMotorSpeed(0);
		m_backJoint->SetMotorSpeed(0);
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

void MotorbikeNew::updateFrontDamping()
{
	const float angle = m_body->getAngle() + m_delta;
	const f2Vec2 position = m_frontWheel->getPosition() + f2Math::rotateVector(m_offset, m_body->getAngle());

	m_frontDamping->setTransform(position, angle);
}

void MotorbikeNew::clear()
{
	if (m_frontJoint)
	{
		m_world->DestroyJoint(m_frontJoint);
		m_frontJoint = NULL;
	}
	if (m_backJoint)
	{
		m_world->DestroyJoint(m_backJoint);
		m_backJoint = NULL;
	}

	delete m_frontWheel, m_frontWheel = NULL;
	delete m_backWheel, m_backWheel = NULL;
	delete m_body, m_body = NULL;
	delete m_frontDamping, m_frontDamping = NULL;
	delete m_backDamping, m_backDamping = NULL;
}