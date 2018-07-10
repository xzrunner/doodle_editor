#ifndef _DEDITOR_POLYGON_EDIT_STAGE_CANVAS_H_
#define _DEDITOR_POLYGON_EDIT_STAGE_CANVAS_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace polygon_edit
	{
		class StagePanel;

		class StageCanvas : public wxgui::ShapeStageCanvas
		{
		public:
			StageCanvas(StagePanel* parent);

			void clear();

		protected:
			virtual void onDraw();

		private:
			void drawGuideLines() const;

		private:
			std::vector<wxgui::ISprite*> m_tiles;

			mutable wxgui::SpriteBatch m_batch;

			friend class FileIOCMPT;

		}; // StageCanvas
	}
}

#endif // _DEDITOR_POLYGON_EDIT_STAGE_CANVAS_H_