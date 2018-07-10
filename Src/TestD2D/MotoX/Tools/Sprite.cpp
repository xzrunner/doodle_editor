#include "Sprite.h"

using namespace motox;

Sprite::Sprite()
	: m_graphics(NULL)
	, m_physics(NULL)
	, m_bDirty(true)
{
}

Sprite::~Sprite()
{
	delete m_graphics;
	delete m_physics;
}

void Sprite::setTransform(const d2d::Vector& location, float angle)
{
	if (m_graphics)
	{
		m_graphics->setTransform(location, angle);
	}
	if (m_physics)
	{
 		b2Vec2 loc;
 		loc.x = location.x * d2d::BOX2D_SCALE_FACTOR_INVERSE;
 		loc.y = location.y * d2d::BOX2D_SCALE_FACTOR_INVERSE;
 		m_physics->getBody()->SetTransform(loc, angle);
	}
}

void Sprite::update()
{
	if (m_physics && m_graphics)
	{
		d2d::Vector location;
		float angle = m_physics->getBody()->GetAngle();
		b2Vec2 p = m_physics->getBody()->GetPosition();
		location.set(p.x * d2d::BOX2D_SCALE_FACTOR, p.y * d2d::BOX2D_SCALE_FACTOR);
		m_bDirty = (m_graphics->getLocation() != location || m_graphics->getAngle() != angle);
		m_graphics->setTransform(location, angle);
	}
	else
	{
		m_bDirty = false;
	}
}

void Sprite::getAABB(d2d::AABB& aabb) const
{
	const d2d::Quad& quad = m_graphics->getQuad();
	const float scale = m_graphics->getScale();

	float x1 = quad.getVertices()[0].x * scale;
	float y1 = quad.getVertices()[0].y * scale;
	float x2 = quad.getVertices()[1].x * scale;
	float y2 = quad.getVertices()[1].y * scale;
	float x3 = quad.getVertices()[2].x * scale;
	float y3 = quad.getVertices()[2].y * scale;

	const d2d::Vector& center = m_graphics->getLocation();
	float angle = m_graphics->getAngle();

#ifdef D2D_FAST_MATH
	const float sine = static_cast<float>(d2d::taylorSin(angle)),
		cosine = static_cast<float>(d2d::taylorCos(angle));
#else
	const float sine = sin(angle),
		cosine = cos(angle);
#endif

	d2d::Vector vertices[4];

	vertices[0].x = cosine * x1 - sine * y1 + center.x;
	vertices[0].y = sine * x1 + cosine * y1 + center.y;

	vertices[1].x = cosine * x2 - sine * y2 + center.x;
	vertices[1].y = sine * x2 + cosine * y2 + center.y;

	vertices[2].x = cosine * x3 - sine * y3 + center.x;
	vertices[2].y = sine * x3 + cosine * y3 + center.y;

	vertices[3].x = vertices[0].x + (vertices[2].x - vertices[1].x);
	vertices[3].y = vertices[2].y - (vertices[1].y - vertices[0].y);

	aabb.combine(vertices[0]);
	aabb.combine(vertices[1]);
	aabb.combine(vertices[2]);
	aabb.combine(vertices[3]);
}