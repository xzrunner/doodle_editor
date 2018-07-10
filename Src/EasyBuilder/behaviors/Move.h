#ifndef _EASY_BUILDER_MOVE_H_
#define _EASY_BUILDER_MOVE_H_

#include "Behavior.h"

namespace ebuilder
{
	class Move : public Behavior
	{
	private:
		Move(Actor* actor);

	public:
		f2Vec2 start, end;

		float speed;

		friend class BehaviorFactory;

	}; // Move
}

#endif // _EASY_BUILDER_MOVE_H_