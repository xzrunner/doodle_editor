#ifndef _DEDITOR_BOUNDARY_EXTRACTION_STAGE_CANVAS_H_
#define _DEDITOR_BOUNDARY_EXTRACTION_STAGE_CANVAS_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace boundary_extraction
	{
		class StagePanel;

		class StageCanvas : public wxgui::ShapeStageCanvas
		{
		public:
			StageCanvas(StagePanel* editPanel);

		protected:
			virtual void onDraw();

		}; // StageCanvas 
	}
}

#endif // _DEDITOR_BOUNDARY_EXTRACTION_STAGE_CANVAS_H_