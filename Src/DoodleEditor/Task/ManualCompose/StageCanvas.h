#ifndef _DEDITOR_MANUAL_COMPOSE_STAGE_CANVAS_H_
#define _DEDITOR_MANUAL_COMPOSE_STAGE_CANVAS_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace manual_compose
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
			void drawBackground();

			void drawCross();
			void drawRect();

		}; // StageCanvas
	}
}

#endif // _DEDITOR_MANUAL_COMPOSE_STAGE_CANVAS_H_