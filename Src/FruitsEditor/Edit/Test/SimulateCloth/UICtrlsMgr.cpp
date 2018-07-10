#include "UICtrlsMgr.h"
#include "Blackboard.h"
#include "Edit/EditComponent/CmptMgr.h"
#include "Edit/EditComponent/CmptTypeID.h"
#include "glui/glui.h"

using namespace FEDITOR;
using namespace FEDITOR::SIMULATE_CLOTH;

int UICtrlsMgr::m_openFileType = 0;

GLUI_FileBrowser* UICtrlsMgr::m_common_fb = NULL;

UICtrlsMgr::UICtrlsMgr(Blackboard* blackboard)
{
	m_blackboard = blackboard;
}

void UICtrlsMgr::createUIControls(CmptMgr& cmptMgr, ShortcutKeyListener* shortcutLsn)
{
	cmptMgr.createUIControls(m_root, e_PhysTaskSettingCmpt);
	buildOpenPanel();
	buildEditIrregularPanel(cmptMgr, shortcutLsn);
	buildSettingsPanel();
}

void UICtrlsMgr::callback(int id)
{
	switch (id)
	{
	case e_OpenFile:
		switch (m_openFileType)
		{
		case 0:
			m_eventList.push(Event(Blackboard::e_openRegularTexture, m_common_fb->get_file()));
			break;
		case 1:
			m_eventList.push(Event(Blackboard::e_openIrregularTexture, m_common_fb->get_file()));
			break;
		}
		break;
	default:
		m_eventList.push(Event(id));
	}
}

void UICtrlsMgr::buildOpenPanel()
{
	GLUI_Rollout* open_panel = new GLUI_Rollout(m_root, "Open", true);

	GLUI_RadioGroup* chooseOpen = new GLUI_RadioGroup(open_panel, &m_openFileType);
	new GLUI_RadioButton(chooseOpen, "Regular Img (*.jpg, *.png)");
	new GLUI_RadioButton(chooseOpen, "Irregular Fill (*_fill.txt)");

	m_common_fb = new GLUI_FileBrowser(open_panel, "", false, e_OpenFile, callback);
}

void UICtrlsMgr::buildEditIrregularPanel(CmptMgr& cmptMgr, ShortcutKeyListener* shortcutLsn)
{
	GLUI_Panel* edit_panel = new GLUI_Panel(m_root, "Edit Irregular");

	GLUI_Panel* bounding = new GLUI_Panel(edit_panel, "Bounding");
	cmptMgr.createUIControls(bounding, e_DrawPolylineCmpt, shortcutLsn);

	GLUI_Panel* inner = new GLUI_Panel(edit_panel, "Inner");
}

void UICtrlsMgr::buildSettingsPanel()
{
	GLUI_Rollout* settings_panel = new GLUI_Rollout(m_root, "Params", true);

	GLUI_Spinner* hz = new GLUI_Spinner(settings_panel, "hz", &m_blackboard->m_frequencyHz, Blackboard::e_resetJointsFrequency, callback);
	hz->set_float_limits(0, 5);
	GLUI_Spinner* damping = new GLUI_Spinner(settings_panel, "damping", &m_blackboard->m_dampingRatio, Blackboard::e_resetJointsDamping, callback);
	damping->set_float_limits(0, 2);

	GLUI_Spinner* edge = new GLUI_Spinner(settings_panel, "node half edge", &m_blackboard->m_nodeHalfEdge, Blackboard::e_resetNodesEdge, callback);
	edge->set_float_limits(0.01f, 5.0f);

	GLUI_Panel* regular_panel = new GLUI_Panel(settings_panel, "regular", true);

	GLUI_Spinner* row = new GLUI_Spinner(regular_panel, "row", &m_blackboard->m_row, Blackboard::e_resetWeb, callback);
	row->set_int_limits(2, 15);
	GLUI_Spinner* col = new GLUI_Spinner(regular_panel, "col", &m_blackboard->m_col, Blackboard::e_resetWeb, callback);
	col->set_int_limits(2, 15);

	new GLUI_Checkbox(regular_panel, "Bound Static", &m_blackboard->m_boundStatic, Blackboard::e_resetWeb, callback);
	new GLUI_Checkbox(regular_panel, "Connect Center", &m_blackboard->m_connectNodeCenter, Blackboard::e_resetWeb, callback);
}