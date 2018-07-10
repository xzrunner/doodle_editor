#ifndef _EASY_BUILDER_MOUSE_BUTTON_H_
#define _EASY_BUILDER_MOUSE_BUTTON_H_

#include "Behavior.h"

namespace ebuilder
{
	class MouseButton : public Behavior
	{
	public:
		virtual ~MouseButton();

	private:
		MouseButton(Actor* actor);

	public:
		bool bPress;

		std::vector<Behavior*> satisfies;
		std::vector<Behavior*> notSatisfies;

		friend class BehaviorFactory;

	}; // MouseButton
}

#endif // _EASY_BUILDER_MOUSE_BUTTON_H_
