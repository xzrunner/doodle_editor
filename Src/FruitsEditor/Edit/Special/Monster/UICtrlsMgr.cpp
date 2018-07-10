#include "UICtrlsMgr.h"
#include "Blackboard.h"
#include "GroupDialog.h"
#include "View/SaveDialog.h"
#include "View/SetValuesDialog.h"
#include "glui/glui.h"

using namespace FEDITOR;
using namespace FEDITOR::MONSTER;

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
	buildGroupPanel();
	new GLUI_Button(m_root, "Play", Blackboard::e_Play, callback);
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

	SaveDialog::create(panel, &m_eventList, Blackboard::e_saveLevel);
}

void UICtrlsMgr::buildSettingPanel()
{
	GLUI_Panel* panel = new GLUI_Panel(m_root, "Settings");

	new GLUI_StaticText(panel, "edge");
	GLUI_Scrollbar* edge = new GLUI_Scrollbar(panel, "edge", GLUI_SCROLL_HORIZONTAL, &m_blackboard->m_edge, Blackboard::e_resizeBg, callback);
	edge->set_int_limits(30, 100);

	new GLUI_Separator(panel);

	GLUI_Spinner* length = new GLUI_Spinner(panel, "length", &m_blackboard->m_length, Blackboard::e_resizeBg, callback);
	length->set_int_limits(30, 200);

	new GLUI_Separator(panel);

// 	SetValueDialog::create(panel, "Set Time ...", &m_blackboard->m_time);
// 	SetValueDialog::create(panel, "Set minEmptyGrid ...", &m_blackboard->m_minEmptyGrid);
// 	SetValueDialog::create(panel, "Set maxEmptyGrid ...", &m_blackboard->m_maxEmptyGrid);

	std::vector<std::string> names;
	std::vector<int*> values;
	names.push_back("Time");	values.push_back(&m_blackboard->m_time);
	names.push_back("MinEmptyGrid");	values.push_back(&m_blackboard->m_minEmptyGrid);
	names.push_back("MaxEmptyGrid");	values.push_back(&m_blackboard->m_maxEmptyGrid);
	SetValuesDialog::create(panel, names, values);
}

void UICtrlsMgr::buildGroupPanel()
{
	GLUI_Panel* panel = new GLUI_Panel(m_root, "Group");

	GroupDialog::createQueryDialog(panel);
	GroupDialog::createSetDialog(panel);
}