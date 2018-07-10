#include "SkeletonEditGLCanvas.h"
#include "SkeletonSymbolList.h"
#include "Tools/Render.h"

using namespace FRUITS_ANIMATOR;

BEGIN_EVENT_TABLE(SkeletonEditGLCanvas, wxgui::GLCanvas)
	EVT_MOUSE_EVENTS(SkeletonEditGLCanvas::onMouse)
END_EVENT_TABLE()

SkeletonEditGLCanvas::SkeletonEditGLCanvas(wxgui::EditPanel* parent, WholeSkeleton* skeleton, 
										   SkeletonSymbolList* symbolList)
	: wxgui::GLCanvas(parent)
{
	m_skeleton = skeleton;
	m_symbolList = symbolList;
}

void SkeletonEditGLCanvas::initGL()
{
	wxgui::GLCanvas::initGL();
 	m_symbolList->reloadAllTexture();
}

void SkeletonEditGLCanvas::onDraw()
{
	m_skeleton->onDraw();
	m_editPanel->drawEditTemp();
}

void SkeletonEditGLCanvas::onMouse(wxMouseEvent& event)
{
	m_editPanel->onMouse(event);
}
