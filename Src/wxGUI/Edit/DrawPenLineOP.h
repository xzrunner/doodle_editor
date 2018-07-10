#ifndef _WX_GUI_DRAW_PEN_LINE_OP_H_
#define _WX_GUI_DRAW_PEN_LINE_OP_H_

#include "DrawPolylineOP.h"

namespace wxgui
{
	class MultiShapesImpl;

	class DrawPenLineOP : public DrawPolylineOP
	{
	public:
		DrawPenLineOP(EditPanel* editPanel, MultiShapesImpl* shapesImpl);

		virtual bool onMouseLeftDClick(int x, int y);

	private:
		MultiShapesImpl* m_shapesImpl;

	}; // DrawPenLineOP
}

#endif // _WX_GUI_DRAW_PEN_LINE_OP_H_