#ifndef _DEDITOR_SKATER_SPRITE_EDIT_DIALOG_H_
#define _DEDITOR_SKATER_SPRITE_EDIT_DIALOG_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace skater
	{
		class SpriteEditDialog : public wxDialog
		{
		public:
			SpriteEditDialog(wxWindow* parent, 
				wxgui::ImageSprite* sprite);
			~SpriteEditDialog();

		private:
			wxgui::ISprite* m_sprite;
			wxgui::EditPanel* m_editPanel;

		}; // SpriteEditDialog
	}
}

#endif // _DEDITOR_SKATER_SPRITE_EDIT_DIALOG_H_