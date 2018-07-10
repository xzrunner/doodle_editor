#include "Actor.h"

#include "modules/graphics/GraphicsSprite.h"

using namespace d2d;

Actor::Actor(GraphicsSprite* sprite)
	: Item(e_actor)
	, m_sprite(sprite)
{
}

void Actor::onDraw() const
{
	m_sprite->onDraw();
}