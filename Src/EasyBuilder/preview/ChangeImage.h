#ifndef _EASY_BUILDER_PREVIEW_CHANGE_IMAGE_H_
#define _EASY_BUILDER_PREVIEW_CHANGE_IMAGE_H_

#include "Behavior.h"

#include <wxGUI/wxGUI.h>

namespace ebuilder
{	
	namespace preview
	{
		class ChangeImage : public Behavior
		{
		public:
			ChangeImage(wxgui::ISprite* sprite, wxgui::ISymbol* symbol);

			virtual void trigger();

		private:
			wxgui::ISprite* m_sprite;

			wxgui::ISymbol* m_symbol;

		}; // ChangeImage
	}
}

#endif // _EASY_BUILDER_PREVIEW_CHANGE_IMAGE_H_