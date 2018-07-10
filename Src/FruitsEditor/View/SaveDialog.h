#ifndef _FEDITOR_SAVE_DIALOG_H_
#define _FEDITOR_SAVE_DIALOG_H_
#include <Fruits2D/Fruits2D.h>
#include "Edit/Utility.h"

class GLUI_Panel;
class GLUI_Control;
class GLUI_Button;
class GLUI_EditText;

namespace FEDITOR
{
	class SaveDialog
	{
	public:
		static void create(GLUI_Panel* parent, std::queue<Event>* eventList, int id);

	private:
		enum
		{
			e_Open,
			e_Ok,
			e_Cancel	
		};

		static void callback(GLUI_Control* control);

	private:
		static std::queue<Event>* m_eventList;
		static int m_id;

		static GLUI_Button* m_saveBtn;
		static GLUI_EditText* m_saveEditText;

	}; // SaveDialog
}

#endif // _FEDITOR_SAVE_DIALOG_H_