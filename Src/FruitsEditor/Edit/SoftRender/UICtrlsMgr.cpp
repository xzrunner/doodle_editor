#include "UICtrlsMgr.h"
#include "Blackboard.h"
#include "glui/glui.h"

using namespace FEDITOR;
using namespace FEDITOR::SOFT_RENDER;

int UICtrlsMgr::m_openFileType = 0;

GLUI_FileBrowser* UICtrlsMgr::m_common_fb = NULL;

UICtrlsMgr::UICtrlsMgr(Blackboard* blackboard)
{
	m_blackboard = blackboard;
}

void UICtrlsMgr::createUIControls(CmptMgr& cmptMgr, ShortcutKeyListener* shortcutLsn)
{
	buildIOPanel();
	buildCameraPanel();
}

void UICtrlsMgr::callback(int id)
{
 	switch (id)
 	{
	case e_OpenFile:
		m_eventList.push(Event(Blackboard::e_OpenMode, m_common_fb->get_file()));
		break;
	default:
		m_eventList.push(Event(id));
 	}
}

void UICtrlsMgr::buildIOPanel()
{
	GLUI_Panel* panel = new GLUI_Panel(m_root, "I/O");
	m_common_fb = new GLUI_FileBrowser(panel, "", false, e_OpenFile, callback);
}

void UICtrlsMgr::buildCameraPanel()
{
	GLUI_Panel* panel = new GLUI_Panel(m_root, "Camera");

	GLUI_Panel* cam_pos_panel = new GLUI_Panel(panel, "cam pos");
	GLUI_Spinner* spinner = new GLUI_Spinner(cam_pos_panel, "x", &m_blackboard->m_camPos.x);
	spinner->set_float_limits(-1500, 1500);
	spinner = new GLUI_Spinner(cam_pos_panel, "y", &m_blackboard->m_camPos.y);
	spinner->set_float_limits(-1500, 1500);
	spinner = new GLUI_Spinner(cam_pos_panel, "z", &m_blackboard->m_camPos.z);
	spinner->set_float_limits(-1500, 1500);

	GLUI_Panel* cam_dir_panel = new GLUI_Panel(panel, "cam dir");
	spinner = new GLUI_Spinner(cam_dir_panel, "x", &m_blackboard->m_camDir.x);
	spinner->set_float_limits(-1, 1);
	spinner = new GLUI_Spinner(cam_dir_panel, "y", &m_blackboard->m_camDir.y);
	spinner->set_float_limits(-1, 1);
	spinner = new GLUI_Spinner(cam_dir_panel, "z", &m_blackboard->m_camDir.z);
	spinner->set_float_limits(-1, 1);
}