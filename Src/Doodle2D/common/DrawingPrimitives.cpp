#include "DrawingPrimitives.h"
#include "Log.h"

#include "modules/graphics/Color.h"

#include <GLES/gl.h>

using namespace d2d;

void DrawingPrimitives::drawPolyline(const std::vector<Vector>& vertices, bool isClose)
{
	glEnableClientState(GL_VERTEX_ARRAY);

	glVertexPointer(2, GL_FLOAT, 0, &vertices[0]);

	if (isClose)
		glDrawArrays(GL_LINE_LOOP, 0, vertices.size());
	else
		glDrawArrays(GL_LINE_STRIP, 0, vertices.size());

	glDisableClientState(GL_VERTEX_ARRAY);
}

void DrawingPrimitives::drawTriangles(const std::vector<Vector>& vertices, const Color& color)
{
 	glEnableClientState(GL_VERTEX_ARRAY);
 	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(2, GL_FLOAT, 0, &vertices[0]);
 	std::vector<Color> colors(vertices.size(), color);
 	glColorPointer(4, GL_UNSIGNED_BYTE, 0, &colors[0]);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());

 	glDisableClientState(GL_VERTEX_ARRAY);
 	glDisableClientState(GL_COLOR_ARRAY);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

void DrawingPrimitives::drawTriangles(const std::vector<Vector>& vertices, const std::vector<unsigned short>& indices, 
									  const Color& color)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(2, GL_FLOAT, 0, &vertices[0]);
	std::vector<Color> colors(indices.size(), color);
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, &colors[0]);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, &indices[0]);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

void DrawingPrimitives::drawTriangles(const std::vector<Vector>& vertices, const std::vector<Color>& colors, 
									  const std::vector<unsigned short>& indices)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(2, GL_FLOAT, 0, &vertices[0]);
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, &colors[0]);

	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_SHORT, &indices[0]);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}