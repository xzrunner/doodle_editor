#include "MeshSprite.h"

using namespace motox;

MeshSprite::MeshSprite(float scale)
	: m_scale(scale)
	, m_mesh(NULL) 
	, m_meshID(-1)
	, m_angle(0)
{
}

MeshSprite::~MeshSprite()
{
}

void MeshSprite::setTransform(const d2d::Vector& location, float angle)
{
	IObstacleSprite::setTransform(location, angle);

	m_location = location;
	m_angle = angle;
}

void MeshSprite::update()
{
	if (!m_physics) return;

	m_angle = m_physics->getBody()->GetAngle();

	b2Vec2 p = m_physics->getBody()->GetPosition();
	m_location.set(p.x * d2d::BOX2D_SCALE_FACTOR, p.y * d2d::BOX2D_SCALE_FACTOR);
}

void MeshSprite::addToBatch(d2d::MeshBatch* batch) const
{
	batch->add(*m_mesh, m_location.x, m_location.y, m_angle, m_scale, /*index++*/-1);
}