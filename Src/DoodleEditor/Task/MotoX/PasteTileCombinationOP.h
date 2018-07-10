#ifndef _DEDITOR_MOTOX_PASTE_TILE_COMBINATION_OP_H_
#define _DEDITOR_MOTOX_PASTE_TILE_COMBINATION_OP_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace motox
	{
		class StagePanel;
		class LibraryCombinationList;
		class LibraryCombinationItem;
		class PasteTileCombinationCMPT;

		class PasteTileCombinationOP : public wxgui::ZoomViewOP
		{
		public:
			PasteTileCombinationOP(StagePanel* stagePanel, 
				wxgui::LibraryPanel* libraryPanel,
				PasteTileCombinationCMPT* cmpt);

			virtual bool onMouseLeftDown(int x, int y);
			virtual bool onMouseRightDown(int x, int y);
			virtual bool onMouseMove(int x, int y);

			virtual bool onDraw() const;
			virtual bool clear();

		private:
			LibraryCombinationItem* randomDrawing() const;

		private:
			StagePanel* m_stagePanel;

			wxgui::LibraryPanel* m_libraryPanel;

			PasteTileCombinationCMPT* m_cmpt;

			LibraryCombinationItem* m_lastSelected;

			f2Vec2 m_pos;

		}; // PasteTileCombinationOP
	}
}

#endif // _DEDITOR_MOTOX_PASTE_TILE_COMBINATION_OP_H_