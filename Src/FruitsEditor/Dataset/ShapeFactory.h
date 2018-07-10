#ifndef _FEDITOR_SHAPE_FACTORY_H_
#define _FEDITOR_SHAPE_FACTORY_H_
#include <Fruits2D/Fruits2D.h>

namespace FEDITOR
{
	class Shape;

	class ShapeFactory
	{
	public:
		static Shape* createShape(std::ifstream& fin);

	}; // ShapeFactory
}

#endif // _FEDITOR_SHAPE_FACTORY_H_