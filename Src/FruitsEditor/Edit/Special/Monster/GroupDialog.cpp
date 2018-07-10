#include "GroupDialog.h"
#include "Dataset/Sprite.h"
#include "Dataset/SelectionSet.h"
#include "glui/glui.h"

using namespace FEDITOR;
using namespace FEDITOR::MONSTER;

SelectionSet* GroupDialog::m_selection = NULL;

GLUI_Button* GroupDialog::m_queryBtn = NULL;
GLUI_Button* GroupDialog::m_setBtn = NULL;

int GroupDialog::m_groupID = -1;

void GroupDialog::setSelection(SelectionSet* selection)
{
	m_selection = selection;
}

void GroupDialog::createQueryDialog(GLUI_Panel* parent)
{
	m_queryBtn = new GLUI_Button(parent, "Query...", e_OpenQuery, callback);
}

void GroupDialog::createSetDialog(GLUI_Panel* parent)
{
	m_setBtn = new GLUI_Button(parent, "Set...", e_OpenSet, callback);
}

void GroupDialog::callback(GLUI_Control* control)
{
	switch (control->get_id())
	{
	case e_OpenQuery:
		{
			GLUI* wnd = GLUI_Master.create_glui("Group ID", 0, 800, 400);

			const std::set<Sprite*>& sprites = m_selection->getAll();
			if (sprites.size() == 0)
				new GLUI_StaticText(wnd, "Choose empty");
			else if (sprites.size() > 1)
				new GLUI_StaticText(wnd, "Please choose only one");
			else
			{
				float* data = static_cast<float*>((*sprites.begin())->getUserData());
				int id = data[2];

				GLUI_Panel* panel = new GLUI_Panel(wnd, "", false);
				new GLUI_StaticText(panel, "Group is: ");
				new GLUI_Column(panel, false);
				new GLUI_StaticText(panel, StringTools::intToString(id).c_str());
			}
			new GLUI_Button(wnd, "Cancel", e_CancelQuery, callback);

			control->disable();
		}
		break;
	case e_OpenSet:
		{
			GLUI* wnd = GLUI_Master.create_glui("Group ID", 0, 800, 400);
			
			GLUI_Panel* panel = new GLUI_Panel(wnd, "", false);
			new GLUI_StaticText(panel, "Set group: ");
			new GLUI_Column(panel, false);
			new GLUI_EditText(panel, "", &m_groupID);

			GLUI_Panel* btnPanel = new GLUI_Panel(wnd, "", false);
			new GLUI_Button(btnPanel, "Ok", e_OkSet, callback);
			new GLUI_Column(btnPanel, false);
			new GLUI_Button(btnPanel, "Cancel", e_CancelSet, callback);
		}
		break;
	case e_OkSet:
		{
			const std::set<Sprite*>& sprites = m_selection->getAll();
			std::set<Sprite*>::const_iterator itr = sprites.begin();
			for ( ; itr != sprites.end(); ++itr)
			{
				float* data = static_cast<float*>((*itr)->getUserData());
				data[2] = m_groupID;
			}
			m_setBtn->enable();
			control->glui->close();
		}
		break;
	case e_CancelQuery:
		m_queryBtn->enable();
		control->glui->close();
		break;
	case e_CancelSet:
		m_setBtn->enable();
		control->glui->close();
		break;
	}
}