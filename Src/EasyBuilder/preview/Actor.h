#ifndef _EASY_BUILDER_PREVIEW_ACTOR_H_
#define _EASY_BUILDER_PREVIEW_ACTOR_H_

#include "Item.h"

namespace ebuilder
{	
	namespace preview
	{
		class Actor : public Item
		{
		public:
			Actor(const wxgui::ImageSprite& sprite);

		}; // Actor
	}
}

#endif // _EASY_BUILDER_PREVIEW_ACTOR_H_