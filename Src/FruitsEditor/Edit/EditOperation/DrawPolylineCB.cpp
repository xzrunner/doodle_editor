#include "DrawPolylineCB.h"
#include "../../Dataset/ChainShape.h"
#include "../../Dataset/Sprite.h"

using namespace FEDITOR;

DrawPolylineCB::DrawPolylineCB(Sprite* sprite)
{
	m_sprite = sprite;

	m_staticShape = new ChainShape;
	m_dynamicShape = new ChainShape;
	m_sprite->pushShape(m_staticShape);
	m_sprite->pushShape(m_dynamicShape);

	m_finishDirSet = true;
}

DrawPolylineCB::DrawPolylineCB(Sprite* sprite, const std::vector<f2Vec2>& preload)
{
	m_sprite = sprite;

	m_staticShape = new ChainShape;
	m_dynamicShape = new ChainShape;
	m_sprite->pushShape(m_staticShape);
	m_sprite->pushShape(m_dynamicShape);

	for (size_t i = 0, n = preload.size(); i < n; ++i)
		m_staticShape->pushBack(preload[i]);

	if (!preload.empty()) m_finishDirSet = false;
}

DrawPolylineCB::~DrawPolylineCB()
{
	m_staticShape->m_isLoop = true;
	m_sprite->popShape();
	eraseEmptyShape();	
}

void DrawPolylineCB::afterMouseLeftDown(const f2Vec2& pos)
{
	if (!m_finishDirSet)
	{
		const float d0 = f2Math::getDistance(pos, m_staticShape->m_vertices.front()),
			d1 = f2Math::getDistance(pos, m_staticShape->m_vertices.back());
		if (d0 < d1) reverse(m_staticShape->m_vertices.begin(), m_staticShape->m_vertices.end());

		m_finishDirSet = true;
	}

	m_staticShape->m_vertices.push_back(pos);

	if (m_dynamicShape->m_vertices.empty())
		m_dynamicShape->m_vertices.push_back(pos);
	else
		m_dynamicShape->m_vertices[0] = pos;
}

void DrawPolylineCB::afterMouseRightDown(const f2Vec2& pos)
{
	m_staticShape->m_vertices.pop_back();
	if (m_staticShape->m_vertices.empty())
		m_dynamicShape->m_vertices.clear();
	else
		m_dynamicShape->m_vertices[0] = m_staticShape->m_vertices.back();
}

void DrawPolylineCB::afterMouseMove(const f2Vec2& pos)
{
	if (m_staticShape->m_vertices.empty())
		;
	else if (m_dynamicShape->m_vertices.size() < 2)
		m_dynamicShape->m_vertices.push_back(pos);
	else
		m_dynamicShape->m_vertices[1] = pos;
}

void DrawPolylineCB::eraseEmptyShape()
{
	ChainShape *chain;
	do 
	{
		Shape* shape = m_sprite->popShape();
		chain = dynamic_cast<ChainShape*>(shape);
	} while (chain && chain->m_vertices.empty());

	if (chain && !chain->m_vertices.empty())
		m_sprite->pushShape(chain);
}