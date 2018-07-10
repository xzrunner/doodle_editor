#ifndef _DEDITOR_MODELING_PREVIEW_CANVAS_H_
#define _DEDITOR_MODELING_PREVIEW_CANVAS_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace modeling
	{
		class PreviewPanel;

		class PreviewCanvas : public wxgui::GLCanvas
		{
		public:
			PreviewCanvas(PreviewPanel* editPanel, 
				wxgui::LibraryPanel* libraryPanel);
			virtual ~PreviewCanvas();

		protected:
			virtual void initGL();
			virtual void onDraw();

			void onTimer(wxTimerEvent& event);

		private:
			enum
			{
				TIMER_ID = 1000
			};

			static const int FRAME_RATE = 60;

		private:
			wxgui::LibraryPanel* m_libraryPanel;

			wxTimer m_timer;

			DECLARE_EVENT_TABLE()

		}; // PreviewCanvas
	}
}

#endif // _DEDITOR_MODELING_PREVIEW_CANVAS_H_