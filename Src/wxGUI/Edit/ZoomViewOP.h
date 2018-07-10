#ifndef _WX_GUI_ZOOM_VIEW_OP_H_
#define _WX_GUI_ZOOM_VIEW_OP_H_

#include "AbstractEditOP.h"

#include "View/EditPanel.h"

namespace wxgui
{
	class ZoomViewOP : public AbstractEditOP
	{
	public:
		ZoomViewOP(EditPanel* editPanel, bool bMouseMoveFocus);

		virtual bool onKeyDown(int keyCode);
		virtual bool onKeyUp(int keyCode);
		virtual bool onMouseLeftDown(int x, int y);
		virtual bool onMouseLeftUp(int x, int y);
		virtual bool onMouseMove(int x, int y);
		virtual bool onMouseDrag(int x, int y);
		virtual bool onMouseWheelRotation(int x, int y, int direction);

	private:
		bool m_bMouseMoveFocus;

		f2Vec2 m_lastPos;

	}; // ZoomViewOP
}

#endif // _WX_GUI_ZOOM_VIEW_OP_H_