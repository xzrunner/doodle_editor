#ifndef _DEDITOR_COMBINATION_STAGE_CANVAS_H_
#define _DEDITOR_COMBINATION_STAGE_CANVAS_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace combination
	{
		class StagePanel;

		class StageCanvas : public wxgui::GLCanvas
		{
		public:
			StageCanvas(StagePanel* editPanel);
			virtual ~StageCanvas();

		protected:
			virtual void onDraw();

		private:
			void drawGuideLines();

		private:
			wxgui::SpriteBatch m_batch;

		}; // StageCanvas
	}
}

#endif // _DEDITOR_COMBINATION_STAGE_CANVAS_H_