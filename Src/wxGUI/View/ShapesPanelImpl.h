#ifndef _WX_GUI_SHAPES_PANEL_IMPL_H_
#define _WX_GUI_SHAPES_PANEL_IMPL_H_

#include "MultiShapesImpl.h"

namespace wxgui
{
	class IShape;

	class ShapesPanelImpl : public MultiShapesImpl
	{
	public:
		ShapesPanelImpl(wxWindow* wnd);
		virtual ~ShapesPanelImpl();

		virtual void traverseShapes(IVisitor& visitor, 
			TraverseType type = e_allExisting) const;
		virtual void removeShape(IShape* shape);
		virtual void insertShape(IShape* shape);
		virtual void clear();

	private:
		std::vector<IShape*> m_shapes;

	}; // ShapesPanelImpl
}

#endif // _WX_GUI_SHAPES_PANEL_IMPL_H_