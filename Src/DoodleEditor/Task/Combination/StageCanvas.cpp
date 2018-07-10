#include "StageCanvas.h"
#include "StagePanel.h"

#include "Frame/defs.h"

using namespace deditor::combination;

StageCanvas::StageCanvas(StagePanel* editPanel)
	: wxgui::GLCanvas(editPanel)
	, m_batch(100, wxgui::SpriteBatch::USAGE_STATIC)
{
}

StageCanvas::~StageCanvas()
{
}

void StageCanvas::onDraw()
{
	drawGuideLines();

	StagePanel* editPanel = static_cast<StagePanel*>(m_editPanel);
	editPanel->traverseShapes(wxgui::DrawShapesVisitor(),
		wxgui::e_visible);
	editPanel->traverseSprites(wxgui::DrawSpritesVisitor(m_batch),
		wxgui::e_visible);
	editPanel->drawEditTemp();
}

void StageCanvas::drawGuideLines()
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