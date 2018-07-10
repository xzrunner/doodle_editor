#include "PasteSpriteSetCmpt.h"
#include "CmptTypeID.h"
#include "glui/glui.h"

using namespace FEDITOR;

PasteSpriteSetCmpt::PasteSpriteSetCmpt(CmptMgr& cmptMgr)
	: AbstractCmpt(e_PasteSpriteSetCmpt, cmptMgr)
{
	m_scale = 1.0f;
	m_mirrorType = 0;
}

void PasteSpriteSetCmpt::createUIControls(GLUI_Node* parent, ShortcutKeyListener* shortcutLsn)
{
	if (dynamic_cast<GLUI*>(parent))
		largeLayoutUI(parent);
	else
		smallLayoutUI(parent);
}

void PasteSpriteSetCmpt::handleUIEvent()
{

}

void PasteSpriteSetCmpt::getScale(float& x, float& y) const
{
	x = m_scale;
	y = m_scale;
	if (m_mirrorType == 1 || m_mirrorType == 3) x = -m_scale;
	if (m_mirrorType == 2 || m_mirrorType == 3) y = -m_scale;
}

void PasteSpriteSetCmpt::smallLayoutUI(GLUI_Node* parent)
{
	new GLUI_StaticText(parent, "Scale Setting");

	new GLUI_Spinner(parent, "scale", &m_scale);

	GLUI_Listbox* choose = new GLUI_Listbox(parent, "mirror\t", &m_mirrorType);
	choose->add_item(0, "Null");
	choose->add_item(1, "X");
	choose->add_item(2, "Y");
	choose->add_item(3, "XY");

	new GLUI_Separator(parent);
}

void PasteSpriteSetCmpt::largeLayoutUI(GLUI_Node* parent)
{
	GLUI_Panel* panel = new GLUI_Panel(parent, "Scale Setting");

	new GLUI_Spinner(panel, "scale", &m_scale);

	GLUI_Listbox* choose = new GLUI_Listbox(panel, "mirror\t", &m_mirrorType);
	choose->add_item(0, "Null");
	choose->add_item(1, "X");
	choose->add_item(2, "Y");
	choose->add_item(3, "XY");
}