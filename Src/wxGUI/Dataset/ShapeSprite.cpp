#include "ShapeSprite.h"
#include "PolygonShape.h"
#include "IBody.h"
#include "BodyFactory.h"

#include <Box2D/Box2D.h>

using namespace wxgui;

ShapeSprite::ShapeSprite()
{
}

ShapeSprite::ShapeSprite(const ShapeSprite& sprite)
	: ISprite(sprite)
	, m_symbol(sprite.m_symbol)
{
}

ShapeSprite::ShapeSprite(ShapeSymbol* symbol)
	: m_symbol(symbol)
{
	buildBounding();
}

ShapeSprite::~ShapeSprite()
{
}

ShapeSprite* ShapeSprite::clone()
{
	return new ShapeSprite(*this);
}

const ShapeSymbol& ShapeSprite::getSymbol() const
{
	return *m_symbol;
}

void ShapeSprite::setSymbol(ISymbol* symbol)
{
	ShapeSymbol* shape = dynamic_cast<ShapeSymbol*>(symbol);
	if (shape) m_symbol = shape;
}

void ShapeSprite::loadBodyFromFile()
{
	if (!m_symbol) return;

	if (m_body) delete m_body;

	std::vector<f2Vec2> triangles;
	const std::vector<IShape*>& shapes = m_symbol->getAllShapes();
	for (size_t i = 0, n = shapes.size(); i < n; ++i)
	{
		PolygonShape* poly = dynamic_cast<PolygonShape*>(shapes[i]);
		if (poly)
			copy(poly->m_fillingVertices.begin(), poly->m_fillingVertices.end(), back_inserter(triangles));
	}

	m_body = BodyFactory::createBody(triangles, m_scale);

	m_body->getBody()->SetTransform(b2Vec2(m_pos.x / BOX2D_SCALE_FACTOR, m_pos.y / BOX2D_SCALE_FACTOR), m_angle);
}

void ShapeSprite::buildBounding()
{
	delete m_bounding;
	m_bounding = BVFactory::createBV(e_obb);

	if (m_symbol)
	{
		f2AABB aabb;
		const std::vector<IShape*>& shapes = m_symbol->getAllShapes();
		for (size_t i = 0, n = shapes.size(); i < n; ++i)
			aabb.combine(shapes[i]->getAABB());
		
		aabb *= m_scale;
		aabb.translate(m_pos);
		m_bounding->initFromAABB(aabb);
		m_bounding->rotate(m_angle);
	}
}