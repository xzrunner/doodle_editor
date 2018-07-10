#ifndef _WX_GUI_PRIMITIVE_DRAW_H_
#define _WX_GUI_PRIMITIVE_DRAW_H_

#include <Fruits2D/Fruits2D.h>

namespace wxgui
{
	class PrimitiveDraw
	{
	public:
		static void resetColorAndTexture();

		static void drawSquare(const f2Vec2& center, float radius, const f2Colorf& color);
		static void drawSquareFrame(const f2Vec2& center, float radius, const f2Colorf& color);
		static void drawRectangle(const f2Vec2& center, float width, float height, const f2Colorf& color);
		static void drawRing(const f2Vec2& center, float radius, const f2Colorf& color, int size = 3, int kSegments = 16);
		static void drawCircle(const f2Vec2& center, float radius, const f2Colorf& color);
		static void drawCircles(const std::vector<f2Vec2>& circles, float radius, const f2Colorf& color);
		static void drawPoints(const std::vector<f2Vec2>& vertices, const f2Colorf& color, int size = 3);
		static void drawLine(const f2Vec2& p0, const f2Vec2& p1, const f2Colorf& color, int size = 3);
		static void drawDotLine(const f2Vec2& p0, const f2Vec2& p1, const f2Colorf& color, int size = 3);
		static void drawDashLine(const f2Vec2& p0, const f2Vec2& p1, const f2Colorf& color, int size = 3);
		static void drawDotDashLine(const f2Vec2& p0, const f2Vec2& p1, const f2Colorf& color, int size = 3);
		static void drawLines(const std::vector<f2Vec2>& vertices, const f2Colorf& color, int size = 3);
		static void drawPolyline(const std::vector<f2Vec2>& vertices, const f2Colorf& color, bool isClose, int size = 3);
		static void drawPolygon(const std::vector<f2Vec2>& vertices, const f2Colorf& color);
		static void drawTriangles(const std::vector<f2Vec2>& triangles, const f2Colorf& color);
		// 		static void drawTriangles(const std::vector<f2Vec2>& triangles, const wxString& filepath);
		// 		static void drawTriangles(const std::vector<f2Vec2>& triangles, const wxString& filepath, 
		// 			const f2Vec2& leftLow, const std::vector<unsigned int>& mesh);
		static void drawTriangles(unsigned int texID, const std::vector<f2Vec2>& triangles, 
			const std::vector<f2Vec2>& texCoords);
		static void drawTrianglesSlow(unsigned int texID, const std::vector<f2Vec2>& triangles, 
			const std::vector<f2Vec2>& texCoords);

	}; // PrimitiveDraw
}

#endif // _WX_GUI_PRIMITIVE_DRAW_H_