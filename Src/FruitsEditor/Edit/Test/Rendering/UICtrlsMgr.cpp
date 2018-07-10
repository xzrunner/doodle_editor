#include "UICtrlsMgr.h"
#include "Blackboard.h"
#include "View/SetValueDialog.h"
#include "glui/glui.h"

using namespace FEDITOR;
using namespace FEDITOR::TEST_RENDERING;

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
	case Blackboard::e_Open:
		m_eventList.push(Event(id, m_common_fb->get_file()));
		break;
	default:
		m_eventList.push(Event(id));
 	}
}

void UICtrlsMgr::buildIOPanel()
{
	GLUI_Panel* panel = new GLUI_Panel(m_root, "I/O");
	m_common_fb = new GLUI_FileBrowser(panel, "", false, Blackboard::e_Open, callback);
}

void UICtrlsMgr::buildSettingPanel()
{
	GLUI_Panel* panel = new GLUI_Panel(m_root, "Settings");

	SetValueDialog::create(panel, "set number ...", &m_blackboard->m_num);

	GLUI_RadioGroup* typeChoose = new GLUI_RadioGroup(panel, &m_blackboard->m_renderType);
	new GLUI_RadioButton(typeChoose, "immediate");
	new GLUI_RadioButton(typeChoose, "bindOneTime");
	new GLUI_RadioButton(typeChoose, "bindOneTime_Strip");
	new GLUI_RadioButton(typeChoose, "bindOneTime_Strip_Depth");
	new GLUI_RadioButton(typeChoose, "drawArrays");
	new GLUI_RadioButton(typeChoose, "drawElements");
	new GLUI_RadioButton(typeChoose, "drawElements_interleave");
	new GLUI_RadioButton(typeChoose, "drawRangeElements");
	new GLUI_RadioButton(typeChoose, "displayList");
	new GLUI_RadioButton(typeChoose, "VBO");

	new GLUI_Checkbox(panel, "Transparent", &m_blackboard->m_isTransparent);
}