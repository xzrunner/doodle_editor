#ifndef _DEDITOR_SHOOT_BUBBLE_STAGE_PANEL_H_
#define _DEDITOR_SHOOT_BUBBLE_STAGE_PANEL_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace shoot_bubble
	{
		class StagePanel : public wxgui::EditPanel, public wxgui::SpritesPanelImpl
		{
		public:
			StagePanel(wxWindow* parent, wxgui::LibraryPanel* libraryPanel);

			//
			// wxgui::SpritesPanelImpl interface
			//
			virtual void insertSprite(wxgui::ISprite* sprite);
			virtual void clear();

			void transCoordsToGridPos(const f2Vec2& pos, int& row, int& col) const;
			void transGridPosToCoords(int row, int col, f2Vec2& pos) const;

			void computeParams(float& hEdge, float& posOffset, float& posOffset1, 
				float& rowOffset) const;

			void updateAllSpritesLocation();

		private:
			f2Vec2 fixSpriteLocation(const f2Vec2& pos) const;

		}; // StagePanel
	}
}

#endif // _DEDITOR_SHOOT_BUBBLE_STAGE_PANEL_H_