#include "f2Sprite.h"
#include "AbstractBV.h"

using namespace F2D;

f2Sprite::f2Sprite()
{
	m_pos.set(0.0f, 0.0f);
	m_angle = 0.0f;
	m_scale = 1.0f;
	m_xMirror = m_yMirror = false;
	m_bounding = NULL;
}

f2Sprite::f2Sprite(const f2Sprite& sprite)
{
	m_pos = sprite.m_pos;
	m_angle = sprite.m_angle;
	m_scale = sprite.m_scale;
	m_xMirror = sprite.m_xMirror;
	m_yMirror = sprite.m_yMirror;

	m_bounding = (AbstractBV*) sprite.m_bounding->clone();
}

f2Sprite::~f2Sprite()
{
	delete m_bounding;
}

void f2Sprite::clearUserData(bool deletePtr)
{
	delete m_userData, m_userData = NULL;
}

void f2Sprite::setTransform(const f2Vec2& position, float angle)
{
	if (m_pos != position) translate(position - m_pos);
	if (m_angle != angle) rotate(angle - m_angle);
}

bool f2Sprite::isContain(const f2Vec2& pos) const
{
	return m_bounding->isContain(pos);
}

bool f2Sprite::isIntersect(const f2AABB& aabb) const
{
	return m_bounding->isIntersect(aabb);
}

void f2Sprite::translate(const f2Vec2& offset)
{
	m_pos += offset;
	m_bounding->translate(offset);
}

void f2Sprite::rotate(float delta)
{
	m_angle += delta;
	m_bounding->rotate(delta);
}

const f2Vec2& f2Sprite::getPosition() const
{
	return m_pos;
}

float f2Sprite::getAngle() const
{
	return m_angle;
}

AbstractBV* f2Sprite::getBounding() const
{
	return m_bounding;
}