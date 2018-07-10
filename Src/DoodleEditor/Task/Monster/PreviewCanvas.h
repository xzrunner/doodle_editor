#ifndef _DEDITOR_MONSTER_PREVIEW_CANVAS_H_
#define _DEDITOR_MONSTER_PREVIEW_CANVAS_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace monster
	{
		class StagePanel;

		class PreviewCanvas : public wxgui::GLCanvas
		{
		public:
			PreviewCanvas(wxgui::EditPanel* editPanel, StagePanel* stagePanel, 
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
			class DrawVisitor : public IVisitor
			{
			public:
				DrawVisitor(float yOffset) : m_yOffset(yOffset) {}

				virtual void visit(IObject* object, bool& bFetchNext);

			private:
				float m_yOffset;

			}; // DrawVisitor

		private:
			StagePanel* m_stagePanel;

			wxgui::LibraryPanel* m_libraryPanel;

			wxTimer m_timer;
			float m_yOffset;

			DECLARE_EVENT_TABLE()

		}; // PreviewCanvas
	}
}

#endif // _DEDITOR_MONSTER_PREVIEW_CANVAS_H_