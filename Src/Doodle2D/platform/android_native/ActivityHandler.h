#include "common/config.h"

#ifdef D2D_ANDROID_NATIVE

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

		virtual void onStart() {}
		virtual void onResume() {}
		virtual void onPause() {}
		virtual void onStop() {}
		virtual void onDestroy() {}

		virtual void onSaveState(void** pData, size_t* pSize) {}
		virtual void onConfigurationChanged() {}
		virtual void onLowMemory() {}

		virtual void onCreateWindow() {}
		virtual void onDestroyWindow() {}
		virtual void onGainFocus() {}
		virtual void onLostFocus() {}

	}; // ActivityHandler
}

#endif // _D2D_ACTIVITY_HANDLER_H_

#endif // D2D_ANDROID_NATIVE