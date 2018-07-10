#ifndef _EASY_BUILDER_PREVIEW_MOVE_H_
#define _EASY_BUILDER_PREVIEW_MOVE_H_

#include "Behavior.h"
#include "AnimationControl.h"

#include <wxGUI/wxGUI.h>

namespace ebuilder
{	
	namespace preview
	{
		class Move : public Behavior, public ITimeObserver
		{
		public:
			Move(wxgui::ISprite* sprite, const f2Vec2& start, 
				const f2Vec2& end, float speed);

			virtual void trigger();

			virtual void onTick();

		private:
			wxgui::ISprite* m_sprite;

			f2Vec2 m_start, m_end;

			float m_speed;

			wxMilliClock_t m_startTime;

		}; // Move
	}
}

#endif // _EASY_BUILDER_PREVIEW_MOVE_H_