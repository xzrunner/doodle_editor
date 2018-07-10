#include "CommonSprite.h"

using namespace motox;

CommonSprite::CommonSprite()
	: m_graphics(NULL)
	, m_texID(-1)
{
}

CommonSprite::~CommonSprite()
{
	delete m_graphics;
}

void CommonSprite::setTransform(const d2d::Vector& location, float angle)
{
	IObstacleSprite::setTransform(location, angle);

	if (m_graphics)
		m_graphics->setTransform(location, angle);
}

void CommonSprite::update()
{
	if (!m_physics) return;

	if (m_physics && m_graphics)
	{
		float angle = m_physics->getBody()->GetAngle();

		d2d::Vector location;
		b2Vec2 p = m_physics->getBody()->GetPosition();
		location.set(p.x * d2d::BOX2D_SCALE_FACTOR, p.y * d2d::BOX2D_SCALE_FACTOR);

		m_graphics->setTransform(location, angle);
	}
}

void CommonSprite::addToBatch(d2d::MeshBatch* batch) const
{
	batch->add(*m_graphics, -1);
}