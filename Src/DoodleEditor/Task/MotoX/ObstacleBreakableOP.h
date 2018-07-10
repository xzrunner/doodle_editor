#ifndef _DEDITOR_MOTOX_OBSTACLE_BREAKABLE_OP_H_
#define _DEDITOR_MOTOX_OBSTACLE_BREAKABLE_OP_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class StagePanel;

		class ObstacleBreakableOP : public wxgui::ZoomViewOP
		{
		public:
			ObstacleBreakableOP(StagePanel* stagePanel, 
				wxgui::LibraryPanel* libraryPanel);

			virtual bool onMouseLeftDown(int x, int y);
			virtual bool onMouseMove(int x, int y);

			virtual bool onDraw() const;
			virtual bool clear();

			void setStatic(bool bStatic) { m_bStatic = bStatic; }

		private:
			StagePanel* m_stagePanel;

			wxgui::LibraryPanel* m_libraryPanel;

			f2Vec2 m_pos;

			bool m_bStatic;

		}; // ObstacleBreakableOP
	}
}

#endif // _DEDITOR_MOTOX_OBSTACLE_BREAKABLE_OP_H_