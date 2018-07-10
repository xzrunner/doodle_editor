#ifndef _EASY_BUILDER_BEHAVIOR_FACTORY_H_
#define _EASY_BUILDER_BEHAVIOR_FACTORY_H_

#include "BehaviorDefs.h"

namespace ebuilder
{
	class Behavior;
	class BehaviorPanel;
	class Actor;

	class BehaviorFactory
	{
	public:
		static Behavior* createBehavior(BehaviorType type, Actor* actor);

		static BehaviorPanel* createBehaviorPanel(wxWindow* parent, 
			Behavior* behavior);

	}; // BehaviorFactory
}

#endif // _EASY_BUILDER_BEHAVIOR_FACTORY_H_