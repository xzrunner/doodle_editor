#ifndef _EASY_BUILDER_SCALE_SIZE_H_
#define _EASY_BUILDER_SCALE_SIZE_H_

#include "Behavior.h"

namespace ebuilder
{
	class ScaleSize : public Behavior
	{
	private:
		ScaleSize(Actor* actor);
		
	public:
		float val;

		friend class BehaviorFactory;

	}; // ScaleSize
}

#endif // _EASY_BUILDER_SCALE_SIZE_H_