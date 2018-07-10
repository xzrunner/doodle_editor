#include "StagePanel.h"
#include "StageCanvas.h"
#include "Blackboard.h"
#include "LibraryItem.h"

using namespace deditor::boundary_extraction;

StagePanel::StagePanel(wxWindow* parent)
	: EditPanel(parent)
	, MultiShapesImpl(parent)
{
	m_canvas = new StageCanvas(this);
	m_item = NULL;
}

void StagePanel::traverseShapes(IVisitor& visitor, 
								wxgui::TraverseType type/* = wxgui::e_allExisting*/) const
{
	if (!m_item || !m_item->getUserData())
		return;

	std::vector<wxgui::IShape*>* shapes 
		= static_cast<std::vector<wxgui::IShape*>*>(m_item->getUserData());
	std::vector<wxgui::IShape*>::const_iterator itr = shapes->begin();
	for ( ; itr != shapes->end(); ++itr)
	{
		bool hasNext;
		visitor.visit(*itr, hasNext);
		if (!hasNext) break;
	}
}

void StagePanel::removeShape(wxgui::IShape* shape)
{
	if (!m_item || !m_item->getUserData())
		return;

	std::vector<wxgui::IShape*>* shapes 
		= static_cast<std::vector<wxgui::IShape*>*>(m_item->getUserData());
	std::vector<wxgui::IShape*>::iterator itr = shapes->begin();
	for ( ; itr != shapes->end(); ++itr)
	{
		if (*itr == shape)
		{
			shape->release();
			shapes->erase(itr);
			break;
		}
	}
}

void StagePanel::insertShape(wxgui::IShape* shape)
{
	if (!m_item || !m_item->getUserData())
		return;

	std::vector<wxgui::IShape*>* shapes 
		= static_cast<std::vector<wxgui::IShape*>*>(m_item->getUserData());
	static_cast<wxgui::ChainShape*>(shape)->setClosed(Blackboard::isClosed);
	shapes->push_back(shape);
}

void StagePanel::clear()
{
	if (!m_item || !m_item->getUserData())
		return;

	std::vector<wxgui::IShape*>* shapes 
		= static_cast<std::vector<wxgui::IShape*>*>(m_item->getUserData());
	for_each(shapes->begin(), shapes->end(), DeletePointerFunctor<wxgui::IShape>());
	shapes->clear();
}

void StagePanel::onDraw()
{
	if (m_item) m_item->draw();
}

void StagePanel::changeCurrItem(LibraryItem* item)
{
	m_item = item;
	if (m_item && !m_item->getUserData())
	{
		std::vector<wxgui::IShape*>* shapes = new std::vector<wxgui::IShape*>;
		m_item->setUserData(shapes);
	}
	Refresh();
}

void StagePanel::clearItemLines()
{
	if (m_item && m_item->getUserData())
		m_item->clearUserData(false);
}