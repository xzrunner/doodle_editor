#include "DrawTrackChainCB.h"
#include "TrackChains.h"
#include "../../../Dataset/ChainShape.h"
#include "../../../Dataset/Sprite.h"

using namespace FEDITOR;
using namespace FEDITOR::MOTOX::LEVEL;

DrawTrackChainCB::DrawTrackChainCB(TrackChains& trackChains)
	: m_trackChains(trackChains)
{
	m_staticShape = new ChainShape;
	m_dynamicShape = new ChainShape;
	m_trackChains.getShapeSprite()->pushShape(m_staticShape);
	m_trackChains.getShapeSprite()->pushShape(m_dynamicShape);

	m_trackChains.setCtlposDrawable(true);
}

DrawTrackChainCB::~DrawTrackChainCB()
{
	m_trackChains.getShapeSprite()->popShape();
	eraseEmptyShape();
	m_trackChains.addFixtureFromLastChain();

	m_trackChains.setCtlposDrawable(false);
}

void DrawTrackChainCB::afterMouseLeftDown(const f2Vec2& pos)
{
	m_staticShape->m_vertices.push_back(pos);

	if (m_dynamicShape->m_vertices.empty())
		m_dynamicShape->m_vertices.push_back(pos);
	else
		m_dynamicShape->m_vertices[0] = pos;
}

void DrawTrackChainCB::afterMouseRightDown(const f2Vec2& pos)
{
	m_staticShape->m_vertices.pop_back();
	if (m_staticShape->m_vertices.empty())
		m_dynamicShape->m_vertices.clear();
	else
		m_dynamicShape->m_vertices[0] = m_staticShape->m_vertices.back();
}

void DrawTrackChainCB::afterMouseMove(const f2Vec2& pos)
{
	if (m_staticShape->m_vertices.empty())
		;
	else if (m_dynamicShape->m_vertices.size() < 2)
		m_dynamicShape->m_vertices.push_back(pos);
	else
		m_dynamicShape->m_vertices[1] = pos;
}

void DrawTrackChainCB::eraseEmptyShape()
{
	ChainShape *chain;
	do 
	{
		Shape* shape = m_trackChains.getShapeSprite()->popShape();
		chain = dynamic_cast<ChainShape*>(shape);
	} while (chain && chain->m_vertices.empty());

	if (chain && !chain->m_vertices.empty())
		m_trackChains.getShapeSprite()->pushShape(chain);
}