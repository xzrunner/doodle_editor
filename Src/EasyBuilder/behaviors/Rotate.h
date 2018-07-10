#ifndef _EASY_BUILDER_ROTATE_H_
#define _EASY_BUILDER_ROTATE_H_

#include "Behavior.h"

namespace ebuilder
{
	class Rotate : public Behavior
	{
	private:
		Rotate(Actor* actor);

	public:
		float start, end;

		float speed;

		friend class BehaviorFactory;

	}; // Rotate
}

#endif // _EASY_BUILDER_ROTATE_H_