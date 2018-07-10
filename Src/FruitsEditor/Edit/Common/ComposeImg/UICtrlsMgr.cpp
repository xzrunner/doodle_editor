#include "UICtrlsMgr.h"
#include "Blackboard.h"
#include "Edit/EditComponent/CmptMgr.h"
#include "Edit/EditComponent/CmptTypeID.h"
#include "View/SaveDialog.h"
#include "glui/glui.h"

using namespace FEDITOR;
using namespace FEDITOR::COMPOSE_IMG;

int UICtrlsMgr::m_openFileType = 0;

GLUI_FileBrowser* UICtrlsMgr::m_common_fb = NULL;

UICtrlsMgr::UICtrlsMgr(Blackboard* blackboard)
{
	m_blackboard = blackboard;
}

void UICtrlsMgr::createUIControls(CmptMgr& cmptMgr, ShortcutKeyListener* shortcutLsn)
{
	buildOpenPanel();
	cmptMgr.createUIControls(m_root, e_GuidelinesCmpt);
	cmptMgr.createUIControls(m_root, e_CoordinateAxesCmpt);
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
		}
		break;
	default:
		m_eventList.push(Event(id));
	}
}

void UICtrlsMgr::buildOpenPanel()
{
	GLUI_Panel* panel = new GLUI_Panel(m_root, "Open");

	GLUI_RadioGroup* choose = new GLUI_RadioGroup(panel, &m_openFileType);
	new GLUI_RadioButton(choose, "Background (*.jpg, *.png)");
	new GLUI_RadioButton(choose, "Tile Sprite (*.jpg, *.png)");
	new GLUI_RadioButton(choose, "Level (*.txt)");

	m_common_fb = new GLUI_FileBrowser(panel, "", false, e_OpenFile, callback);

	SaveDialog::create(panel, &m_eventList, Blackboard::e_SaveLevel);
}