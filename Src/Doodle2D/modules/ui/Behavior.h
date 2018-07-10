#ifndef _D2D_BEHAVIOR_H_
#define _D2D_BEHAVIOR_H_

namespace d2d
{
	class Behavior
	{
	public:
		virtual ~Behavior() {}

		virtual void trigger() = 0;

	}; // Behavior
}

#endif // _D2D_BEHAVIOR_H_