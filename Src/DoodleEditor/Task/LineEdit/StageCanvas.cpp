#include "StageCanvas.h"
#include "StagePanel.h"

#include "Frame/defs.h"

using namespace deditor::line_edit;

StageCanvas::StageCanvas(StagePanel* parent)
	: wxgui::ShapeStageCanvas(parent, parent)
{
}

void StageCanvas::onDraw()
{
	drawGuideLines();
	wxgui::ShapeStageCanvas::onDraw();
}

void StageCanvas::drawGuideLines()
{
	glColor3f(LIGHT_GRAY.r, LIGHT_GRAY.g, LIGHT_GRAY.b);
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
		glVertex2f(0, 0);
		glVertex2f(SCREEN_WIDTH, 0);
		glVertex2f(SCREEN_WIDTH, SCREEN_HEIGHT);
		glVertex2f(0, SCREEN_HEIGHT);
	glEnd();
	glPopMatrix();
}