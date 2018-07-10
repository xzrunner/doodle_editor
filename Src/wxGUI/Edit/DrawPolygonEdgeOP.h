#ifndef _WX_GUI_DRAW_POLYGON_EDGE_OP_H_
#define _WX_GUI_DRAW_POLYGON_EDGE_OP_H_

#include "DrawPolylineOP.h"

namespace wxgui
{
	class MultiShapesImpl;

	class DrawPolygonEdgeOP : public DrawPolylineOP
	{
	public:
		DrawPolygonEdgeOP(EditPanel* editPanel, MultiShapesImpl* shapesImpl);

		virtual bool onMouseLeftDClick(int x, int y);

	private:
		MultiShapesImpl* m_shapesImpl;

	}; // DrawPolygonEdgeOP
}

#endif // _WX_GUI_DRAW_POLYGON_EDGE_OP_H_