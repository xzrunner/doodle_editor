#include "SetValueDialog.h"
#include "Edit/Utility.h"
#include "glui/glui.h"

using namespace FEDITOR;

float* SetValueDialog::m_floatVal = NULL;
int* SetValueDialog::m_intVal = NULL;

GLUI_Button* SetValueDialog::m_setBtn = NULL;
GLUI_EditText* SetValueDialog::m_setEditText = NULL;

void SetValueDialog::create(GLUI_Panel* parent, const std::string& name, float* value)
{
	m_floatVal = value;
	m_intVal = NULL;
	m_setBtn = new GLUI_Button(parent, name.c_str(), e_Set, callback);
}

void SetValueDialog::create(GLUI_Panel* parent, const std::string& name, int* value)
{
	m_floatVal = NULL;
	m_intVal = value;
	m_setBtn = new GLUI_Button(parent, name.c_str(), e_Set, callback);
}

void SetValueDialog::callback(GLUI_Control* control)
{
	switch (control->get_id())
	{
	case e_Set:
		{
			GLUI* wnd = GLUI_Master.create_glui("Set", 0, 800, 400);
			if (m_floatVal) m_setEditText = new GLUI_EditText(wnd, "Set: ", m_floatVal);
			else if (m_intVal) m_setEditText = new GLUI_EditText(wnd, "Set: ", m_intVal);
			else assert(0); 
			
			new GLUI_Button(wnd, "OK", e_Ok, callback);
			new GLUI_Button(wnd, "Cancel", e_Cancel, callback);

			control->disable();
		}
		break;
	case e_Ok:
		m_setBtn->enable();
		control->glui->close();
		if (m_floatVal) *m_floatVal = m_setEditText->get_float_val();
		else if (m_intVal) *m_intVal = m_setEditText->get_int_val();
		else assert(0);
		break;
	case e_Cancel:
		m_setBtn->enable();
		control->glui->close();
		break;
	}
}