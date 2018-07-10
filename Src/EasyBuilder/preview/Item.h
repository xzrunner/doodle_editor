#ifndef _EASY_BUILDER_ITEM_H_
#define _EASY_BUILDER_ITEM_H_

#include <wxGUI/wxGUI.h>

namespace ebuilder
{
	namespace preview
	{
		class Item : public wxgui::ImageSprite
		{
		public:
			enum Type
			{
				e_actor = 0,
				e_button
			};

		public:
			Item(Type type, const wxgui::ImageSprite& sprite)
				: wxgui::ImageSprite(sprite), m_type(type) {}

			Type type() const {
				return m_type;
			}

		private:
			Type m_type;

		}; // Item
	}
}

#endif // _EASY_BUILDER_ITEM_H_