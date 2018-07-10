#ifndef _DEDITOR_AUTOMATIC_MERGE_STAGE_CANVAS_H_
#define _DEDITOR_AUTOMATIC_MERGE_STAGE_CANVAS_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace automatic_merge
	{
		class StagePanel;

		class StageCanvas : public wxgui::SpriteStageCanvas
		{
		public:
			StageCanvas(StagePanel* parent);

			void setOutputImageSize(int width, int height);

		protected:
			virtual void onDraw();

		private:
			void drawGuideLines();

			void drawCross();
			void drawRect();

		private:
			int m_width, m_height;

		}; // StageCanvas
	}
}

#endif // _DEDITOR_AUTOMATIC_MERGE_STAGE_CANVAS_H_