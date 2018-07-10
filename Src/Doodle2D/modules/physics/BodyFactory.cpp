#include "BodyFactory.h"
#include "PhysicsBody.h"

#include "common/math.h"

using namespace d2d;

static int count = 0;

PhysicsBody* BodyFactory::createChains(b2World* world, const std::vector<std::vector<Vector> >& chains)
{
	PhysicsBody* body = new PhysicsBody(world);

	b2BodyDef bd;
	bd.type = b2_staticBody;
	body->m_body = world->CreateBody(&bd);

	for (size_t i = 0, n = chains.size(); i < n; ++i)
	{
		const size_t size = chains[i].size();
		std::vector<b2Vec2> chain(size);
		for (size_t j = 0; j < size; ++j)
		{
			chain[j].x = chains[i][j].x * BOX2D_SCALE_FACTOR_INVERSE;
			chain[j].y = chains[i][j].y * BOX2D_SCALE_FACTOR_INVERSE;
		}

		b2ChainShape shape;
		shape.CreateChain(&chain[0], size);

		b2FixtureDef fd;
		fd.shape = &shape;

		body->m_body->CreateFixture(&fd);
	}

	return body;
}

PhysicsBody* BodyFactory::createPolygons(b2World* world, const std::vector<std::vector<Vector> >& loops, float scale /*= 1.0f*/)
{
	PhysicsBody* body = new PhysicsBody(world);

	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	body->m_body = world->CreateBody(&bd);

	for (size_t i = 0, n = loops.size(); i < n; ++i)
	{
		const size_t size = loops[i].size();
		std::vector<b2Vec2> loop(size);
		if (scale == 1.0f)
		{
			for (size_t j = 0; j < size; ++j)
			{
				loop[j].x = loops[i][j].x * BOX2D_SCALE_FACTOR_INVERSE;
				loop[j].y = loops[i][j].y * BOX2D_SCALE_FACTOR_INVERSE;
			}
		}
		else
		{
			for (size_t j = 0; j < size; ++j)
			{
				loop[j].x = loops[i][j].x * scale * BOX2D_SCALE_FACTOR_INVERSE;
				loop[j].y = loops[i][j].y * scale * BOX2D_SCALE_FACTOR_INVERSE;
			}
		}

		b2PolygonShape shape;
		shape.Set(&loop[0], size);

		b2FixtureDef fd;
		fd.shape = &shape;
		fd.density = 0.5f;
		fd.friction = 0.5f;

		body->m_body->CreateFixture(&fd);
	}

	return body;
}

PhysicsBody* BodyFactory::createCircle(b2World* world, float radius)
{
	PhysicsBody* body = new PhysicsBody(world);

	b2BodyDef bd;
	bd.type = b2_dynamicBody;
	body->m_body = world->CreateBody(&bd);

	b2CircleShape shape;
	shape.m_radius = radius * BOX2D_SCALE_FACTOR_INVERSE;

	b2FixtureDef fd;
	fd.shape = &shape;
	fd.density = 0.2f;
	fd.friction = 1.0f;

	body->m_body->CreateFixture(&fd);

	return body;
}

PhysicsBody* BodyFactory::createBody(b2World* world, const PhysicsParser::Body& body)
{
	PhysicsBody* retBody = new PhysicsBody(world);

	b2BodyDef bd;
	switch (body.type)
	{
	case PhysicsParser::Body::e_dynamic:
		bd.type = b2_dynamicBody;
		break;
	case PhysicsParser::Body::e_kinematic:
		bd.type = b2_kinematicBody;
		break;
	case PhysicsParser::Body::e_static:
		bd.type = b2_staticBody;
		break;
	}

	bd.position.x = body.location.x * BOX2D_SCALE_FACTOR_INVERSE;
	bd.position.y = body.location.y * BOX2D_SCALE_FACTOR_INVERSE;
	bd.angle = body.angle;
	retBody->m_body = world->CreateBody(&bd);

	for (size_t i = 0, n = body.fixtures.size(); i < n; ++i)
	{
		PhysicsParser::Fixture* fixture = body.fixtures[i];

		b2FixtureDef fd;
		fd.density = fixture->density;
		fd.friction = fixture->friction;
		fd.restitution = fixture->restitution;
		// no bits

		switch (fixture->shape->type)
		{
		case PhysicsParser::Shape::e_circle:
			{
				PhysicsParser::CircleShape* circle = static_cast<PhysicsParser::CircleShape*>(fixture->shape);

				b2CircleShape shape;
				shape.m_radius = circle->radius * BOX2D_SCALE_FACTOR_INVERSE;

				fd.shape = &shape;

//				if (bd.position.x < 0)
//					fd.density = 0.1f;
//				else
//					fd.density = 0.25f;
//
////				fd.density = 0.25f;
//				fd.friction = 3;

				retBody->m_body->CreateFixture(&fd);
			}
			break;
		case PhysicsParser::Shape::e_polygon:
			{
				PhysicsParser::PolygonShape* poly = static_cast<PhysicsParser::PolygonShape*>(fixture->shape);

				size_t size = poly->vertices.size();
				std::vector<b2Vec2> loop(size);
				for (size_t j = 0; j < size; ++j)
				{
					loop[j].x = poly->vertices[j].x * BOX2D_SCALE_FACTOR_INVERSE;
					loop[j].y = poly->vertices[j].y * BOX2D_SCALE_FACTOR_INVERSE;
				}

				b2PolygonShape shape;
				shape.Set(&loop[0], size);

				fd.shape = &shape;

				retBody->m_body->CreateFixture(&fd);
			}
			break;
		}
	}

	return retBody;
}