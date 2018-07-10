#include "AECanvas.h"
#include "AEEditPanel.h"

#include "Frame/defs.h"

using namespace deditor::motox;

BEGIN_EVENT_TABLE(AECanvas, wxgui::GLCanvas)
	EVT_MOUSE_EVENTS(AECanvas::onMouse)
	EVT_KEY_DOWN(AECanvas::onKeyDown)
END_EVENT_TABLE()

AECanvas::AECanvas(AEEditPanel* editPanel)
	: wxgui::GLCanvas(editPanel)
	, m_editPanel(editPanel)
	, m_batch(100, wxgui::SpriteBatch::USAGE_STATIC)
{
}

void AECanvas::initGL()
{
	GLCanvas::initGL();

	std::vector<wxgui::ISymbol*> symbols;
	wxgui::SymbolMgr::Instance()->traverse(FetchAllVisitor<wxgui::ISymbol>(symbols));
	for (size_t i = 0, n = symbols.size(); i < n; ++i)
	{
		symbols[i]->reloadTexture();
	}
}

void AECanvas::onDraw()
{
	drawGuideLines();
	switch (wxgui::Settings::drawType)
	{
	case wxgui::Settings::e_DrawBoth:
		m_editPanel->traverseSprites(wxgui::DrawSpritesVisitor(m_batch), wxgui::e_visible);
		m_editPanel->drawPhysics();
		break;
	case wxgui::Settings::e_DrawImage:
		m_editPanel->traverseSprites(wxgui::DrawSpritesVisitor(m_batch), wxgui::e_visible);
		break;
	case wxgui::Settings::e_DrawPhysics:
		m_editPanel->drawPhysics();
		break;
	}
	m_editPanel->drawEditTemp();
}

void AECanvas::onMouse(wxMouseEvent& event)
{
	m_editPanel->onMouse(event);
}

void AECanvas::onKeyDown(wxKeyEvent& event)
{
	m_editPanel->onKeyDown(event);
}

void AECanvas::drawGuideLines()
{
	glColor3f(LIGHT_GRAY.r, LIGHT_GRAY.g, LIGHT_GRAY.b);

	glPushMatrix();
	glBegin(GL_LINES);
		glVertex2f(-SCREEN_WIDTH * 0.5f, 0.0f);
		glVertex2f( SCREEN_WIDTH * 0.5f, 0.0f);
		glVertex2f(0.0f, -SCREEN_HEIGHT * 0.5f);
		glVertex2f(0.0f,  SCREEN_HEIGHT * 0.5f);
	glEnd();
	glBegin(GL_LINE_LOOP);
		glVertex2f(-SCREEN_WIDTH * 0.5f, -SCREEN_HEIGHT * 0.5f);
		glVertex2f( SCREEN_WIDTH * 0.5f, -SCREEN_HEIGHT * 0.5f);
		glVertex2f( SCREEN_WIDTH * 0.5f,  SCREEN_HEIGHT * 0.5f);
		glVertex2f(-SCREEN_WIDTH * 0.5f,  SCREEN_HEIGHT * 0.5f);
	glEnd();
	glPopMatrix();
}