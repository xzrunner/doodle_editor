#include "SetTextureCoordsOP.h"

using namespace deditor::skater;

SetTextureCoordsOP::SetTextureCoordsOP(wxgui::EditPanel* editPanel, wxgui::ImageSprite* sprite)
	: ZoomViewOP(editPanel, false)
	, m_sprite(sprite)
{
	m_userData = static_cast<float*>(m_sprite->getUserData());

	m_selected = e_null;
}

bool SetTextureCoordsOP::onMouseLeftDown(int x, int y)
{
	if (ZoomViewOP::onMouseLeftDown(x, y)) return true;

	const float width = m_sprite->getSymbol().getWidth(),
		height = m_sprite->getSymbol().getHeight();

	f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);

	float nearest = FLOAT_MAX;
	m_selected = e_null;

	float left = width * (m_userData[0] - 0.5f),
		right = width * (m_userData[2] - 0.5f),
		down = height * (m_userData[1] - 0.5f),
		up = height * (m_userData[3] - 0.5f);

	float dis = f2Math::getDistance(pos, f2Vec2(left, (down + up) * 0.5f));
	if (dis < nearest)
	{
		nearest = dis;
		m_selected = e_left;
	}

	dis = f2Math::getDistance(pos, f2Vec2((left + right) * 0.5f, down));
	if (dis < nearest)
	{
		nearest = dis;
		m_selected = e_down;
	}

	dis = f2Math::getDistance(pos, f2Vec2(right, (down + up) * 0.5f));
	if (dis < nearest)
	{
		nearest = dis;
		m_selected = e_right;
	}

	dis = f2Math::getDistance(pos, f2Vec2((left + right) * 0.5f, up));
	if (dis < nearest)
	{
		nearest = dis;
		m_selected = e_up;
	}

	setSelectedEdgePos(pos);

	return false;
}

bool SetTextureCoordsOP::onMouseDrag(int x, int y)
{
	if (ZoomViewOP::onMouseDrag(x, y)) return true;

	if (m_selected != e_null)
	{
		f2Vec2 pos = m_editPanel->transPosScreenToProject(x, y);
		setSelectedEdgePos(pos);
	}

	return false;
}

bool SetTextureCoordsOP::onDraw() const
{
	if (ZoomViewOP::onDraw()) return true;

	const float width = m_sprite->getSymbol().getWidth(),
		height = m_sprite->getSymbol().getHeight();

	glLineWidth(3.0f);
	glColor3f(0.0f, 0.5f, 0.5f);

	glPushMatrix();

	float left = width * (m_userData[0] - 0.5f),
		right = width * (m_userData[2] - 0.5f),
		down = height * (m_userData[1] - 0.5f),
		up = height * (m_userData[3] - 0.5f);

	glBegin(GL_LINE_LOOP);
		glVertex2f(left, down);
		glVertex2f(right, down);
		glVertex2f(right, up);
		glVertex2f(left, up);
	glEnd();

	glPopMatrix();

	glLineWidth(1.0f);

	return false;
}

bool SetTextureCoordsOP::clear()
{
	if (ZoomViewOP::clear()) return true;

	m_selected = e_null;

	return false;
}

void SetTextureCoordsOP::setSelectedEdgePos(const f2Vec2& pos)
{
	if (m_selected == e_null) return;

	const float hWidth = m_sprite->getSymbol().getWidth() * 0.5f,
		hHeight = m_sprite->getSymbol().getHeight() * 0.5f;

	if (m_selected == e_left)
	{
		if (pos.x < -hWidth)
			m_userData[0] = 0.0f;
		else if (pos.x >= -hWidth && pos.x < 0.0f)
			m_userData[0] = (hWidth + pos.x) / (hWidth * 2);
		else
			m_userData[0] = 0.5f;
	}
	else if (m_selected == e_right)
	{
		if (pos.x > hWidth)
			m_userData[2] = 1.0f;
		else if (pos.x <= hWidth && pos.x > 0.0f)
			m_userData[2] = (hWidth + pos.x) / (hWidth * 2);
		else
			m_userData[2] = 0.5f;
	}
	else if (m_selected == e_down)
	{
		if (pos.y < -hHeight)
			m_userData[1] = 0.0f;
		else if (pos.y >= -hHeight && pos.y < 0.0f)
			m_userData[1] = (hHeight + pos.y) / (hHeight * 2);
		else
			m_userData[1] = 0.5f;
	}
	else
	{
		if (pos.y > hHeight)
			m_userData[3] = 1.0f;
		else if (pos.y <= hHeight && pos.y > 0.0f)
			m_userData[3] = (hHeight + pos.y) / (hHeight * 2);
		else
			m_userData[3] = 0.5f;
	}

	static_cast<wxgui::ImageSprite*>(m_sprite)->buildBounding(m_userData);

	m_editPanel->Refresh();
}