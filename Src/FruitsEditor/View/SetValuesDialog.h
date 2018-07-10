#ifndef _FEDITOR_SET_VALUES_DIALOG_H_
#define _FEDITOR_SET_VALUES_DIALOG_H_
#include <Fruits2D/Fruits2D.h>

class GLUI_Control;
class GLUI_Panel;
class GLUI_Button;
class GLUI_EditText;

namespace FEDITOR
{
	class SetValuesDialog
	{
	public:
		static void create(GLUI_Panel* parent, const std::vector<std::string>& names, 
			const std::vector<int*>& values);

	private:
		enum
		{
			e_Set,
			e_Ok,
			e_Cancel
		};

		static void callback(GLUI_Control* control);

	private:
		static std::vector<std::string> m_names;
		static std::vector<int*> m_values; 

		static GLUI_Button* m_setBtn;
		static std::vector<GLUI_EditText*> m_setEditText;

	}; // SetValuesDialog
}

#endif // _FEDITOR_SET_VALUES_DIALOG_H_