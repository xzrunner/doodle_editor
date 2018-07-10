#ifndef _EASY_BUILDER_PREVIEW_BUTTON_H_
#define _EASY_BUILDER_PREVIEW_BUTTON_H_

#include "Item.h"

namespace ebuilder
{	
	namespace preview
	{
		class Behavior;

		class Button : public Item
		{
		public:
			Button(const wxgui::ImageSprite& sprite);

		public:
			std::vector<Behavior*> m_pressBehaviors;
			std::vector<Behavior*> m_liftBehaviors;

		}; // Button
	}
}

#endif // _EASY_BUILDER_PREVIEW_BUTTON_H_