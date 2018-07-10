#ifndef _DEDITOR_MOTOX_STAGE_CANVAS_H_
#define _DEDITOR_MOTOX_STAGE_CANVAS_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class StagePanel;

		class StageCanvas : public wxgui::GLCanvas
		{
		public:
			StageCanvas(StagePanel* editPanel);
			virtual ~StageCanvas();

			virtual void clear();

		protected:
			virtual void onDraw();

		private:
			void drawGuideLines();
			void drawPolygonFillings();

			void drawSprites(const std::vector<wxgui::ISprite*>& sprites);
			void drawObstacleSprite(wxgui::ISprite* sprite);

		private:
			static const int GUIDE_LINES_WIDTH_TIMES = 20;

		private:
			StagePanel* m_editPanel;

			wxgui::SpriteBatch m_batch;

			std::vector<wxgui::PolygonShape*> m_polys;

			friend class TileIOCMPT;

		}; // StageCanvas  
	}
}

#endif // _DEDITOR_MOTOX_STAGE_CANVAS_H_