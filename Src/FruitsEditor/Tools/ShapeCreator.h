#ifndef _FEDITOR_SHAPE_CREATOR_H_
#define _FEDITOR_SHAPE_CREATOR_H_
#include <Fruits2D/Fruits2D.h>

namespace FEDITOR
{
	class Shape;

	class ShapeCreator
	{
	public:
		// dir:
		// 0 toUp
		// 1 toDown
		// 2 toLeft
		// 3 toRight
		static Shape* arrow(const f2Vec2& pos, int dir, int length = 25, int width = 10);

	}; // ShapeCreator
}

#endif // _FEDITOR_SHAPE_CREATOR_H_