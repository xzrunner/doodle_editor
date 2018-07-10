#include "PhysTaskSettingCmpt.h"
#include "CmptTypeID.h"
#include "glui/glui.h"

using namespace FEDITOR;

PhysTaskSettingCmpt::PhysTaskSettingCmpt(CmptMgr& cmptMgr)
	: AbstractCmpt(e_PhysTaskSettingCmpt, cmptMgr)
{
	m_stepFlag = m_drawFlag = 1;

	m_hz = 60;
	m_velocityIterations = 8;
	m_positionIterations = 3;
}

void PhysTaskSettingCmpt::createUIControls(GLUI_Node* parent, ShortcutKeyListener* shortcutLsn)
{
	if (dynamic_cast<GLUI*>(parent))
		largeLayoutUI(parent);
	else
		smallLayoutUI(parent);
}

void PhysTaskSettingCmpt::handleUIEvent()
{
}

void PhysTaskSettingCmpt::smallLayoutUI(GLUI_Node* parent)
{
	GLUI_Panel* panel = new GLUI_Panel(parent, "phys");

	new GLUI_Checkbox(panel, "Step", &m_stepFlag);
	new GLUI_Column(panel);
	new GLUI_Checkbox(panel, "Display", &m_drawFlag);
}

void PhysTaskSettingCmpt::largeLayoutUI(GLUI_Node* parent)
{
	GLUI_Panel* panel = new GLUI_Panel(parent, "Physics Settings");

	new GLUI_Checkbox(panel, "Step Physics", &m_stepFlag);
	new GLUI_Checkbox(panel, "Display Physics", &m_drawFlag);
}