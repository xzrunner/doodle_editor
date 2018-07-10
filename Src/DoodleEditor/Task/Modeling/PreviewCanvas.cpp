#include "PreviewCanvas.h"
#include "PreviewPanel.h"

using namespace deditor::modeling;

BEGIN_EVENT_TABLE(PreviewCanvas, wxgui::GLCanvas)
	EVT_TIMER(TIMER_ID, PreviewCanvas::onTimer)
END_EVENT_TABLE()

PreviewCanvas::PreviewCanvas(PreviewPanel* editPanel, 
							 wxgui::LibraryPanel* libraryPanel)
	: wxgui::GLCanvas(editPanel)
	, m_libraryPanel(libraryPanel)
	, m_timer(this, TIMER_ID)
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
	m_libraryPanel->reloadTexture();
}

void PreviewCanvas::onDraw()
{
	static_cast<PreviewPanel*>(m_editPanel)->drawPhysics();
}

void PreviewCanvas::onTimer(wxTimerEvent& event)
{
	Refresh();
}