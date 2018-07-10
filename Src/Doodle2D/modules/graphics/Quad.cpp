#include "Quad.h"

#include "common/math.h"

#include <string.h>

using namespace d2d;

Quad::Quad(int left, int top, int width, int height, 
		   int totWidth, int totHeight, float scale)
{
	const float hw = width * 0.5f * scale,
		hh = height * 0.5f * scale;

	m_vertices[0].x = -hw;
	m_vertices[0].y = -hh;
	m_vertices[1].x = -hw;
	m_vertices[1].y = hh;
	m_vertices[2].x = hw;
	m_vertices[2].y = hh;
	m_vertices[3].x = hw;
	m_vertices[3].y = -hh;

	m_vertices[0].u = m_vertices[1].u = (float)left / totWidth;
	m_vertices[0].v = m_vertices[3].v = (float)(totHeight - top - height) / totHeight;
	m_vertices[1].v = m_vertices[2].v = (float)(totHeight - top) / totHeight;
	m_vertices[2].u = m_vertices[3].u = (float)(left + width) / totWidth;
}

Quad::Quad(int width, int height, float scale)
{
	const float hw = width * 0.5f * scale,
		hh = height * 0.5f * scale;

	m_vertices[0].x = -hw;
	m_vertices[0].y = -hh;
	m_vertices[1].x = -hw;
	m_vertices[1].y = hh;
	m_vertices[2].x = hw;
	m_vertices[2].y = hh;
	m_vertices[3].x = hw;
	m_vertices[3].y = -hh;

	int texture_width = getNextPOT(width);
	int texture_height = getNextPOT(height);
 	if (texture_width != width || texture_height != height) 
 	{
		const float w = (width - 0.5f) / texture_width,
			h = (height - 0.5f) / texture_height;

 		m_vertices[0].u = 0;
 		m_vertices[0].v = 0;
 		m_vertices[1].u = 0;
 		m_vertices[1].v = h;
 		m_vertices[2].u = w;
 		m_vertices[2].v = h;
 		m_vertices[3].u = w;
 		m_vertices[3].v = 0;
 	}
 	else
	{
		m_vertices[0].u = 0;
		m_vertices[0].v = 0;
		m_vertices[1].u = 0;
		m_vertices[1].v = 1;
		m_vertices[2].u = 1;
		m_vertices[2].v = 1;
		m_vertices[3].u = 1;
		m_vertices[3].v = 0;
	}
}

const Vertex* Quad::getVertices() const
{
	return m_vertices;
}

void Quad::flipHorizontal()
{
	float u = m_vertices[1].u;
	m_vertices[1].u = m_vertices[0].u = m_vertices[2].u;
	m_vertices[2].u = m_vertices[3].u = u;
}

void Quad::flipVertical()
{
	float v = m_vertices[1].v;
	m_vertices[1].v = m_vertices[2].v = m_vertices[0].v;
	m_vertices[0].v = m_vertices[3].v = v;
}