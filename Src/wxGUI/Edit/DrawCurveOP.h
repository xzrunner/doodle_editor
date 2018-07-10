#ifndef _WX_GUI_DRAW_CURVE_OP_H_
#define _WX_GUI_DRAW_CURVE_OP_H_

#include "ZoomViewOP.h"

namespace wxgui
{
	class DrawCurveOP : public ZoomViewOP
	{
	public:
		DrawCurveOP(EditPanel* editPanel);

		virtual bool onMouseLeftDown(int x, int y);
		virtual bool onMouseLeftUp(int x, int y);
		virtual bool onMouseDrag(int x, int y);

		virtual bool onDraw() const;
		virtual bool clear();

	protected:
		std::vector<f2Vec2> m_curve;

	private:
		f2Vec2 m_firstPos;
		bool m_startDraw;

	}; // DrawCurveOP
}

#endif // _WX_GUI_DRAW_CURVE_OP_H_