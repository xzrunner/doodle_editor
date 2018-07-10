#include "StageCanvas.h"
#include "StagePanel.h"
#include "Frame/defs.h"

using namespace deditor::automatic_merge;

StageCanvas::StageCanvas(StagePanel* parent)
	: wxgui::SpriteStageCanvas(parent, parent)
{
	m_width = m_height = 0;
}

void StageCanvas::setOutputImageSize(int width, int height)
{
	m_width = width;
	m_height = height;
}

void StageCanvas::onDraw()
{
	drawGuideLines();
	wxgui::SpriteStageCanvas::onDraw();
}

void StageCanvas::drawGuideLines()
{
	glColor3f(LIGHT_GRAY.r, LIGHT_GRAY.g, LIGHT_GRAY.b);

	glPushMatrix();
	glBegin(GL_LINES);
	for (size_t i = 0; i <= m_height; ++i)
	{
		glVertex2f(0, i);
		glVertex2f(m_width, i);
	}
	for (size_t i = 0; i <= m_width; ++i)
	{
		glVertex2f(i, 0);
		glVertex2f(i, m_height);
	}
	glEnd();
	glPopMatrix();
}