#include "MeshSprite.h"
#include "IBody.h"
#include "BodyFactory.h"

#include <Box2D/Box2D.h>

using namespace wxgui;

MeshSprite::MeshSprite()
{
}

MeshSprite::MeshSprite(const MeshSprite& sprite)
	: ISprite(sprite)
	, m_symbol(sprite.m_symbol)
{
}

MeshSprite::MeshSprite(MeshSymbol* symbol)
	: m_symbol(symbol)
{
	buildBounding();
}

MeshSprite::~MeshSprite()
{
}

MeshSprite* MeshSprite::clone()
{
	return new MeshSprite(*this);
}

const MeshSymbol& MeshSprite::getSymbol() const
{
	return *m_symbol;
}

void MeshSprite::setSymbol(ISymbol* symbol)
{
	MeshSymbol* mesh = dynamic_cast<MeshSymbol*>(symbol);
	if (mesh) m_symbol = mesh;
}

void MeshSprite::loadBodyFromFile()
{
	if (!m_symbol) return;

	if (m_body) delete m_body;
	m_body = BodyFactory::createBody(m_symbol->getVertices(), m_scale);

	m_body->getBody()->SetTransform(b2Vec2(m_pos.x / BOX2D_SCALE_FACTOR, m_pos.y / BOX2D_SCALE_FACTOR), m_angle);
}

void MeshSprite::buildBounding()
{
	delete m_bounding;
	m_bounding = BVFactory::createBV(e_obb);

	if (m_symbol)
	{
		f2AABB aabb;
		const std::vector<f2Vec2>& vertices = m_symbol->getVertices();
		for (size_t i = 0, n = vertices.size(); i < n; ++i)
			aabb.combine(vertices[i]);

		aabb *= m_scale;
		aabb.translate(m_pos);
		m_bounding->initFromAABB(aabb);
		m_bounding->rotate(m_angle);
	}
}