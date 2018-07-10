#ifndef _DEDITOR_MOTOX_TEMPLATE_EDIT_CANVAS_H_
#define _DEDITOR_MOTOX_TEMPLATE_EDIT_CANVAS_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class TEEditPanel;

		class TECanvas : public wxgui::GLCanvas
		{
		public:
			TECanvas(TEEditPanel* editPanel);

		protected:
			virtual void initGL();
			virtual void onDraw();

			void onMouse(wxMouseEvent& event);
			void onKeyDown(wxKeyEvent& event);

		private:
			void drawGuideLines();

		private:
			TEEditPanel* m_editPanel;

			wxgui::SpriteBatch m_batch;

			DECLARE_EVENT_TABLE()

		}; // TECanvas
	}
}

#endif // _DEDITOR_MOTOX_TEMPLATE_EDIT_CANVAS_H_