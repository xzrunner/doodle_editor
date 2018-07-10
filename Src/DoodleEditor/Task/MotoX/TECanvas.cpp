#include "TECanvas.h"
#include "TEEditPanel.h"

#include "Frame/defs.h"

using namespace deditor::motox;

BEGIN_EVENT_TABLE(TECanvas, wxgui::GLCanvas)
	EVT_MOUSE_EVENTS(TECanvas::onMouse)
	EVT_KEY_DOWN(TECanvas::onKeyDown)
END_EVENT_TABLE()

TECanvas::TECanvas(TEEditPanel* editPanel)
	: wxgui::GLCanvas(editPanel)
	, m_editPanel(editPanel)
	, m_batch(100, wxgui::SpriteBatch::USAGE_STATIC)
{
}

void TECanvas::initGL()
{
	wxgui::GLCanvas::initGL();
	m_editPanel->getLibraryPanel()->reloadTexture();
}

void TECanvas::onDraw()
{
	drawGuideLines();
	m_editPanel->traverseSprites(wxgui::DrawSpritesVisitor(m_batch), wxgui::e_visible);
	m_editPanel->drawEditTemp();
}

void TECanvas::onMouse(wxMouseEvent& event)
{
	m_editPanel->onMouse(event);
}

void TECanvas::onKeyDown(wxKeyEvent& event)
{
	m_editPanel->onKeyDown(event);
}

void TECanvas::drawGuideLines()
{
	const float halfWidthTimes = 1.5f;

	glColor3f(0.8f, 0.2f, 0.2f);
	glPushMatrix();
	glBegin(GL_LINES);
		glVertex2f(-SCREEN_WIDTH * halfWidthTimes, 0.0f);
		glVertex2f( SCREEN_WIDTH * halfWidthTimes, 0.0f);
	glEnd();

	glColor3f(LIGHT_GRAY.r, LIGHT_GRAY.g, LIGHT_GRAY.b);
	glBegin(GL_LINE_LOOP);
		glVertex2f(-SCREEN_WIDTH * 0.5f, -SCREEN_HEIGHT * 0.5f);
		glVertex2f( SCREEN_WIDTH * 0.5f, -SCREEN_HEIGHT * 0.5f);
		glVertex2f( SCREEN_WIDTH * 0.5f,  SCREEN_HEIGHT * 0.5f);
		glVertex2f(-SCREEN_WIDTH * 0.5f,  SCREEN_HEIGHT * 0.5f);
	glEnd();
	glPopMatrix();
}