#include "EditWholeSkeletonJointOP.h"
#include "Tools/Render.h"

using namespace FRUITS_ANIMATOR;

EditWholeSkeletonJointOP::EditWholeSkeletonJointOP(wxgui::EditPanel* editPanel, 
												   WholeSkeleton::Body* body)
	: wxgui::ZoomViewOP(editPanel, false)
{
	m_body = body;
	m_selected = NULL;
}

bool EditWholeSkeletonJointOP::onMouseLeftDown(int x, int y)
{
	if (ZoomViewOP::onMouseLeftDown(x, y)) return true;

	f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);
	WholeSkeleton::Node* node = m_body->queryNodeByPos(pos);
	if (node) 
	{
		m_selected = node;
		m_selected->pos = pos;
	}
	else 
	{
		m_body->insertNode(pos);
		m_selected = m_body->queryNodeByPos(pos);
	}
	m_editPanel->Refresh();

	return false;
}

bool EditWholeSkeletonJointOP::onMouseLeftUp(int x, int y)
{
	if (ZoomViewOP::onMouseLeftUp(x, y)) return true;

	if (m_selected)
	{
		m_selected = NULL;
		m_editPanel->Refresh();
	}

	return false;
}

bool EditWholeSkeletonJointOP::onMouseRightDown(int x, int y)
{
	if (ZoomViewOP::onMouseRightDown(x, y)) return true;

	f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);
	WholeSkeleton::Node* node = m_body->queryNodeByPos(pos);
	if (node) 
	{
		m_body->eraseNode(node);
		m_editPanel->Refresh();
	}

	return false;
}

bool EditWholeSkeletonJointOP::onMouseDrag(int x, int y)
{
	if (ZoomViewOP::onMouseDrag(x, y)) return true;

	if (m_selected) 
	{
		m_selected->pos = m_editPanel->transPosScreenToProject(x, y);
		m_editPanel->Refresh();
	}

	return false;
}

bool EditWholeSkeletonJointOP::onDraw() const
{
	if (ZoomViewOP::onDraw()) return true;

	m_body->onDraw();

	if (m_selected)
	{
		wxgui::Render::drawRing(m_selected->pos, 
			WholeSkeleton::Body::NODE_RADIUS, f2Colorf(0.0f, 1.0f, 1.0f));
	}

	return false;
}

bool EditWholeSkeletonJointOP::clear()
{
	if (ZoomViewOP::clear()) return true;

	m_selected = NULL;

	return false;
}