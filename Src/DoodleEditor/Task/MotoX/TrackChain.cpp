#include "TrackChain.h"

using namespace deditor::motox;

TrackChain::TrackChain(b2World* world, b2World* worldReverse,
					   const std::vector<f2Vec2>& vertices)
	: ChainShape(vertices, false)
	, m_scale(1.0f)
	, m_world(world)
	, m_worldReverse(worldReverse)
	, m_body(NULL)
	, m_bodyReverse(NULL)
{
	createBody();
}

TrackChain::~TrackChain()
{
	delete m_body, m_body = NULL;
	delete m_bodyReverse, m_bodyReverse = NULL;
}

void TrackChain::insertVertices(size_t index, const f2Vec2& pos)
{
	ChainShape::insertVertices(index, pos);
	createBody();
}

void TrackChain::removeVertices(const f2Vec2& pos)
{
	ChainShape::removeVertices(pos);
	createBody();
}

void TrackChain::changeVertices(const f2Vec2& from, const f2Vec2& to)
{
	ChainShape::changeVertices(from, to);
//	createBody();
}

void TrackChain::setVertices(const std::vector<f2Vec2>& vertices)
{
	ChainShape::setVertices(vertices);
	createBody();
}

void TrackChain::refresh()
{
	createBody();
}

void TrackChain::setFriction(float friction)
{
	if (m_body)
		m_body->setFriction(friction);
}

void TrackChain::setScale(float scale)
{
	const float factor = scale / m_scale;
	m_scale = scale;
	for (size_t i = 0, n = m_vertices.size(); i < n; ++i)
		m_vertices[i] *= factor;
	m_bounding *= factor;

	createBody();
}

void TrackChain::setTranslation(const f2Vec2& offset)
{
	const f2Vec2 delta = offset - m_offset;
	m_offset = offset;
	for (size_t i = 0, n = m_vertices.size(); i < n; ++i)
		m_vertices[i] += delta;
	m_bounding.translate(delta);

	createBody();
}

void TrackChain::createBody()
{
	if (m_body) delete m_body;
	m_body = new wxgui::ChainBody(m_world, m_vertices, false);

	if (m_bodyReverse) delete m_bodyReverse;
	m_bodyReverse = new wxgui::ChainBody(m_worldReverse, m_vertices, false);
}