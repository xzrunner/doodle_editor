#include "UICtrlsMgr.h"
#include "Blackboard.h"
#include "Edit/EditComponent/CmptMgr.h"
#include "Edit/EditComponent/CmptTypeID.h"
#include "glui/glui.h"

using namespace FEDITOR;
using namespace FEDITOR::FILL_COLOR;

int UICtrlsMgr::m_openFileType = 0;
int UICtrlsMgr::m_saveFileType = 0;

GLUI_FileBrowser* UICtrlsMgr::m_common_fb = NULL;

UICtrlsMgr::UICtrlsMgr(Blackboard* blackboard)
{
	m_blackboard = blackboard;
}

void UICtrlsMgr::createUIControls(CmptMgr& cmptMgr, ShortcutKeyListener* shortcutLsn)
{
	cmptMgr.createUIControls(m_root, e_LayersMgrCmpt);
	buildIOPanel();
	cmptMgr.createUIControls(m_root, e_DrawPolylineCmpt, shortcutLsn);
	buildColorPanel(cmptMgr);
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
			m_eventList.push(Event(Blackboard::e_OpenChains, m_common_fb->get_file()));
			break;
		case 1:
			m_eventList.push(Event(Blackboard::e_OpenTris, m_common_fb->get_file()));
			break;
		case 2:
			m_eventList.push(Event(Blackboard::e_OpenImg, m_common_fb->get_file()));
			break;
		case 3:
			m_eventList.push(Event(Blackboard::e_OpenFill, m_common_fb->get_file()));
			break;
		}
		break;
	case e_SaveFile:
		switch (m_saveFileType)
		{
		case 0:
			m_eventList.push(Event(Blackboard::e_SaveTris));
			break;
		case 1:
			m_eventList.push(Event(Blackboard::e_SaveFill));
			break;
		}
		break;
	default:
		m_eventList.push(Event(id));
	}
}

void UICtrlsMgr::buildIOPanel()
{
	GLUI_Rollout* panel = new GLUI_Rollout(m_root, "I/O", true);

	GLUI_Panel* panelOpen = new GLUI_Panel(panel, "Open");

	GLUI_RadioGroup* chooseOpen = new GLUI_RadioGroup(panelOpen, &m_openFileType);
	new GLUI_RadioButton(chooseOpen, "Chains (*_chains.txt)");
	new GLUI_RadioButton(chooseOpen, "Triangles (*_tris.txt)");
	new GLUI_RadioButton(chooseOpen, "Img (*.jpg, *.png)");
	new GLUI_RadioButton(chooseOpen, "Fill (*_fill.txt)");

	m_common_fb = new GLUI_FileBrowser(panelOpen, "", false, e_OpenFile, callback);

	GLUI_Panel* panelSave = new GLUI_Panel(panel, "Save");

	GLUI_RadioGroup* chooseSave = new GLUI_RadioGroup(panelSave, &m_saveFileType);
	new GLUI_RadioButton(chooseSave, "Color (track_tris.txt)");
	new GLUI_RadioButton(chooseSave, "Fill (track_fill.txt)");

	new GLUI_Button(panelSave, "Save", e_SaveFile, callback);
}

void UICtrlsMgr::buildColorPanel(CmptMgr& cmptMgr)
{
	GLUI_Panel* panel = new GLUI_Panel(m_root, "Color");

	cmptMgr.createUIControls(panel, e_SetColorCmpt);
	new GLUI_Button(panel, "set", Blackboard::e_SetColor, callback);
}

void UICtrlsMgr::buildSettingPanel()
{
	GLUI_Panel* panel = new GLUI_Panel(m_root, "Setting");
	new GLUI_Checkbox(panel, "Select Control Points", &m_blackboard->m_flagSelectCtlpos, Blackboard::e_ChangeSelectFlag, callback);
}