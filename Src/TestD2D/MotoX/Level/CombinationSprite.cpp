#include "CombinationSprite.h"

using namespace motox;

CombinationSprite::CombinationSprite()
{
}

CombinationSprite::~CombinationSprite()
{
	for (size_t i = 0, n = m_children.size(); i < n; ++i)
		m_children[i]->release();
	m_children.clear();
}

void CombinationSprite::setTransform(const d2d::Vector& location, float angle)
{
	IObstacleSprite::setTransform(location, angle);

	for (size_t i = 0, n = m_children.size(); i < n; ++i)
	{
		Part* child = m_children[i];
		child->sprite->setTransform(location + child->offset, angle + child->delta);
	}
}

void CombinationSprite::update()
{
	if (!m_physics) return;

	m_angle = m_physics->getBody()->GetAngle();

	b2Vec2 p = m_physics->getBody()->GetPosition();
	m_location.set(p.x * d2d::BOX2D_SCALE_FACTOR, p.y * d2d::BOX2D_SCALE_FACTOR);

	for (size_t i = 0, n = m_children.size(); i < n; ++i)
	{
		Part* child = m_children[i];
		d2d::Vector offset;
		d2d::rotateVector(child->offset, m_angle, offset);
		child->sprite->setTransform(m_location + offset, m_angle + child->delta);
	}
}

void CombinationSprite::addToBatch(d2d::MeshBatch* batch) const
{
	for (size_t i = 0, n = m_children.size(); i < n; ++i)
		m_children[i]->sprite->addToBatch(batch);
}