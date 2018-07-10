#include "SaveDialog.h"
#include "glui/glui.h"

using namespace FEDITOR;

std::queue<Event>* SaveDialog::m_eventList = NULL;
int SaveDialog::m_id = -1;

GLUI_Button* SaveDialog::m_saveBtn = NULL;
GLUI_EditText* SaveDialog::m_saveEditText = NULL;

void SaveDialog::create(GLUI_Panel* parent, std::queue<Event>* eventList, int id)
{
	m_eventList = eventList;
	m_id = id;
	m_saveBtn = new GLUI_Button(parent, "Save...", e_Open, callback);
}

void SaveDialog::callback(GLUI_Control* control)
{
	switch (control->get_id())
	{
	case e_Open:
		{
			GLUI* wnd = GLUI_Master.create_glui("Save", 0, 800, 400);
			m_saveEditText = new GLUI_EditText(wnd, "File Name: ");
			new GLUI_Button(wnd, "OK", e_Ok, callback);
			new GLUI_Button(wnd, "Cancel", e_Cancel, callback);

			//			cmd_line_glui->set_main_gfx_window( main_window );

			control->disable();
		}
		break;
	case e_Ok:
		m_saveBtn->enable();
		control->glui->close();
		m_eventList->push(Event(m_id, m_saveEditText->get_text()));
		break;
	case e_Cancel:
		m_saveBtn->enable();
		control->glui->close();
		break;
	}
}