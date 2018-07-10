#ifndef _DEDITOR_MOTOX_ACTOR_EDIT_CANVAS_H_
#define _DEDITOR_MOTOX_ACTOR_EDIT_CANVAS_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class AEEditPanel;

		class AECanvas : public wxgui::GLCanvas
		{
		public:
			AECanvas(AEEditPanel* editPanel);

		protected:
			virtual void initGL();
			virtual void onDraw();

			void onMouse(wxMouseEvent& event);
			void onKeyDown(wxKeyEvent& event);

		private:
			void drawGuideLines();

		private:
			AEEditPanel* m_editPanel;

			wxgui::SpriteBatch m_batch;

			DECLARE_EVENT_TABLE()

		}; // AECanvas
	}
}

#endif // _DEDITOR_MOTOX_ACTOR_EDIT_CANVAS_H_