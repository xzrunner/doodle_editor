#ifndef _DEDITOR_HILL_CLIMB_STAGE_CANVAS_H_
#define _DEDITOR_HILL_CLIMB_STAGE_CANVAS_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace hill_climb
	{
		class StagePanel;

		class StageCanvas : public wxgui::ShapeStageCanvas
		{
		public:
			StageCanvas(StagePanel* parent);

		protected:
			virtual void onDraw();

		private:
			void drawGuideLines();

			void drawSurfaces();

		private:
			static const int GUIDE_LINES_WIDTH_TIMES = 100;

			wxgui::SpriteBatch m_batch;

		}; // StageCanvas
	}
}

#endif // _DEDITOR_HILL_CLIMB_STAGE_CANVAS_H_