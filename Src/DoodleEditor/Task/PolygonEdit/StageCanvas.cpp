#include "StageCanvas.h"
#include "StagePanel.h"

#include "Frame/defs.h"

using namespace deditor::polygon_edit;

StageCanvas::StageCanvas(StagePanel* parent)
	: wxgui::ShapeStageCanvas(parent, parent)
	, m_batch(500, wxgui::SpriteBatch::USAGE_STATIC)
{
}

void StageCanvas::clear()
{
	std::vector<wxgui::ISprite*>::iterator itr = m_tiles.begin();
	for ( ; itr != m_tiles.end(); ++itr)
		(*itr)->release();
	m_tiles.clear();
}

void StageCanvas::onDraw()
{
	drawGuideLines();

	m_shapesImpl->traverseShapes(wxgui::DrawShapesVisitor(m_color), wxgui::e_visible);
	wxgui::SpriteDraw::drawSprites(m_tiles, m_batch);
	m_editPanel->drawEditTemp();
}

void StageCanvas::drawGuideLines() const
{
	static const float xStart = 0, xEnd = 25;
	static const float yStart = -5, yEnd = 5;

	glColor3f(LIGHT_GRAY.r, LIGHT_GRAY.g, LIGHT_GRAY.b);
	glPushMatrix();
	glBegin(GL_LINES);
	for (int i = yStart; i <= yEnd; ++i)
	{
		glVertex2f(SCREEN_WIDTH * xStart, SCREEN_HEIGHT * i);
		glVertex2f(SCREEN_WIDTH * xEnd, SCREEN_HEIGHT * i);
	}
	for (int i = xStart; i <= xEnd; ++i)
	{
		glVertex2f(SCREEN_WIDTH * i, SCREEN_HEIGHT * yStart);
		glVertex2f(SCREEN_WIDTH * i, SCREEN_HEIGHT * yEnd);
	}
	glEnd();
	glPopMatrix();

	glColor3f(1, 0, 0);
	glPushMatrix();
	glBegin(GL_LINES);
		glVertex2f(SCREEN_WIDTH * xStart, 0);
		glVertex2f(SCREEN_WIDTH * xEnd, 0);
		glVertex2f(SCREEN_WIDTH * xStart, SCREEN_HEIGHT);
		glVertex2f(SCREEN_WIDTH * xEnd, SCREEN_HEIGHT);
		for (int i = xStart; i <= xEnd; ++i)
		{
			glVertex2f(SCREEN_WIDTH * i, 0);
			glVertex2f(SCREEN_WIDTH * i, SCREEN_HEIGHT);
		}
	glEnd();
	glPopMatrix();

	glColor3f(0, 0, 0);
}