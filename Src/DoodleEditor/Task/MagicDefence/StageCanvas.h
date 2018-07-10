#ifndef _DEDITOR_MAGIC_DEFENCE_STAGE_CANVAS_H_
#define _DEDITOR_MAGIC_DEFENCE_STAGE_CANVAS_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace magic_defence
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

#endif // _DEDITOR_MAGIC_DEFENCE_STAGE_CANVAS_H_