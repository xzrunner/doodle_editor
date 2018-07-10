#include "CircleBody.h"
#include "BodyData.h"
#include <Box2D/Box2D.h>

using namespace FEDITOR;

CircleBody::CircleBody(b2World* world, const BodyData& bodyData, float scale/* = 1.0f*/)
	: Body(world, scale)
{
	m_filename = bodyData.getFilename();

	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	m_body = world->CreateBody(&bd);

	b2FixtureDef fd;
	fd.density = 1;
	fd.restitution = 0.6f;

	b2CircleShape shape;
	shape.m_radius = bodyData.getAllFixturesData()[0]->vertices[0].x * 0.5f * scale;
	fd.shape = &shape;

	m_body->CreateFixture(&fd);
}

CircleBody::CircleBody(b2World* world, float radius)
	: Body(world, 1.0f)
{
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	m_body = world->CreateBody(&bd);

	b2FixtureDef fd;
	fd.density = 1;
	fd.restitution = 0.6f;

	b2CircleShape shape;
	shape.m_radius = radius;
	fd.shape = &shape;

	m_body->CreateFixture(&fd);
}

void CircleBody::getAABB(f2AABB& aabb, const f2Vec2& position, float angle) const
{
	b2Shape* shape = m_body->GetFixtureList()->GetShape();
	b2CircleShape* circle = dynamic_cast<b2CircleShape*>(shape);
	assert(circle);
	aabb.xMin = position.x - circle->m_radius;
	aabb.xMax = position.x + circle->m_radius;
	aabb.yMin = position.y - circle->m_radius;
	aabb.yMax = position.y + circle->m_radius;
}