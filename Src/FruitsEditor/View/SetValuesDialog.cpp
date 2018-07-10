#include "SetValuesDialog.h"
#include "glui/glui.h"

using namespace FEDITOR;

std::vector<std::string> SetValuesDialog::m_names;
std::vector<int*> SetValuesDialog::m_values; 

GLUI_Button* SetValuesDialog::m_setBtn = NULL;
std::vector<GLUI_EditText*> SetValuesDialog::m_setEditText;

void SetValuesDialog::create(GLUI_Panel* parent, const std::vector<std::string>& names, 
							 const std::vector<int*>& values)
{
	m_names.clear();
	m_values.clear();
	copy(names.begin(), names.end(), back_inserter(m_names));
	copy(values.begin(), values.end(), back_inserter(m_values));
	m_setBtn = new GLUI_Button(parent, "Setting ...", e_Set, callback);
}

void SetValuesDialog::callback(GLUI_Control* control)
{
	switch (control->get_id())
	{
	case e_Set:
		{
			m_setEditText.clear();

			GLUI* wnd = GLUI_Master.create_glui("Set", 0, 800, 400);
			for (size_t i = 0, n = m_values.size(); i < n; ++i)
			{
				GLUI_EditText* editText = new GLUI_EditText(wnd, (m_names[i] + ": ").c_str(), m_values[i]);
				m_setEditText.push_back(editText);
			}

			GLUI_Panel* panel = new GLUI_Panel(wnd, "", false);
			new GLUI_Button(panel, "OK", e_Ok, callback);
			new GLUI_Column(panel, false);
			new GLUI_Button(panel, "Cancel", e_Cancel, callback);

			control->disable();
		}
		break;
	case e_Ok:
		m_setBtn->enable();
		control->glui->close();
		for (size_t i = 0, n = m_values.size(); i < n; ++i)
			*m_values[i] = m_setEditText[i]->get_int_val();
		break;
	case e_Cancel:
		m_setBtn->enable();
		control->glui->close();
		break;
	}
}