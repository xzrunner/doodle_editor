#include "DrawShapesVisitor.h"

#include "Dataset/IShape.h"

using namespace wxgui;

DrawShapesVisitor::DrawShapesVisitor(const f2Colorf& color/* = f2Colorf(0, 0, 0)*/)
	: m_color(color)
{
}

void DrawShapesVisitor::visit(IObject* object, bool& bFetchNext)
{
	IShape* shape = static_cast<IShape*>(object);
	shape->draw(m_color);
	bFetchNext = true;
}