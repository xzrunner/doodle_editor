#include "UICtrlsMgr.h"
#include "Blackboard.h"
#include "Edit/EditComponent/CmptMgr.h"
#include "Edit/EditComponent/CmptTypeID.h"
#include "glui/glui.h"

using namespace FEDITOR;
using namespace FEDITOR::EXTRACT_EDGE;

GLUI_FileBrowser* UICtrlsMgr::m_background_fb = NULL;

UICtrlsMgr::UICtrlsMgr(Blackboard* blackboard)
{
	m_blackboard = blackboard;
}

void UICtrlsMgr::createUIControls(CmptMgr& cmptMgr, ShortcutKeyListener* shortcutLsn)
{
	buildInputPanel();
	buildCoordLinesPanel();
	buildEditorPanel(cmptMgr, shortcutLsn);
	buildAutoPanel();
}

void UICtrlsMgr::callback(int id)
{
	switch (id)
	{
	case Blackboard::e_OpenFile:
		m_eventList.push(Event(id, m_background_fb->get_file()));
		break;
	default:
		m_eventList.push(Event(id));
	}
}

void UICtrlsMgr::buildInputPanel()
{
	m_background_fb = new GLUI_FileBrowser(m_root, "Open", true, Blackboard::e_OpenFile, callback);
}

void UICtrlsMgr::buildCoordLinesPanel()
{
	GLUI_Panel* panel = new GLUI_Panel(m_root, "Coordinate");

	new GLUI_Checkbox(panel, "visible", &m_blackboard->m_drawCoordLines, Blackboard::e_SetCoordLinesVisible, callback);

	GLUI_RadioGroup* original_choose = new GLUI_RadioGroup(panel, &m_blackboard->m_coordsType, Blackboard::e_ChangeCoordLines, callback);
	new GLUI_RadioButton(original_choose, "center");
	new GLUI_RadioButton(original_choose, "left low");
	new GLUI_RadioButton(original_choose, "left top");
}

void UICtrlsMgr::buildEditorPanel(CmptMgr& cmptMgr, ShortcutKeyListener* shortcutLsn)
{
	GLUI_Panel* panel = new GLUI_Panel(m_root, "Edit Tools");

	cmptMgr.createUIControls(panel, e_DrawPolylineCmpt, shortcutLsn);

	new GLUI_Button(panel, "Save", Blackboard::e_SavePolyline, callback);
}

void UICtrlsMgr::buildAutoPanel()
{
	GLUI_Panel* panel = new GLUI_Panel(m_root, "Auto");

	GLUI_Spinner* color = new GLUI_Spinner(panel, "color tolerance", &m_blackboard->m_colorTolerance, Blackboard::e_SetColorTol, callback);
	color->set_int_limits(0, 15);
	GLUI_Spinner* edge = new GLUI_Spinner(panel, "edge tolerance", &m_blackboard->m_edgeTolerance, Blackboard::e_SetEdgeTol, callback);
	edge->set_float_limits(0, 50);

	new GLUI_Button(panel, "Select", Blackboard::e_AutoSelect, callback);
}