#include "Body.h"
#include "BodyFactory.h"
#include <Box2D/Box2D.h>

using namespace FEDITOR;

Body::Body(b2World* world, float scale/* = 1.0f*/)
{
	m_alive = false;
	
	m_world = world;
	m_body = NULL;
	
	m_scale = scale;
}

Body::~Body()
{
	if (m_body)
	{
		m_world->DestroyBody(m_body);
		m_body = NULL;
	}
}

Body* Body::clone()
{
	if (m_filename == "") return NULL;

	Body* body = BodyFactory::createBody(m_filename, m_scale);

	body->m_filename = m_filename;
	body->m_alive = m_alive;

	b2Body* b2body = body->getBody();
	b2body->SetTransform(m_body->GetPosition(), m_body->GetAngle());

	return body;
}

void Body::setDensity(float density)
{
	for (b2Fixture* f = m_body->GetFixtureList(); f; f = f->GetNext())
	{
		f->SetDensity(density);
	}
}

void Body::setFriction(float friction)
{
	for (b2Fixture* f = m_body->GetFixtureList(); f; f = f->GetNext())
	{
		f->SetFriction(friction);
	}
}

void Body::setCollisionFilter(const b2Filter& filter)
{
	for (b2Fixture* f = m_body->GetFixtureList(); f; f = f->GetNext())
	{
		f->SetFilterData(filter);
	}
}

void Body::setTransform(const f2Vec2& pos, float angle)
{
	m_body->SetTransform(b2Vec2(pos.x, pos.y), angle);
}