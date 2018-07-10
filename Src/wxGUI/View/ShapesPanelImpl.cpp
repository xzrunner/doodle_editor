#include "ShapesPanelImpl.h"

using namespace wxgui;

ShapesPanelImpl::ShapesPanelImpl(wxWindow* wnd)
	: MultiShapesImpl(wnd)
{
}

ShapesPanelImpl::~ShapesPanelImpl()
{
	clear();
}

void ShapesPanelImpl::traverseShapes(IVisitor& visitor, 
									 TraverseType type/* = e_allExisting*/) const
{
	std::vector<IShape*>::const_iterator itr = m_shapes.begin();
	for ( ; itr != m_shapes.end(); ++itr)
	{
		bool hasNext;
		visitor.visit(*itr, hasNext);
		if (!hasNext) break;
	}
}

void ShapesPanelImpl::removeShape(IShape* shape)
{
	std::vector<IShape*>::iterator itr = m_shapes.begin();
	for ( ; itr != m_shapes.end(); ++itr)
	{
		if (*itr == shape)
		{
			delete *itr;
			m_shapes.erase(itr);
			break;
		}
	}
}

void ShapesPanelImpl::insertShape(IShape* shape)
{
	m_shapes.push_back(shape);
	m_wnd->Refresh();
}

void ShapesPanelImpl::clear()
{
	for_each(m_shapes.begin(), m_shapes.end(), DeletePointerFunctor<IShape>());
	m_shapes.clear();
}