#include "SpriteBatch.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "Quad.h"
#include "Color.h"
#include "GraphicsSprite.h"

#include "common/types.h"
#include "common/math.h"

#include <stdlib.h>
#include <GLES/gl.h>

using namespace d2d;

SpriteBatch::SpriteBatch(Texture* texture, int size, int usage)
	: m_texture(texture)
	, m_size(size)
	, m_next(0)
	, m_color(NULL)
	, m_vertices(NULL)
	, m_indices(NULL)
{
	createBuffer(size, usage);
	fillIndicesBuffer(size);
}

SpriteBatch::~SpriteBatch()
{
	delete m_color;
	delete m_vertices;
	delete m_indices;
}

//int SpriteBatch::add(const Quad& quad, int index/* = -1*/)
//{
//	if ((index == -1 && m_next >= m_size) || index < -1 || index >= m_next)
//		return -1;
//
//	memcpy(m_sprite, quad.getVertices(), sizeof(Vertex) * 4);
//
//	if (m_color)
//		setColor(m_sprite, *m_color);
//
//	add(m_sprite, (index == -1 ? m_next : index));
//
//	if (index == -1)
//		return m_next++;
//	return index;
//}

int SpriteBatch::add(const GraphicsSprite& sprite, int index/* = -1*/)
{
	return add(sprite.getQuad(), sprite.getLocation().x, sprite.getLocation().y, 
		sprite.getAngle(), sprite.getScale(), index);
}

int SpriteBatch::add(const Quad& quad, float x, float y, 
					 float angle, float scale, int index/* = -1*/)
{
	if ((index == -1 && m_next >= m_size) || index < -1 || index >= m_next)
		return -1;

 	memcpy(m_sprite, quad.getVertices(), sizeof(Vertex) * 4);

#ifdef D2D_FAST_MATH
	const float sine = static_cast<float>(d2d::taylorSin(angle)),
		cosine = static_cast<float>(d2d::taylorCos(angle));
#else
	const float sine = sin(angle),
		cosine = cos(angle);
#endif
	float x1 = quad.getVertices()[0].x * scale;
	float y1 = quad.getVertices()[0].y * scale;
	float x2 = quad.getVertices()[1].x * scale;
	float y2 = quad.getVertices()[1].y * scale;
	float x3 = quad.getVertices()[2].x * scale;
	float y3 = quad.getVertices()[2].y * scale;

	m_sprite[0].x = cosine * x1 - sine * y1 + x;
	m_sprite[0].y = sine * x1 + cosine * y1 + y;

	m_sprite[1].x = cosine * x2 - sine * y2 + x;
	m_sprite[1].y = sine * x2 + cosine * y2 + y;

	m_sprite[2].x = cosine * x3 - sine * y3 + x;
	m_sprite[2].y = sine * x3 + cosine * y3 + y;

	m_sprite[3].x = m_sprite[0].x + (m_sprite[2].x - m_sprite[1].x);
	m_sprite[3].y = m_sprite[2].y - (m_sprite[1].y - m_sprite[0].y);

	if (m_color)
		setColor(m_sprite, *m_color);

	add(m_sprite, (index == -1 ? m_next : index));

	if (index == -1)
		return m_next++;
	return index;
}

//int SpriteBatch::add(const Quad& quad, float x, float y, float a, float sx, float sy, float ox, float oy, float kx, float ky, int index/* = -1*/)
//{
//	if ((index == -1 && m_next >= m_size) || index < -1 || index >= m_next)
//		return -1;
//
//	memcpy(m_sprite, quad.getVertices(), sizeof(Vertex) * 4);
//
//// 	Matrix t;
//// 	t.setTransformation(x, y, a, sx, sy, ox, oy, kx, ky);
//// 	t.transform(m_sprite, m_sprite, 4);
//
//	if (m_color)
//		setColor(m_sprite, *m_color);
//
//	add(m_sprite, (index == -1 ? m_next : index));
//
//	if (index == -1)
//		return m_next++;
//	return index;
//}

void* SpriteBatch::lock()
{
	m_vertices->bind();
	void* ret = m_vertices->map();
	m_vertices->unbind();

	return ret;
}

void SpriteBatch::unlock()
{
	m_vertices->bind();
	m_vertices->unmap();
	m_vertices->unbind();
}

void SpriteBatch::setColor(const Color& color)
{
	if (!m_color)
		m_color = new Color(color);
	else
		*m_color = color;
}

void SpriteBatch::setColor()
{
	delete m_color, m_color = NULL;
}

void SpriteBatch::onDraw() const
{
	glColor4f(1, 1, 1, 1);

	const int color_offset = 0;
	const int vertex_offset = sizeof(unsigned char) * 4;
	const int texel_offset = sizeof(unsigned char) * 4 + sizeof(float) * 2;

	glPushMatrix();

	m_texture->bind();
	
	m_vertices->bind();
	m_indices->bind();

	if (m_color)
	{
		glEnableClientState(GL_COLOR_ARRAY);
		glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(Vertex), m_vertices->getPointer(color_offset));
	}
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, sizeof(Vertex), m_vertices->getPointer(vertex_offset));

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), m_vertices->getPointer(texel_offset));

	glDrawElements(GL_TRIANGLES, m_next * 6, GL_UNSIGNED_SHORT, m_indices->getPointer(0));

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	m_indices->unbind();
	m_vertices->unbind();

	m_texture->unbind();

	glPopMatrix();
}

void SpriteBatch::createBuffer(int size, int usage)
{
	GLenum gl_usage;
	switch (usage)
	{
	default:
	case USAGE_DYNAMIC:
		gl_usage = GL_DYNAMIC_DRAW;
		break;
	case USAGE_STATIC:
		gl_usage = GL_STATIC_DRAW;
		break;
// 	case USAGE_STREAM:
// 		gl_usage = GL_STREAM_DRAW;
// 		break;
	}

	int vertex_size = sizeof(Vertex) * 4 * size;
	int index_size = sizeof(GLushort) * 6 * size;

	m_vertices = VertexBuffer::create(vertex_size, GL_ARRAY_BUFFER, gl_usage);
	m_indices = VertexBuffer::create(index_size, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
}

void SpriteBatch::fillIndicesBuffer(int size)
{
	m_indices->bind();
	GLushort* indices = static_cast<GLushort*>(m_indices->map());

	if (indices)
	{
		for (int i = 0; i < size; ++i)
		{
			indices[i*6+0] = 0+(i*4);
			indices[i*6+1] = 1+(i*4);
			indices[i*6+2] = 2+(i*4);

			indices[i*6+3] = 0+(i*4);
			indices[i*6+4] = 2+(i*4);
			indices[i*6+5] = 3+(i*4);
		}
	}

	m_indices->unmap();
	m_indices->unbind();
}

void SpriteBatch::add(const Vertex* v, int index)
{
	int sprite_size = sizeof(Vertex) * 4;

	m_vertices->bind();
	m_vertices->fill(index * sprite_size, sprite_size, v);
	m_vertices->unbind();
}

void SpriteBatch::setColor(Vertex* v, const Color& color)
{
	v[0].r = color.r; v[0].g = color.g; v[0].b = color.b; v[0].a = color.a;
	v[1].r = color.r; v[1].g = color.g; v[1].b = color.b; v[1].a = color.a;
	v[2].r = color.r; v[2].g = color.g; v[2].b = color.b; v[2].a = color.a;
	v[3].r = color.r; v[3].g = color.g; v[3].b = color.b; v[3].a = color.a;
}