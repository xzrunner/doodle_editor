#include "UICtrlsMgr.h"
#include "Blackboard.h"
#include "glui/glui.h"

using namespace FEDITOR;
using namespace FEDITOR::MOTOX::PACKAGE;

int UICtrlsMgr::m_openFileType = 0;

GLUI_FileBrowser* UICtrlsMgr::m_common_fb = NULL;

UICtrlsMgr::UICtrlsMgr(Blackboard* blackboard)
{
	m_blackboard = blackboard;
}

void UICtrlsMgr::createUIControls(CmptMgr& cmptMgr, ShortcutKeyListener* shortcutLsn)
{
	buildIOPanel();
}

void UICtrlsMgr::callback(int id)
{
 	switch (id)
 	{
	case e_OpenFile:
 		switch (m_openFileType)
 		{
 		case 0:
 			m_eventList.push(Event(Blackboard::e_packTrackChains, m_common_fb->get_file()));
 			break;
		case 1:
			m_eventList.push(Event(Blackboard::e_packActor, m_common_fb->get_file()));
			break;
 		}
		break;
	default:
		m_eventList.push(Event(id));
 	}
}

void UICtrlsMgr::buildIOPanel()
{
	GLUI_Panel* panel = new GLUI_Panel(m_root, "Pack");

	GLUI_RadioGroup* choose = new GLUI_RadioGroup(panel, &m_openFileType);
	new GLUI_RadioButton(choose, "Track Chains (*_chains.txt)");
	new GLUI_RadioButton(choose, "Actor (actor_motion.txt)");

	m_common_fb = new GLUI_FileBrowser(panel, "", false, e_OpenFile, callback);
}