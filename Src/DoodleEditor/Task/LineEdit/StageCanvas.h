#ifndef _DEDITOR_LINE_EDIT_STAGE_CANVAS_H_
#define _DEDITOR_LINE_EDIT_STAGE_CANVAS_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace line_edit
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

		}; // StageCanvas
	}
}

#endif // _DEDITOR_LINE_EDIT_STAGE_CANVAS_H_