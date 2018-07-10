#ifndef _DEDITOR_MOTOX_OBSTACLE_SOFT_OP_H_
#define _DEDITOR_MOTOX_OBSTACLE_SOFT_OP_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class StagePanel;
		class ObstacleSoftCMPT;

		class ObstacleSoftOP : public wxgui::ZoomViewOP
		{
		public:
			ObstacleSoftOP(StagePanel* stagePanel, 
				wxgui::LibraryPanel* libraryPanel,
				ObstacleSoftCMPT* cmpt);

			virtual bool onMouseLeftDown(int x, int y);
			virtual bool onMouseMove(int x, int y);

			virtual bool onDraw() const;
			virtual bool clear();

		private:
			StagePanel* m_stagePanel;

			wxgui::LibraryPanel* m_libraryPanel;

			ObstacleSoftCMPT* m_cmpt;

			f2Vec2 m_pos;

		}; // ObstacleSoftOP
	}
}

#endif // _DEDITOR_MOTOX_OBSTACLE_SOFT_OP_H_