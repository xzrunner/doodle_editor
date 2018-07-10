#ifndef _EASY_BUILDER_PREVIEW_SCALE_SIZE_H_
#define _EASY_BUILDER_PREVIEW_SCALE_SIZE_H_

#include "Behavior.h"

#include <wxGUI/wxGUI.h>

namespace ebuilder
{	
	namespace preview
	{
		class ScaleSize : public Behavior
		{
		public:
			ScaleSize(wxgui::ISprite* sprite, float scale);

			virtual void trigger();

		private:
			wxgui::ISprite* m_sprite;

			float m_scale;

		}; // ScaleSize
	}
}

#endif // _EASY_BUILDER_PREVIEW_SCALE_SIZE_H_