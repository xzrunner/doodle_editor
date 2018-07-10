#include "ISprite.h"
#include "ISymbol.h"
#include "IBody.h"

#include <Box2D/Box2D.h>

using namespace wxgui;

ISprite::ISprite()
	: m_body(NULL)
{
}

ISprite::~ISprite()
{
	delete m_body;
}

// todo: translate() and rotate() has no opt to m_body
void ISprite::setTransform(const f2Vec2& position, float angle)
{
	f2Sprite::setTransform(position, angle);
	if (m_body)
		m_body->getBody()->SetTransform(b2Vec2(position.x / BOX2D_SCALE_FACTOR, position.y / BOX2D_SCALE_FACTOR), angle);
}

void ISprite::setScale(float scale)
{
	f2Sprite::setScale(scale);

	buildBounding();

	if (m_body)
	{
		b2BodyType type = m_body->getBody()->GetType();
		loadBodyFromFile();
		if (m_body)
		{
			m_body->getBody()->SetTransform(b2Vec2(m_pos.x / BOX2D_SCALE_FACTOR, m_pos.y / BOX2D_SCALE_FACTOR), m_angle);
			m_body->getBody()->SetType(type);
		}
	}
}

void ISprite::updateEachFrame()
{
	if (!m_body) return;

	b2Body* body = m_body->getBody();
	if (!body) return;

	if (m_body->isAlive() && m_body->getBody()->GetType() != b2_staticBody)
	{
		const b2Vec2& pos = body->GetPosition();
		setTransform(f2Vec2(pos.x * BOX2D_SCALE_FACTOR, pos.y * BOX2D_SCALE_FACTOR), body->GetAngle());
	}
	else
	{
		body->SetTransform(b2Vec2(m_pos.x / BOX2D_SCALE_FACTOR, m_pos.y / BOX2D_SCALE_FACTOR), m_angle);
	}
}

IBody* ISprite::getBody() const
{
	return m_body;
}

//////////////////////////////////////////////////////////////////////////
// class SpriteCmp
//////////////////////////////////////////////////////////////////////////

SpriteCmp::SpriteCmp(Type type /*= e_file*/)
	: m_type(type)
{
}

bool SpriteCmp::operator() (const ISprite* s0, const ISprite* s1) const
{
	switch (m_type)
	{
	case e_file:
		return s0->getSymbol().getFilepath() < s1->getSymbol().getFilepath();
	case e_x:
		return s0->getPosition().x < s1->getPosition().x;
	case e_y:
		return s0->getPosition().y < s1->getPosition().y;
	default:
		return s0->getSymbol().getFilepath() < s1->getSymbol().getFilepath();
	}
}
