#include "ScaleSize.h"

#include "modules/graphics/GraphicsSprite.h"

using namespace d2d;

ScaleSize::ScaleSize(GraphicsSprite* sprite, float scale)
	: m_sprite(sprite)
	, m_scale(scale)
{
}

void ScaleSize::trigger()
{
	m_sprite->setScale(m_scale);
}