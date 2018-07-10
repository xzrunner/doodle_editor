#include "common/config.h"

#ifdef D2D_WINDOWS

#ifndef _D2D_ACTIVITY_HANDLER_H_
#define _D2D_ACTIVITY_HANDLER_H_

#include <string>

namespace d2d
{
	class ActivityHandler
	{
	public:
		virtual ~ActivityHandler() {}

		virtual std::string name() const = 0;

		virtual void onDraw() {}
		virtual void onResize(int width, int height) {}
		virtual void onKey(int action, int keyCode, int unicode) {}
		virtual void onMouse(int action, int x, int y, int buttons) {}
		virtual void onUpdate(float deltaTime) {}
		virtual void onQuit() {}

	}; // ActivityHandler
}

#endif // _D2D_ACTIVITY_HANDLER_H_
#endif // D2D_WINDOWS
