#ifndef _WX_GUI_DRAW_SHAPES_VISITOR_H_
#define _WX_GUI_DRAW_SHAPES_VISITOR_H_

#include <Fruits2D/Fruits2D.h>

namespace wxgui
{
	class DrawShapesVisitor : public IVisitor
	{
	public:
		DrawShapesVisitor(const f2Colorf& color = f2Colorf(0, 0, 0));

		virtual void visit(IObject* object, bool& bFetchNext);

	private:
		f2Colorf m_color;

	}; // DrawShapesVisitor
}

#endif // _WX_GUI_DRAW_SHAPES_VISITOR_H_