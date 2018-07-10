#ifndef _EASY_BUILDER_PREVIEW_ROTATE_H_
#define _EASY_BUILDER_PREVIEW_ROTATE_H_

#include "Behavior.h"
#include "AnimationControl.h"

#include <wxGUI/wxGUI.h>

namespace ebuilder
{
	namespace preview
	{
		class Rotate : public Behavior, public ITimeObserver
		{
		public:
			Rotate(wxgui::ISprite* sprite, float start, 
				float end, float speed);

			virtual void trigger();

			virtual void onTick();

		private:
			wxgui::ISprite* m_sprite;

			float m_start, m_end;

			float m_speed;

			wxMilliClock_t m_startTime;

		}; // Rotate
	}
}

#endif // _EASY_BUILDER_PREVIEW_ROTATE_H_