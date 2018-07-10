#ifndef _DEDITOR_MONSTER_STAGE_PANEL_H_
#define _DEDITOR_MONSTER_STAGE_PANEL_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace monster
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

		private:
			class RemoveOverlappedUnderground : public IVisitor
			{
			public:
				RemoveOverlappedUnderground(wxgui::MultiSpritesImpl* spritesImpl, wxgui::ISprite* sprite);

				virtual void visit(IObject* object, bool& bFetchNext);

			private:
				wxgui::MultiSpritesImpl* m_spritesImpl;
				wxgui::ISprite* m_sprite;

			}; // RemoveOverlappedUnderground

		}; // StagePanel
	}
}

#endif // _DEDITOR_MONSTER_STAGE_PANEL_H_