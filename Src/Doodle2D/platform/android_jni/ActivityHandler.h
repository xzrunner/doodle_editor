#include "common/config.h"

#ifdef D2D_ANDROID_JNI

#ifndef _D2D_ACTIVITY_HANDLER_H_
#define _D2D_ACTIVITY_HANDLER_H_

#include "common/Types.h"

namespace d2d
{
	class ActivityHandler
	{
	public:
		virtual status onActivate() = 0;
		virtual void onDeactivate() = 0;
		virtual status onStep() = 0;

	}; // ActivityHandler
}

#endif // _D2D_ACTIVITY_HANDLER_H_

#endif // D2D_ANDROID_JNI