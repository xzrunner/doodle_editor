#ifndef _WX_GUI_INTERFACE_H_
#define _WX_GUI_INTERFACE_H_

#include <Fruits2D/Fruits2D.h>

namespace wxgui
{
	class ICameraObserver
	{
	public:
		virtual ~ICameraObserver() {}

		virtual void onCameraChanged() = 0;

	}; // ICameraObserver
}

#endif // _WX_GUI_INTERFACE_H_