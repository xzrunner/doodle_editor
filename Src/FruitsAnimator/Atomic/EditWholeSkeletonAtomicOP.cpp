#include "EditWholeSkeletonAtomicOP.h"

using namespace FRUITS_ANIMATOR;
using namespace FRUITS_ANIMATOR::edit_whole_skeleton;

RotateBoneAOP::RotateBoneAOP(wxgui::EditPanel* editPanel, WholeSkeleton::Sprite* selected, float delta)
{
	m_editPanel = editPanel;
	m_selected = selected;
	m_delta = delta;
}

void RotateBoneAOP::undo()
{
	m_selected->m_relativeCoords.delta -= m_delta;
	m_selected->computePosterityAbsoluteCoords();

	m_editPanel->Refresh();
}

void RotateBoneAOP::redo()
{
	m_selected->m_relativeCoords.delta += m_delta;
	m_selected->computePosterityAbsoluteCoords();

	m_editPanel->Refresh();
}