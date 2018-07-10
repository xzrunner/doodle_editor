#ifndef _DEDITOR_SKATER_SPRITE_EDIT_CANVAS_H_
#define _DEDITOR_SKATER_SPRITE_EDIT_CANVAS_H_

#include <wxGUI/wxGUI.h>

namespace deditor
{
	namespace skater
	{
		class SpriteEditCanvas : public wxgui::GLCanvas
		{
		public:
			SpriteEditCanvas(wxgui::EditPanel* parent, 
				wxgui::ISprite* sprite);

		protected:
			virtual void initGL();
			virtual void onDraw();

		private:
			wxgui::ISprite* m_sprite;

		}; // SpriteEditCanvas
	}
}

#endif // _DEDITOR_SKATER_SPRITE_EDIT_CANVAS_H_