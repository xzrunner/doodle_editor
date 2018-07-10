#ifndef _D2D_DRAWING_PRIMITIVES_H_
#define _D2D_DRAWING_PRIMITIVES_H_

#include "Vector.h"

#include <vector>

namespace d2d
{
	class Color;

	class DrawingPrimitives
	{
	public:
		static void drawPolyline(const std::vector<Vector>& vertices, bool isClose);

		static void drawTriangles(const std::vector<Vector>& vertices, const Color& color);
		static void drawTriangles(const std::vector<Vector>& vertices, 
			const std::vector<unsigned short>& indices, const Color& color);
		static void drawTriangles(const std::vector<Vector>& vertices, const std::vector<Color>& colors,
			const std::vector<unsigned short>& indices);

	}; // Render
}

#endif // _D2D_DRAWING_PRIMITIVES_H_