#include "ShapesPanelImpl.h"
#include "TrackChain.h"

using namespace deditor::motox;

ShapesPanelImpl::ShapesPanelImpl(wxWindow* wnd)
	: MultiShapesImpl(wnd)
{
	m_world = NULL;
}

ShapesPanelImpl::~ShapesPanelImpl()
{
	clear();
}

void ShapesPanelImpl::traverseShapes(IVisitor& visitor, 
									 wxgui::TraverseType type/* = wxgui::e_allExisting*/) const
{
	{
		std::vector<TrackChain*>::const_iterator itr = m_chains.begin();
		for ( ; itr != m_chains.end(); ++itr)
		{
			bool hasNext;
			visitor.visit(*itr, hasNext);
			if (!hasNext) break;
		}
	}
	{
		std::vector<wxgui::PolygonShape*>::const_iterator itr = m_polys.begin();
		for ( ; itr != m_polys.end(); ++itr)
		{
			bool hasNext;
			visitor.visit(*itr, hasNext);
			if (!hasNext) break;
		}
	}
}

void ShapesPanelImpl::removeShape(wxgui::IShape* shape)
{
	std::vector<TrackChain*>::iterator itr = m_chains.begin();
	for ( ; itr != m_chains.end(); ++itr)
	{
		if (*itr == shape)
		{
			delete *itr;
			m_chains.erase(itr);
			break;
		}
	}
}

void ShapesPanelImpl::insertShape(wxgui::IShape* shape)
{
	wxgui::PolygonShape* poly = dynamic_cast<wxgui::PolygonShape*>(shape);
	if (poly)
	{
		m_polys.push_back(poly);
		return;
	}

	if (m_world)
	{
		wxgui::ChainShape* chain = static_cast<wxgui::ChainShape*>(shape);
		if (chain->getVertices().size() > 1)
		{
			TrackChain* track = new TrackChain(m_world, m_worldReverse, chain->getVertices());
			shape->release();
			m_chains.push_back(track);
			m_wnd->Refresh();	
		}
	}
	else
	{
		shape->release();
	}
}

void ShapesPanelImpl::clear()
{
	for_each(m_chains.begin(), m_chains.end(), DeletePointerFunctor<TrackChain>());
	m_chains.clear();
}

void ShapesPanelImpl::setTracksFriction(float friction)
{
	for (size_t i = 0, n = m_chains.size(); i < n; ++i)
		m_chains[i]->setFriction(friction);
}

void ShapesPanelImpl::getTracksRegion(float& leftmost, float& rightmost) const
{
	leftmost = FLOAT_MAX;
	rightmost = -FLOAT_MAX;
	for (size_t i = 0, n = m_chains.size(); i < n; ++i)
	{
		const f2AABB& aabb = m_chains[i]->getAABB();
		if (aabb.xMin < leftmost) leftmost = aabb.xMin;
		if (aabb.xMax > rightmost) rightmost = aabb.xMax;
	}
}