#include "ZoomViewOP.h"

#include "View/Camera.h"
#include "Tools/Settings.h"

using namespace wxgui;

ZoomViewOP::ZoomViewOP(EditPanel* editPanel, bool bMouseMoveFocus) 
	: AbstractEditOP(editPanel)
	, m_bMouseMoveFocus(bMouseMoveFocus)
{
	m_lastPos.setInvalid();
}

bool ZoomViewOP::onKeyDown(int keyCode)
{
	if (!Settings::bZoomOnlyUseMouseWheel && keyCode == WXK_SPACE)
		m_editPanel->SetCursor(wxCURSOR_HAND);
	return false;
}

bool ZoomViewOP::onKeyUp(int keyCode)
{
	if (!Settings::bZoomOnlyUseMouseWheel && keyCode == WXK_SPACE)
		m_editPanel->SetCursor(wxCURSOR_ARROW);
	return false;
}

bool ZoomViewOP::onMouseLeftDown(int x, int y)
{
	if (!Settings::bZoomOnlyUseMouseWheel)
		m_lastPos.setInvalid();

	if (!Settings::bZoomOnlyUseMouseWheel && wxGetKeyState(WXK_SPACE))
	{
		m_lastPos.set(x, y);
		return true;
	}
	else
	{
		return false;
	}
}

bool ZoomViewOP::onMouseLeftUp(int x, int y)
{
	if (!Settings::bZoomOnlyUseMouseWheel && wxGetKeyState(WXK_SPACE))
	{
		m_lastPos.setInvalid();
		return true;
	}
	else
	{
		return false;
	}
}

bool ZoomViewOP::onMouseMove(int x, int y) 
{
	if (m_bMouseMoveFocus) 
		m_editPanel->SetFocus();

	return false;
}

bool ZoomViewOP::onMouseDrag(int x, int y)
{
	if (Settings::bZoomOnlyUseMouseWheel) return false;

	if (wxGetKeyState(WXK_SPACE))
	{
		if (!m_lastPos.isValid())
			m_lastPos.set(x, y);
		else
		{
			f2Vec2 currPos(x, y);

			f2Vec2 cameraPos = m_editPanel->getCamera()->getCenter();
			f2Vec2 offset = m_lastPos - currPos;
			offset *= m_editPanel->getCamera()->getScale();
			offset.y = -offset.y;
			m_editPanel->getCamera()->setCenter(cameraPos + offset);

			m_lastPos = currPos;

			m_editPanel->Refresh();
		}
		return true;
	}
	else
	{
		m_lastPos.setInvalid();
		return false;
	}
}

bool ZoomViewOP::onMouseWheelRotation(int x, int y, int direction) 
{
	if (Settings::bZoomOnlyUseMouseWheel)
		m_editPanel->onMouseWheelRotation(x, y, direction);
	else
		m_editPanel->onMouseWheelRotation(m_editPanel->GetSize().GetWidth() * 0.5f, m_editPanel->GetSize().GetHeight() * 0.5f, direction);

	return false;
}