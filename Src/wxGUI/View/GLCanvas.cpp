#include "GLCanvas.h"
#include "Camera.h"

#include "View/EditPanel.h"

#include <wx/wx.h>
#include <gl/glu.h>

using namespace wxgui;

BEGIN_EVENT_TABLE(GLCanvas, wxGLCanvas)
	EVT_SIZE(GLCanvas::onSize)
	EVT_PAINT(GLCanvas::onPaint)
	EVT_ERASE_BACKGROUND(GLCanvas::onEraseBackground)
 	EVT_MOUSE_EVENTS(GLCanvas::onMouse)
 	EVT_KEY_DOWN(GLCanvas::onKeyDown)
	EVT_KEY_UP(GLCanvas::onKeyUp)
END_EVENT_TABLE()

int gl_attrib[20] = {WX_GL_RGBA, WX_GL_MIN_RED, 1, WX_GL_MIN_GREEN, 1,
WX_GL_MIN_BLUE, 1, WX_GL_DEPTH_SIZE, 1,
WX_GL_DOUBLEBUFFER,WX_GL_STENCIL_SIZE, 8, 0};

GLCanvas::GLCanvas(EditPanel* editPanel)
	: wxGLCanvas(editPanel, wxID_ANY, gl_attrib)
	, m_editPanel(editPanel)
 	, m_camera(editPanel->getCamera())
 	, m_width(0), m_height(0)
 	, m_isInit(false)
 	, m_context(new wxGLContext(this))
{
	m_bgColor.set(1.0f, 1.0f, 1.0f, 1.0f);
}

GLCanvas::~GLCanvas()
{
	delete m_context;
}

void GLCanvas::resetInitState() 
{ 
	m_isInit = false; 
}

void GLCanvas::resetViewport()
{
	onSize(wxSizeEvent(m_parent->GetSize()));
}

void GLCanvas::setBgColor(const f2Colorf& color)
{
	m_bgColor = color;
}

void GLCanvas::initGL()
{
	resetViewport();

	glShadeModel(GL_SMOOTH);
	glEnable(GL_TEXTURE_2D);
}

void GLCanvas::onSize(wxSizeEvent& event)
{
	wxSize size = event.GetSize();

	m_width = size.GetWidth();
	m_height = size.GetHeight();
	glViewport(0, 0, size.GetWidth(), size.GetHeight());

	const float hWidth = size.GetWidth() * m_camera->getScale() * 0.5f,
		hHeight = size.GetHeight() * m_camera->getScale() * 0.5f;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(
		m_camera->getCenter().x - hWidth, 
		m_camera->getCenter().x + hWidth, 
		m_camera->getCenter().y - hHeight,
		m_camera->getCenter().y + hHeight
		);
}

void GLCanvas::onPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);

	SetCurrent(*m_context);

	if (!m_isInit)
	{
		initGL();
		m_isInit = true;
	}

	glClearColor(m_bgColor.r, m_bgColor.g, m_bgColor.b, m_bgColor.a);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
	onDraw();
	glPopMatrix();

	glFlush();
	SwapBuffers();

// 	dc.DrawText(wxT("���֧� ���ڧܧ��a�֧ӧڧ� ����ݧ��o��"), 40, 60);
// 	dc.DrawText(wxT("���ߧߧ� ���ѧ�֧ߧڧߧ�"), 70, 80);
}

void GLCanvas::onEraseBackground(wxEraseEvent& event)
{
	
}

void GLCanvas::onMouse(wxMouseEvent& event)
{
	m_editPanel->onMouse(event);
}

void GLCanvas::onKeyDown(wxKeyEvent& event)
{
	m_editPanel->onKeyDown(event);
}

void GLCanvas::onKeyUp(wxKeyEvent& event)
{
	m_editPanel->onKeyUp(event);
}