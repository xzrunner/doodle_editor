#ifndef _FEDITOR_MONSTER_GROUP_DIALOG_H_
#define _FEDITOR_MONSTER_GROUP_DIALOG_H_
#include <Fruits2D/Fruits2D.h>

class GLUI_Panel;
class GLUI_Control;
class GLUI_Button;
class GLUI_EditText;

namespace FEDITOR
{
	class SelectionSet;

	namespace MONSTER
	{
		class GroupDialog
		{
		public:
			static void setSelection(SelectionSet* selection);

			static void createQueryDialog(GLUI_Panel* parent);
			static void createSetDialog(GLUI_Panel* parent);

		private:
			enum
			{
				e_OpenQuery,
				e_OpenSet,
				e_OkSet,
				e_CancelQuery,
				e_CancelSet
			};

			static void callback(GLUI_Control* control);

		private:
			static SelectionSet* m_selection;

			static GLUI_Button *m_queryBtn, *m_setBtn;
			static int m_groupID;

		}; // GroupDialog
	}
}

#endif // _FEDITOR_MONSTER_GROUP_DIALOG_H_