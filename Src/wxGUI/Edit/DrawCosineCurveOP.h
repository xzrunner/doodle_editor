#ifndef _WX_GUI_DRAW_COSINE_CURVE_OP_H_
#define _WX_GUI_DRAW_COSINE_CURVE_OP_H_

#include "DrawPolylineOP.h"

namespace wxgui
{
	class MultiShapesImpl;

	class DrawCosineCurveOP : public DrawPolylineOP
	{
	public:
		DrawCosineCurveOP(EditPanel* editPanel, MultiShapesImpl* shapesImpl);

		virtual bool onMouseLeftDClick(int x, int y);

	private:
		MultiShapesImpl* m_shapesImpl;

	}; // DrawCosineCurveOP
}

#endif // _WX_GUI_DRAW_COSINE_CURVE_OP_H_