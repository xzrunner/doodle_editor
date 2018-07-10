#ifndef _FEDITOR_SET_VALUE_DIALOG_H_
#define _FEDITOR_SET_VALUE_DIALOG_H_
#include <Fruits2D/Fruits2D.h>

class GLUI_Control;
class GLUI_Panel;
class GLUI_Button;
class GLUI_EditText;

namespace FEDITOR
{
	class SetValueDialog
	{
	public:
		static void create(GLUI_Panel* parent, const std::string& name, float* value);
		static void create(GLUI_Panel* parent, const std::string& name, int* value);

	private:
		enum
		{
			e_Set,
			e_Ok,
			e_Cancel	
		};

		static void callback(GLUI_Control* control);

	private:
		static float* m_floatVal;
		static int* m_intVal;

		static GLUI_Button* m_setBtn;
		static GLUI_EditText* m_setEditText;
	};
}

#endif // _FEDITOR_SET_VALUE_DIALOG_H_