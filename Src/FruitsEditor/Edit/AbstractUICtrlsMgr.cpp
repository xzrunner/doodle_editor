#include "AbstractUICtrlsMgr.h"
#include "glui/glui.h"

using namespace FEDITOR;

std::queue<Event> AbstractUICtrlsMgr::m_eventList;

AbstractUICtrlsMgr::AbstractUICtrlsMgr()
{
	m_root = NULL;
}

AbstractUICtrlsMgr::~AbstractUICtrlsMgr()
{
	if (m_root) m_root->close();
}

void AbstractUICtrlsMgr::createUIRoot(int mainWnd)
{
	m_root = GLUI_Master.create_glui_subwindow(mainWnd, GLUI_SUBWINDOW_RIGHT);
}