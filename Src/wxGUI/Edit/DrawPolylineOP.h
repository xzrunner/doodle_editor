#ifndef _WX_GUI_DRAW_POLYLINE_OP_H_
#define _WX_GUI_DRAW_POLYLINE_OP_H_

#include "ZoomViewOP.h"

namespace wxgui
{
	class EditPanel;

	class DrawPolylineOP : public ZoomViewOP
	{
	public:
		DrawPolylineOP(EditPanel* editPanel, bool isClosed);

		virtual bool onMouseLeftDown(int x, int y);
		virtual bool onMouseRightDown(int x, int y);
		virtual bool onMouseMove(int x, int y);
		virtual bool onMouseLeftDClick(int x, int y);

		virtual bool onDraw() const;
		virtual bool clear();

	protected:
		bool shouldFixMousePos() const;

	private:
		void fixPosTo45Degree(f2Vec2& pos) const;

	protected:
		std::vector<f2Vec2> m_polyline;
		f2Vec2 m_currPos;

	private:
		bool m_isClosed;

	}; // DrawPolylineOP
}

#endif // _WX_GUI_DRAW_POLYLINE_OP_H_