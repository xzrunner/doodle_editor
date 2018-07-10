#include "UICtrlsMgr.h"
#include "Blackboard.h"
#include "glui/glui.h"

using namespace FEDITOR;
using namespace FEDITOR::CHESSBOARD;

int UICtrlsMgr::m_openFileType = 0;

GLUI_FileBrowser* UICtrlsMgr::m_common_fb = NULL;

UICtrlsMgr::UICtrlsMgr(Blackboard* blackboard)
{
	m_blackboard = blackboard;
}

void UICtrlsMgr::createUIControls(CmptMgr& cmptMgr, ShortcutKeyListener* shortcutLsn)
{
	buildIOPanel();
	buildSettingPanel();
}

void UICtrlsMgr::callback(int id)
{
 	switch (id)
 	{
	case e_OpenFile:
		switch (m_openFileType)
		{
		case 0:
			m_eventList.push(Event(Blackboard::e_openTile, m_common_fb->get_file()));
			break;
		case 1:
			m_eventList.push(Event(Blackboard::e_openLevel, m_common_fb->get_file()));
			break;
		}
		break;
	default:
		m_eventList.push(Event(id));
 	}
}

void UICtrlsMgr::buildIOPanel()
{
	GLUI_Panel* panel = new GLUI_Panel(m_root, "I/O");

	GLUI_RadioGroup* choose = new GLUI_RadioGroup(panel, &m_openFileType);
	new GLUI_RadioButton(choose, "Tile (*.jpg, *.png)");
	new GLUI_RadioButton(choose, "Level (*_tilechess.txt)");

	m_common_fb = new GLUI_FileBrowser(panel, "", false, e_OpenFile, callback);

	new GLUI_Button(panel, "Save", Blackboard::e_saveLevel, callback);
}

void UICtrlsMgr::buildSettingPanel()
{
	GLUI_Panel* panel = new GLUI_Panel(m_root, "Settings");

	GLUI_Spinner* row = new GLUI_Spinner(panel, "row", &m_blackboard->m_row, Blackboard::e_resizeBg, callback);
	row->set_int_limits(5, 50);
	GLUI_Spinner* col = new GLUI_Spinner(panel, "col", &m_blackboard->m_col, Blackboard::e_resizeBg, callback);
	col->set_int_limits(5, 50);
	GLUI_Spinner* edge = new GLUI_Spinner(panel, "edge", &m_blackboard->m_edge, Blackboard::e_resizeBg, callback);
	edge->set_int_limits(30, 100);
}