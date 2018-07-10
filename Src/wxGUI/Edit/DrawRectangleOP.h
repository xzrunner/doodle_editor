#ifndef _WX_GUI_DRAW_RECTANGLE_OP_H_
#define _WX_GUI_DRAW_RECTANGLE_OP_H_

#include "ZoomViewOP.h"

namespace wxgui
{
	class DrawRectangleOP : public ZoomViewOP
	{
	public:
		DrawRectangleOP(EditPanel* editPanel, 
			const f2Colorf& color = f2Colorf(0, 0, 0));
		
		virtual bool onMouseLeftDown(int x, int y);
		virtual bool onMouseLeftUp(int x, int y);
		virtual bool onMouseDrag(int x, int y);

		virtual bool onDraw() const;
		virtual bool clear();

	private:
		f2Colorf m_color;

		f2Vec2 m_firstPos, m_currPos;

	}; // DrawRectangleOP
}

#endif // _WX_GUI_DRAW_RECTANGLE_OP_H_