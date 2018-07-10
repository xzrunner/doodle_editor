#include "SetColorCmpt.h"
#include "CmptTypeID.h"
#include "glui/glui.h"

using namespace FEDITOR;

std::queue<Event> SetColorCmpt::m_eventList;

SetColorCmpt::SetColorCmpt(CmptMgr& cmptMgr, f2Colorf& color)
	: AbstractCmpt(e_SetColorCmpt, cmptMgr), m_color(color)
{
	m_r = m_g = m_b = 0;
	m_a = 255;
}

void SetColorCmpt::createUIControls(GLUI_Node* parent, ShortcutKeyListener* shortcutLsn)
{
	if (dynamic_cast<GLUI*>(parent))
		largeLayoutUI(parent);
	else
		smallLayoutUI(parent);
}

void SetColorCmpt::handleUIEvent()
{
	while (!m_eventList.empty())
	{
		Event event = m_eventList.front(); m_eventList.pop();
		switch (event.getID())
		{
		case e_SetColor:
			m_color.r = m_r / 255.0f;
			m_color.g = m_g / 255.0f;
			m_color.b = m_b / 255.0f;
			m_color.a = m_a / 255.0f;
			break;
		}
	}
}

void SetColorCmpt::smallLayoutUI(GLUI_Node* parent)
{
	GLUI_Spinner* color;
	color = new GLUI_Spinner(parent, "r", &m_r, e_SetColor, callback);
	color->set_int_limits(0, 255);
	color = new GLUI_Spinner(parent, "g", &m_g, e_SetColor, callback);
	color->set_int_limits(0, 255);
	color = new GLUI_Spinner(parent, "b", &m_b, e_SetColor, callback);
	color->set_int_limits(0, 255);
	color = new GLUI_Spinner(parent, "a", &m_a, e_SetColor, callback);
	color->set_int_limits(0, 255);
}

void SetColorCmpt::largeLayoutUI(GLUI_Node* parent)
{
	GLUI_Panel* panel = new GLUI_Panel(parent, "Color Set");

	GLUI_Spinner* color;
	color = new GLUI_Spinner(panel, "r", &m_r, e_SetColor, callback);
	color->set_int_limits(0, 255);
	color = new GLUI_Spinner(panel, "g", &m_g, e_SetColor, callback);
	color->set_int_limits(0, 255);
	color = new GLUI_Spinner(panel, "b", &m_b, e_SetColor, callback);
	color->set_int_limits(0, 255);
	color = new GLUI_Spinner(panel, "a", &m_a, e_SetColor, callback);
	color->set_int_limits(0, 255);
}

void SetColorCmpt::callback(int id)
{
	m_eventList.push(Event(id));
}