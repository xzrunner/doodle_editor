#ifndef _DEDITOR_MAGIC_DEFENCE_STAGE_PANEL_H_
#define _DEDITOR_MAGIC_DEFENCE_STAGE_PANEL_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace magic_defence
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

			void updateAllSpritesLocation();

		private:
			f2Vec2 fixSpriteLocation(const f2Vec2& pos) const;

		}; // StagePanel
	}
}

#endif // _DEDITOR_MAGIC_DEFENCE_STAGE_PANEL_H_