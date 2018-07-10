#ifndef _WX_GUI_DRAW_SELECTED_SHAPE_VISITOR_H_
#define _WX_GUI_DRAW_SELECTED_SHAPE_VISITOR_H_

#include <Fruits2D/Fruits2D.h>

namespace wxgui
{
	class DrawSelectedShapeVisitor : public IVisitor
	{
	public:
		virtual void visit(IObject* object, bool& bFetchNext) 
		{
			IShape* shape = static_cast<IShape*>(object);
			shape->draw(f2Colorf(1, 0, 0));
			bFetchNext = true;
		}

	}; // DrawSelectedShapeVisitor
}

#endif // _WX_GUI_DRAW_SELECTED_SHAPE_VISITOR_H_