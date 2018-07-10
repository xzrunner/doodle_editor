#include "PhysicsBody.h"

using namespace d2d;

PhysicsBody::PhysicsBody(b2World* world)
	: m_world(world)
	, m_body(NULL)
{
}

PhysicsBody::~PhysicsBody()
{
	if (m_body)
	{
		m_world->DestroyBody(m_body);
		m_body = NULL;
	}
}

void PhysicsBody::setDensity(float density)
{
	for (b2Fixture* f = m_body->GetFixtureList(); f; f = f->GetNext())
	{
		f->SetDensity(density);
	}
}

void PhysicsBody::setFriction(float friction)
{
	for (b2Fixture* f = m_body->GetFixtureList(); f; f = f->GetNext())
	{
		f->SetFriction(friction);
	}
}

void PhysicsBody::setCollisionFilter(const b2Filter& filter)
{
	for (b2Fixture* f = m_body->GetFixtureList(); f; f = f->GetNext())
	{
		f->SetFilterData(filter);
	}
}