#include "DrawPolylineOP.h"
#include "View/Camera.h"

#include <gl/glu.h>

using namespace wxgui;

DrawPolylineOP::DrawPolylineOP(EditPanel* editPanel, bool isClosed)
	: ZoomViewOP(editPanel, true)
{
	m_isClosed = isClosed;
	m_currPos.setInvalid();
}

bool DrawPolylineOP::onMouseLeftDown(int x, int y)
{
	if (ZoomViewOP::onMouseLeftDown(x, y)) return true;

	f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);
	if (shouldFixMousePos())
		fixPosTo45Degree(pos);
	m_polyline.push_back(pos);
	m_editPanel->Refresh();

	return false;
}

bool DrawPolylineOP::onMouseRightDown(int x, int y)
{
	if (ZoomViewOP::onMouseRightDown(x, y)) return true;

	if (!m_polyline.empty())
	{
		m_polyline.pop_back();
		if (m_polyline.empty()) m_currPos.setInvalid();
		m_editPanel->Refresh();
	}

	return false;
}

bool DrawPolylineOP::onMouseMove(int x, int y)
{
	if (ZoomViewOP::onMouseMove(x, y)) return true;

	if (m_polyline.empty()) return false;

	f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);
	if (shouldFixMousePos())
		fixPosTo45Degree(pos);
	m_currPos = pos;
	m_editPanel->Refresh();

	return false;
}

bool DrawPolylineOP::onMouseLeftDClick(int x, int y)
{
	if (ZoomViewOP::onMouseLeftDClick(x, y)) return true;

	if (m_isClosed)
		m_polyline.push_back(m_polyline.front());
	m_editPanel->Refresh();

	return false;
}

bool DrawPolylineOP::onDraw() const
{
	if (ZoomViewOP::onDraw()) return true;

	if (m_polyline.empty()) return false;

	glColor3f(0, 0, 0);

	glLineWidth(2.0f);
	glPushMatrix();
	glBegin(GL_LINE_STRIP);
	for (size_t i = 0, n = m_polyline.size(); i < n; ++i)
		glVertex2f(m_polyline[i].x, m_polyline[i].y);
	if (m_currPos.isValid())
		glVertex2f(m_currPos.x, m_currPos.y);
	glEnd();
	glPopMatrix();
	glLineWidth(1.0f);

	return false;
}

bool DrawPolylineOP::clear()
{
	if (ZoomViewOP::clear()) return true;

	m_polyline.clear();
	m_currPos.setInvalid();

	return false;
}

bool DrawPolylineOP::shouldFixMousePos() const
{
	return !m_polyline.empty() && wxGetKeyState(WXK_SHIFT);
}

void DrawPolylineOP::fixPosTo45Degree(f2Vec2& pos) const
{
	f2Vec2 last = m_polyline.back();

	float nearest;
	f2Vec2 fixed = pos;

	const float dx = fabs(pos.x - last.x);
	nearest = dx;
	fixed.set(last.x, pos.y);

	const float dy = fabs(pos.y - last.y);
	if (dy < nearest)
	{
		nearest = dy;
		fixed.set(pos.x, last.y);
	}

	f2Vec2 other(last.x + 1, last.y - 1);
	const float dxyDown = f2Math::getDisPointToStraightLine(pos, last, other);
	if (dxyDown < nearest)
	{
		nearest = dxyDown;
		f2Math::getFootOfPerpendicular(last, other, pos, &fixed);
	}

	other.set(last.x + 1, last.y + 1);
	const float dxyUp = f2Math::getDisPointToStraightLine(pos, last, other);
	if (dxyUp < nearest)
	{
		nearest = dxyUp;
		f2Math::getFootOfPerpendicular(last, other, pos, &fixed);
	}

	pos = fixed;
}