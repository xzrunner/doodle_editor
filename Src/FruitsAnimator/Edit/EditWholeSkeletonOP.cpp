#include "EditWholeSkeletonOP.h"
#include "Atomic/EditWholeSkeletonAtomicOP.h"

using namespace FRUITS_ANIMATOR;

EditWholeSkeletonOP::EditWholeSkeletonOP(wxgui::EditPanel* editPanel, WholeSkeleton* skeleton)
	: wxgui::ZoomViewOP(editPanel, false)
{
	m_skeleton = skeleton;
	m_selected = NULL;
	m_firstPos.setInvalid();
}

bool EditWholeSkeletonOP::onMouseLeftDown(int x, int y)
{
	if (ZoomViewOP::onMouseLeftDown(x, y)) return true;

	m_lastPos = m_editPanel->transPosScreenToProject(x, y);
	m_selected = m_skeleton->queryByPos(m_lastPos);
	if (!m_selected->m_parent) m_selected = NULL;
	if (m_selected) m_firstPos = m_lastPos;

	return false;
}

bool EditWholeSkeletonOP::onMouseLeftUp(int x, int y)
{
	if (ZoomViewOP::onMouseLeftUp(x, y)) return true;

	if (m_selected && m_firstPos.isValid())
	{
		f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);

		const f2Vec2& center = m_selected->getNodeWorldCoords(m_selected->m_relativeCoords.from);
		float angle = f2Math::getAngleInDirection(center, m_firstPos, pos);

		m_editPanel->addHistoryOP(new edit_whole_skeleton::RotateBoneAOP(m_editPanel, m_selected, angle));
	}

	return false;
}

bool EditWholeSkeletonOP::onMouseDrag(int x, int y)
{
	if (ZoomViewOP::onMouseDrag(x, y)) return true;

	if (!m_selected) return false;

	if (m_selected->m_parent)
	{
		f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);

		const f2Vec2& center = m_selected->getNodeWorldCoords(m_selected->m_relativeCoords.from);
		float angle = f2Math::getAngleInDirection(center, m_lastPos, pos);

		m_selected->m_relativeCoords.delta += angle;
		m_selected->computePosterityAbsoluteCoords();

		m_editPanel->Refresh();

		m_lastPos = pos;
	}

	return false;
}

// bool EditWholeSkeletonOP::onDraw() const
// {
// 	return ZoomViewOP::onDraw();
// }

bool EditWholeSkeletonOP::clear()
{
	if (ZoomViewOP::clear()) return true;

	m_selected = NULL;
	m_lastPos.setInvalid();

	return false;
}