#ifndef _D2D_QUAD_H_
#define _D2D_QUAD_H_

#include "common/types.h"

namespace d2d
{
	class Quad
	{
	public:
//		Quad();
		// Coordinate origin is left-top of the image
		// -------->
		// |
		// |
		// |
		// V
		Quad(int left, int top, int width, int height, 
			int totWidth, int totHeight, float scale);
		Quad(int width, int height, float scale);

		const Vertex* getVertices() const;

		void flipHorizontal();
		void flipVertical();

		// debug
		void clearTexCoords()
		{
			for (size_t i = 0; i < NUM_VERTICES; ++i)
			{
				m_vertices[i].u = 0.0f;
				m_vertices[i].v = 0.0f;
			}
		}

	private:
		static const unsigned int NUM_VERTICES = 4;

	private:
		// 1 2
		// 0 3
		Vertex m_vertices[NUM_VERTICES];

	}; // Quad
}

#endif // _D2D_QUAD_H_