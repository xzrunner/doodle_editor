#ifndef _WX_GUI_MOUSE_POSITION_OP_H_
#define _WX_GUI_MOUSE_POSITION_OP_H_

#include "ZoomViewOP.h"

namespace wxgui
{
	class MousePositionCMPT;

	class MousePositionOP : public ZoomViewOP
	{
	public:
		MousePositionOP(EditPanel* editPanel, MousePositionCMPT* cmpt);

		virtual bool onMouseMove(int x, int y);

	private:
		MousePositionCMPT* m_cmpt;

	}; // MousePositionOP
}

#endif // _WX_GUI_MOUSE_POSITION_OP_H_