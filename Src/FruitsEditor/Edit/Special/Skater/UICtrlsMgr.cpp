#include "UICtrlsMgr.h"
#include "Blackboard.h"
#include "Edit/EditComponent/CmptMgr.h"
#include "Edit/EditComponent/CmptTypeID.h"
#include "View/SaveDialog.h"
#include "glui/glui.h"

using namespace FEDITOR;
using namespace FEDITOR::SKATER;

int UICtrlsMgr::m_openFileType = 0;

GLUI_FileBrowser* UICtrlsMgr::m_common_fb = NULL;

UICtrlsMgr::UICtrlsMgr(Blackboard* blackboard)
{
	m_blackboard = blackboard;
}

void UICtrlsMgr::createUIControls(CmptMgr& cmptMgr, ShortcutKeyListener* shortcutLsn)
{
	cmptMgr.createUIControls(m_root, e_LayersMgrCmpt);
	buildIOPanel();
	buildSettingPanel(cmptMgr, shortcutLsn);
}

void UICtrlsMgr::callback(int id)
{
 	switch (id)
 	{
	case e_OpenFile:
		switch (m_openFileType)
		{
		case 0:
			m_eventList.push(Event(Blackboard::e_OpenBackground, m_common_fb->get_file()));
			break;
		case 1:
			m_eventList.push(Event(Blackboard::e_OpenTile, m_common_fb->get_file()));
			break;
		case 2:
			m_eventList.push(Event(Blackboard::e_OpenLevel, m_common_fb->get_file()));
			break;
		case 3:
			m_eventList.push(Event(Blackboard::e_OpenOldVersion, m_common_fb->get_file()));
			break;
		case 4:
			m_eventList.push(Event(Blackboard::e_OpenBound, m_common_fb->get_file()));
			break;
		}
		break;
	default:
		m_eventList.push(Event(id));
 	}
}

void UICtrlsMgr::buildIOPanel()
{
	GLUI_Rollout* panel = new GLUI_Rollout(m_root, "I/O");

	GLUI_RadioGroup* choose = new GLUI_RadioGroup(panel, &m_openFileType);
	new GLUI_RadioButton(choose, "Background (*.jpg, *.png)");
	new GLUI_RadioButton(choose, "Tile Sprite (*.jpg, *.png)");
	new GLUI_RadioButton(choose, "Level (*_skater.txt)");
	new GLUI_RadioButton(choose, "Old Version(*.txt)");
	new GLUI_RadioButton(choose, "Sprite Bound(*_loops.txt)");

	m_common_fb = new GLUI_FileBrowser(panel, "", false, e_OpenFile, callback);

	SaveDialog::create(panel, &m_eventList, Blackboard::e_SaveLevel);
}

void UICtrlsMgr::buildSettingPanel(CmptMgr& cmptMgr, ShortcutKeyListener* shortcutLsn)
{
	GLUI_Rollout* panel = new GLUI_Rollout(m_root, "Settings");
	cmptMgr.createUIControls(panel, e_PasteSpriteSetCmpt);

	cmptMgr.createUIControls(panel, e_DrawPolylineCmpt, shortcutLsn);
	new GLUI_Button(panel, "Save", Blackboard::e_SaveTrack, callback);

//	buildSetTexCoordPanel(panel);
//	cmptMgr.createUIControls(panel, e_GuidelinesCmpt);
}

void UICtrlsMgr::buildSetTexCoordPanel(GLUI_Panel* parent)
{
	GLUI_Panel* panel = new GLUI_Panel(parent, "Tex Coords");

 	GLUI_Scrollbar* left = new GLUI_Scrollbar(panel, "Left", GLUI_SCROLL_HORIZONTAL, &m_blackboard->m_texCoordLeft, Blackboard::e_SetTexCoords, callback);
 	GLUI_Scrollbar* right = new GLUI_Scrollbar(panel, "Right", GLUI_SCROLL_HORIZONTAL, &m_blackboard->m_texCoordRight, Blackboard::e_SetTexCoords, callback);
 	GLUI_Scrollbar* down = new GLUI_Scrollbar(panel, "Down", GLUI_SCROLL_HORIZONTAL, &m_blackboard->m_texCoordDown, Blackboard::e_SetTexCoords, callback);
 	GLUI_Scrollbar* up = new GLUI_Scrollbar(panel, "Up", GLUI_SCROLL_HORIZONTAL, &m_blackboard->m_texCoordUp, Blackboard::e_SetTexCoords, callback);
 	left->set_float_limits(0.0f, 0.9f);
 	right->set_float_limits(0.1f, 1.0f);
 	down->set_float_limits(0.0f, 0.9f);
 	up->set_float_limits(0.1f, 1.0f);
}