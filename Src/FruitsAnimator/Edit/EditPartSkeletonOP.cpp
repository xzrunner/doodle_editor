#include "EditPartSkeletonOP.h"
#include "Tools/Render.h"

using namespace FRUITS_ANIMATOR;

EditPartSkeletonOP::EditPartSkeletonOP(wxgui::EditPanel* editPanel, PartSkeleton* skeleton)
	: wxgui::ZoomViewOP(editPanel, false)
{
	m_skeleton = skeleton;
	m_selectedJoint = NULL;
	m_selectedNode = NULL;
}

bool EditPartSkeletonOP::onMouseLeftDown(int x, int y)
{
	if (ZoomViewOP::onMouseLeftDown(x, y)) return true;

	f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);
	m_selectedJoint = m_skeleton->queryJointByPos(pos);
	if (!m_selectedJoint) 
	{
		m_selectedNode = m_skeleton->queryNodeByPos(pos);
		m_skeleton->translateNode(m_selectedNode, pos);
	}
	m_editPanel->Refresh();

	return false;
}

bool EditPartSkeletonOP::onMouseLeftUp(int x, int y)
{
	if (ZoomViewOP::onMouseLeftUp(x, y)) return true;

	m_selectedJoint = NULL;
	m_selectedNode = NULL;

	return false;
}

bool EditPartSkeletonOP::onMouseDrag(int x, int y)
{
	if (ZoomViewOP::onMouseDrag(x, y)) return true;

	if (m_selectedJoint)
	{
		f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);
		m_skeleton->translateJoint(m_selectedJoint, pos);
		m_editPanel->Refresh();
	}
	else if (m_selectedNode)
	{
		f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);
		m_skeleton->translateNode(m_selectedNode, pos);
		m_editPanel->Refresh();
	}

	return false;
}

bool EditPartSkeletonOP::onDraw() const
{
	if (ZoomViewOP::onDraw()) return true;

	m_skeleton->onDraw();

	return false;
}

bool EditPartSkeletonOP::clear()
{
	if (ZoomViewOP::clear()) return true;

	m_selectedJoint = NULL;
	m_selectedNode = NULL;

	return false;
}