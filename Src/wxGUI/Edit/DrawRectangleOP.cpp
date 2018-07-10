#include "DrawRectangleOP.h"

#include <gl/glu.h>

using namespace wxgui;

DrawRectangleOP::DrawRectangleOP(EditPanel* editPanel,
								 const f2Colorf& color /*= f2Colorf(0, 0, 0)*/)
	: ZoomViewOP(editPanel, true)
	, m_color(color)
{
	m_firstPos.setInvalid();
	m_currPos.setInvalid();
}

bool DrawRectangleOP::onMouseLeftDown(int x, int y)
{
	if (ZoomViewOP::onMouseLeftDown(x, y)) return true;

	m_firstPos = m_editPanel->transPosScreenToProject(x, y);
	m_editPanel->Refresh();

	return false;
}

bool DrawRectangleOP::onMouseLeftUp(int x, int y)
{
	if (ZoomViewOP::onMouseLeftUp(x, y)) return true;

	m_firstPos.setInvalid();
	m_currPos.setInvalid();
	m_editPanel->Refresh();

	return false;
}

bool DrawRectangleOP::onMouseDrag(int x, int y)
{
	if (ZoomViewOP::onMouseDrag(x, y)) return true;

	if (m_firstPos.isValid())
	{
		m_currPos = m_editPanel->transPosScreenToProject(x, y);
		m_editPanel->Refresh();
	}

	return false;
}

bool DrawRectangleOP::onDraw() const
{
	if (ZoomViewOP::onDraw()) return true;

	if (m_firstPos.isValid() && m_currPos.isValid())
	{
		glColor3f(m_color.r, m_color.g, m_color.b);
		glLineWidth(2.0f);
		glPushMatrix();
		glBegin(GL_LINE_LOOP);
			glVertex3f(m_firstPos.x, m_firstPos.y, -1.0f);
			glVertex3f(m_currPos.x, m_firstPos.y, -1.0f);
			glVertex3f(m_currPos.x, m_currPos.y, -1.0f);
			glVertex3f(m_firstPos.x, m_currPos.y, -1.0f);
		glEnd();
		glPopMatrix();
		glLineWidth(1.0f);
	}

	return false;
}

bool DrawRectangleOP::clear()
{
	if (ZoomViewOP::clear()) return true;

	m_firstPos.setInvalid();
	m_currPos.setInvalid();

	return false;
}