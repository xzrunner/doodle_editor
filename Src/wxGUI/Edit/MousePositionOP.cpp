#include "MousePositionOP.h"

#include "Component/MousePositionCMPT.h"

using namespace wxgui;

MousePositionOP::MousePositionOP(EditPanel* editPanel, MousePositionCMPT* cmpt)
	: ZoomViewOP(editPanel, true)
	, m_cmpt(cmpt)
{
}

bool MousePositionOP::onMouseMove(int x, int y)
{
	if (ZoomViewOP::onMouseMove(x, y)) return true;

	m_cmpt->updatePosition(m_editPanel->transPosScreenToProject(x, y));

	return false;
}