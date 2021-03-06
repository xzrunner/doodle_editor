#include "PreviewCanvas.h"
#include "Blackboard.h"
#include "StagePanel.h"

using namespace deditor::magic_defence;

BEGIN_EVENT_TABLE(PreviewCanvas, wxgui::GLCanvas)
	EVT_TIMER(TIMER_ID, PreviewCanvas::onTimer)
END_EVENT_TABLE()

PreviewCanvas::PreviewCanvas(wxgui::EditPanel* editPanel, StagePanel* stagePanel, 
							 wxgui::LibraryPanel* libraryPanel)
	: wxgui::GLCanvas(editPanel)
	, m_stagePanel(stagePanel)
	, m_libraryPanel(libraryPanel)
	, m_timer(this, TIMER_ID)
	, m_xOffset(0.0f)
{
	m_timer.Start(1000 / FRAME_RATE);
}

PreviewCanvas::~PreviewCanvas()
{
	m_timer.Stop();
}

void PreviewCanvas::initGL()
{
	wxgui::GLCanvas::initGL();

	glTranslatef(800 * 0.5f, - 480 * 0.5f, 0.0f);

	m_libraryPanel->reloadTexture();
}

void PreviewCanvas::onDraw()
{
	m_stagePanel->traverseSprites(DrawVisitor(m_xOffset), wxgui::e_visible);
}

void PreviewCanvas::onTimer(wxTimerEvent& event)
{
	const float offset = 800.0f * Blackboard::length / Blackboard::row / Blackboard::time / FRAME_RATE;
	m_xOffset += offset;

	glTranslatef(-offset, 0.0f, 0.0f);

	Refresh();
}

//////////////////////////////////////////////////////////////////////////
// class PreviewCanvas::DrawVisitor
//////////////////////////////////////////////////////////////////////////

void PreviewCanvas::DrawVisitor::visit(IObject* object, bool& bFetchNext)
{
	wxgui::ISprite* sprite = static_cast<wxgui::ISprite*>(object);

	const float factor = 480.0f / (Blackboard::edge * Blackboard::row);
	f2Vec2 new_pos = sprite->getPosition() * factor;
	const int tol = 100;
//	if (new_pos.x - m_xOffset < 0 + tol && new_pos.x - m_xOffset > -800 - tol)
	{
		wxgui::SpriteDraw::drawSprite(&sprite->getSymbol(), new_pos);
	}

	bFetchNext = true;
}