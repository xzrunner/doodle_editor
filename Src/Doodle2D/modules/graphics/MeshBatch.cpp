#include "MeshBatch.h"
#include "VertexBuffer.h"
#include "Texture.h"
#include "Quad.h"
#include "Mesh.h"
#include "GraphicsSprite.h"

#include <stdlib.h>
#include <GLES/gl.h>

using namespace d2d;

MeshBatch::MeshBatch(Texture* texture, int size, int usage)
	: m_texture(texture)
	, m_size(size)
	, m_next(0)
	, m_vertices(NULL)
{
	createBuffer(size, usage);
}

MeshBatch::~MeshBatch()
{
	delete m_vertices;
}

int MeshBatch::add(const GraphicsSprite& sprite, int index/* = -1*/)
{
	return add(sprite.getQuad(), sprite.getLocation().x, sprite.getLocation().y, 
		sprite.getAngle(), sprite.getScale(), index);
}

int MeshBatch::add(const Mesh& mesh, float x, float y, float angle, 
				   float scale, int index/* = -1*/)
{
	if (mesh.m_vertices.empty()) 
		return -1;
	if ((index == -1 && m_next >= m_size) || index < -1 || index >= m_next)
		return -1;

#ifdef D2D_FAST_MATH
	const float sine = static_cast<float>(d2d::taylorSin(angle)),
		cosine = static_cast<float>(d2d::taylorCos(angle));
#else
	const float sine = sin(angle),
		cosine = cos(angle);
#endif
	std::vector<Vertex> trans(mesh.m_vertices);
	for (size_t i = 0, n = mesh.m_vertices.size(); i < n; ++i)
	{
		const float xScaled = mesh.m_vertices[i].x * scale,
			yScaled = mesh.m_vertices[i].y * scale;
		trans[i].x = cosine * xScaled - sine * yScaled + x;
		trans[i].y = sine * xScaled + cosine * yScaled + y;
	}

// 	int ret = (index == -1 ? m_next : index);
// 	if (index == -1)
// 	{
// 		for (size_t i = 0, n = trans.size(); i < n; ++i)
// 			add(trans[i], m_next++);
// 	}
// 	else
// 	{
// 		for (size_t i = 0, n = trans.size(); i < n; ++i)
// 			add(trans[i], index++);
// 	}
// 	return ret;
	int ret = (index == -1 ? m_next : index);
	if (index == -1)
	{
		add(trans, m_next);
		m_next += trans.size();
	}
	else
	{
		add(trans, index);
	}
	return ret;
}

void* MeshBatch::lock()
{
	m_vertices->bind();
	void* ret = m_vertices->map();
	m_vertices->unbind();

	return ret;
}

void MeshBatch::unlock()
{
	m_vertices->bind();
	m_vertices->unmap();
	m_vertices->unbind();
}

void MeshBatch::onDraw() const
{
	glColor4f(1, 1, 1, 1);

	const int color_offset = 0;
	const int vertex_offset = sizeof(unsigned char) * 4;
	const int texel_offset = sizeof(unsigned char) * 4 + sizeof(float) * 2;

	glPushMatrix();

	m_texture->bind();
	m_vertices->bind();

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, sizeof(Vertex), m_vertices->getPointer(vertex_offset));

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), m_vertices->getPointer(texel_offset));

	glDrawArrays(GL_TRIANGLES, 0, m_next);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	m_vertices->unbind();
	m_texture->unbind();

	glPopMatrix();
}

void MeshBatch::createBuffer(int size, int usage)
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

	int vertex_size = sizeof(Vertex) * size;
	m_vertices = VertexBuffer::create(vertex_size, GL_ARRAY_BUFFER, gl_usage);
}

void MeshBatch::add(const Vertex& v, int index)
{
	int size = sizeof(Vertex);

	m_vertices->bind();
	m_vertices->fill(index * size, size, &v);
	m_vertices->unbind();
}

void MeshBatch::add(const std::vector<Vertex>& vertices, int index)
{
	m_vertices->bind();
	m_vertices->fill(index * sizeof(Vertex), sizeof(Vertex) * vertices.size(), &vertices[0]);
	m_vertices->unbind();
}

int MeshBatch::add(const Quad& quad, float x, float y, float angle,
				   float scale, int index/* = -1*/)
{
	if ((index == -1 && m_next >= m_size) || index < -1 || index >= m_next)
		return -1;

#ifdef D2D_FAST_MATH
	const float sine = static_cast<float>(d2d::taylorSin(angle)),
		cosine = static_cast<float>(d2d::taylorCos(angle));
#else
	const float sine = sin(angle),
		cosine = cos(angle);
#endif
	Vertex vertices[4];
	for (size_t i = 0; i < 4; ++i)
	{
		vertices[i] = quad.getVertices()[i];

		const float sx = quad.getVertices()[i].x /** scale*/,
			sy = quad.getVertices()[i].y /** scale*/;

		vertices[i].x = cosine * sx - sine * sy + x;
		vertices[i].y = sine * sx + cosine * sy + y;
	}

	int ret = (index == -1 ? m_next : index);
	if (index == -1)
	{
		add(vertices[0], m_next++);
		add(vertices[1], m_next++);
		add(vertices[2], m_next++);

		add(vertices[0], m_next++);
		add(vertices[2], m_next++);
		add(vertices[3], m_next++);
	}
	else
	{
		add(vertices[0], index++);
		add(vertices[1], index++);
		add(vertices[2], index++);

		add(vertices[0], index++);
		add(vertices[2], index++);
		add(vertices[3], index++);
	}
	return ret;
}

