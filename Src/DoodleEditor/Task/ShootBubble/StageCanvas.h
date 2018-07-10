#ifndef _DEDITOR_SHOOT_BUBBLE_STAGE_CANVAS_H_
#define _DEDITOR_SHOOT_BUBBLE_STAGE_CANVAS_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace shoot_bubble
	{
		class StagePanel;

		class StageCanvas : public wxgui::SpriteStageCanvas
		{
		public:
			StageCanvas(StagePanel* parent);

		protected:
			virtual void onDraw();

		private:
			void drawGuideLines();

		private:
			StagePanel* m_stagePanel;

		}; // StageCanvas
	}
}

#endif // _DEDITOR_SHOOT_BUBBLE_STAGE_CANVAS_H_