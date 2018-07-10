#include "EditSpritePartSkeletonOP.h"
#include "Tools/Render.h"

using namespace FRUITS_ANIMATOR;

EditSpritePartSkeletonOP::EditSpritePartSkeletonOP(wxgui::EditPanel* editPanel, PartSkeleton* skeleton)
	: wxgui::ZoomViewOP(editPanel, false)
{
	m_skeleton = skeleton;
	m_selected = NULL;
}

bool EditSpritePartSkeletonOP::onMouseLeftDown(int x, int y)
{
	if (ZoomViewOP::onMouseLeftDown(x, y)) return true;

	f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);
	m_selected = m_skeleton->queryJointByPos(pos);

	return false;
}

bool EditSpritePartSkeletonOP::onMouseLeftUp(int x, int y)
{
	if (ZoomViewOP::onMouseLeftUp(x, y)) return true;

	m_selected = NULL;

	return false;
}

bool EditSpritePartSkeletonOP::onMouseDrag(int x, int y)
{
	if (ZoomViewOP::onMouseDrag(x, y)) return true;

	if (m_selected)
	{
		f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);
		m_skeleton->rotateJoint(m_selected, pos);
		m_editPanel->Refresh();
	}

	return false;
}

bool EditSpritePartSkeletonOP::onDraw() const
{
	if (ZoomViewOP::onDraw()) return true;

	m_skeleton->onDraw();

	return false;
}

bool EditSpritePartSkeletonOP::clear()
{
	if (ZoomViewOP::clear()) return true;

	m_selected = NULL;

	return false;
}