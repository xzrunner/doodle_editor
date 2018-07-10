#ifndef _WX_GUI_DRAW_PENCIL_LINE_OP_H_
#define _WX_GUI_DRAW_PENCIL_LINE_OP_H_

#include "DrawCurveOP.h"

namespace wxgui
{
	class MultiShapesImpl;
	class DrawPencilLineCMPT;

	class DrawPencilLineOP : public DrawCurveOP
	{
	public:
		DrawPencilLineOP(EditPanel* editPanel, MultiShapesImpl* shapesImpl,
			DrawPencilLineCMPT* cmpt);

		virtual bool onMouseLeftUp(int x, int y);

	private:
		MultiShapesImpl* m_shapesImpl;

		DrawPencilLineCMPT* m_cmpt;

	}; // DrawPencilLineOP
}

#endif // _WX_GUI_DRAW_PENCIL_LINE_OP_H_