#include "Button.h"
#include "Behavior.h"

#include "common/tools.h"
#include "modules/graphics/GraphicsSprite.h"

using namespace d2d;

Button::Button(GraphicsSprite* sprite)
	: Item(e_button)
	, m_sprite(sprite)
{
}

Button::~Button()
{
	delete m_sprite;

	for_each(m_pressBehaviors.begin(), m_pressBehaviors.end(), 
		DeletePointerFunctor<Behavior>());
	for_each(m_liftBehaviors.begin(), m_liftBehaviors.end(), 
		DeletePointerFunctor<Behavior>());
}

void Button::onDraw() const
{
	if (m_sprite)
		m_sprite->onDraw();
}

// todo: only no rotate
bool Button::isContain(const Vector& pos) const
{
	if (!m_sprite) return false;

	const Vertex* region = m_sprite->getQuad().getVertices();
	const float scale = m_sprite->getScale();
	const d2d::Vector& center = m_sprite->getLocation();
	const float left = center.x + region[0].x * scale,
		right = center.x + region[3].x * scale,
		down = center.y + region[0].y * scale,
		up = center.y + region[1].y * scale;

	return pos.x > left && pos.x < right
		&& pos.y > down && pos.y < up;
}

void Button::addBehavior(Behavior* behavior, bool bPress)
{
	if (bPress)
		m_pressBehaviors.push_back(behavior);
	else
		m_liftBehaviors.push_back(behavior);
}

void Button::triggerBehaviors(bool bPress)
{
	std::vector<Behavior*>& behaviors = bPress ? m_pressBehaviors : m_liftBehaviors;
	for (size_t i = 0, n = behaviors.size(); i < n; ++i)
		behaviors[i]->trigger();
}