#ifndef _EASY_BUILDER_PREVIEW_SCENE_H_
#define _EASY_BUILDER_PREVIEW_SCENE_H_

#include <wxGUI/wxGUI.h>

namespace ebuilder
{	
	namespace preview
	{
		class Button;
		class Item;
		class Behavior;

		class Scene
		{
		public:
			~Scene();

			Button* queryButtonByPos(const f2Vec2& pos) const;

			void triggerAllBehaviors();

		public:
			f2Colorf m_color;

			std::vector<Item*> m_items;

			std::vector<Behavior*> m_behaviors;

		}; // Scene
	}
}

#endif // _EASY_BUILDER_PREVIEW_SCENE_H_