#include "StageCanvas.h"
#include "StagePanel.h"

#include "Frame/defs.h"

using namespace deditor::manual_compose;

StageCanvas::StageCanvas(StagePanel* parent)
	: wxgui::SpriteStageCanvas(parent, parent)
{
}

void StageCanvas::onDraw()
{
	drawGuideLines();
	drawBackground();
	wxgui::SpriteStageCanvas::onDraw();
}

void StageCanvas::drawGuideLines()
{
//	drawCross();
	drawRect();
}

void StageCanvas::drawBackground()
{
	StagePanel* editPanel = static_cast<StagePanel*>(m_editPanel);
	if (editPanel->getBackground())
		wxgui::SpriteDraw::drawSprite(editPanel->getBackground());
}

void StageCanvas::drawRect()
{
	const int hWidth = SCREEN_WIDTH * 0.5f,
		hHeight = SCREEN_HEIGHT * 0.5f;

	glColor3f(LIGHT_GRAY.r, LIGHT_GRAY.g, LIGHT_GRAY.b);
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
		glVertex2f(-hWidth, -hHeight);
		glVertex2f( hWidth, -hHeight);
		glVertex2f( hWidth, hHeight);
		glVertex2f(-hWidth, hHeight);
	glEnd();
	glPopMatrix();
}

void StageCanvas::drawCross()
{
	glColor3f(LIGHT_GRAY.r, LIGHT_GRAY.g, LIGHT_GRAY.b);
	glPushMatrix();
	glBegin(GL_LINES);
		glVertex2f(-1000.0f, 0.0f);
		glVertex2f( 1000.0f, 0.0f);
	glEnd();
	glBegin(GL_LINES);
		glVertex2f(0.0f, -1000.0f);
		glVertex2f(0.0f,  1000.0f);
	glEnd();
	glPopMatrix();
}