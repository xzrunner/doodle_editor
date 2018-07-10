#include "UICtrlsMgr.h"
#include "Blackboard.h"
#include "glui/glui.h"

using namespace FEDITOR;
using namespace FEDITOR::TEXTURE_MERGE;

GLUI_FileBrowser* UICtrlsMgr::m_common_fb = NULL;

UICtrlsMgr::UICtrlsMgr(Blackboard* blackboard)
{
	m_blackboard = blackboard;
}

void UICtrlsMgr::createUIControls(CmptMgr& cmptMgr, ShortcutKeyListener* shortcutLsn)
{
	buildBgPanel();
	buildIOPanel();
	buildEditPanel();
}

void UICtrlsMgr::callback(int id)
{
 	switch (id)
 	{
	case Blackboard::e_openTexture:
		m_eventList.push(Event(id, m_common_fb->get_file()));
		break; 
	default:
		m_eventList.push(Event(id));
 	}
}

void UICtrlsMgr::buildBgPanel()
{
	GLUI_Panel* panel = new GLUI_Panel(m_root, "Background");

	GLUI_Listbox* widthList = new GLUI_Listbox(panel, "width: ", &m_blackboard->m_widthType, Blackboard::e_resetBg, callback);
	widthList->add_item(Blackboard::SCOPE_EDGE_32, "32");
	widthList->add_item(Blackboard::SCOPE_EDGE_64, "64");
	widthList->add_item(Blackboard::SCOPE_EDGE_128, "128");
	widthList->add_item(Blackboard::SCOPE_EDGE_256, "256");
	widthList->add_item(Blackboard::SCOPE_EDGE_512, "512");
	widthList->add_item(Blackboard::SCOPE_EDGE_1024, "1024");

	GLUI_Listbox* heightList = new GLUI_Listbox(panel, "height: ", &m_blackboard->m_heightType, Blackboard::e_resetBg, callback);
	heightList->add_item(Blackboard::SCOPE_EDGE_32, "32");
	heightList->add_item(Blackboard::SCOPE_EDGE_64, "64");
	heightList->add_item(Blackboard::SCOPE_EDGE_128, "128");
	heightList->add_item(Blackboard::SCOPE_EDGE_256, "256");
	heightList->add_item(Blackboard::SCOPE_EDGE_512, "512");
	heightList->add_item(Blackboard::SCOPE_EDGE_1024, "1024");
}

void UICtrlsMgr::buildIOPanel()
{
	GLUI_Panel* panel = new GLUI_Panel(m_root, "I/O");

	GLUI_Panel* openPanel = new GLUI_Panel(panel, "Open", true);
	m_common_fb = new GLUI_FileBrowser(openPanel, "", false, Blackboard::e_openTexture, callback);

	GLUI_Panel* savePanel = new GLUI_Panel(panel, "Save as", true);
	GLUI_Button* btn;
	btn = new GLUI_Button(savePanel, "bmp", Blackboard::e_saveAsBmp, callback); btn->set_w(20);
	new GLUI_Column(savePanel, false);
	btn = new GLUI_Button(savePanel, "png", Blackboard::e_saveAsPng, callback); btn->set_w(20);
	new GLUI_Column(savePanel, false);
	btn = new GLUI_Button(savePanel, "jpg", Blackboard::e_saveAsJpg, callback); btn->set_w(20);
}

void UICtrlsMgr::buildEditPanel()
{
	
}