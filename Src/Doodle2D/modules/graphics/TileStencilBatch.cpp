#include "TileStencilBatch.h"
#include "VertexBuffer.h"
#include "Texture.h"

using namespace d2d;

TileStencilBatch::TileStencilBatch(Texture* texture, int stencilSize, int textureSize, int usage)
	: m_texture(texture)
	, m_texInfo(false)
{
	m_stencilVertices = m_stencilIndices = NULL;
	m_textureVertices = m_textureIndices = NULL;

	m_stencilVerticesCount = m_stencilIndicesCount = 0;
	m_textureVerticesCount = m_textureIndicesCount = 0;

	createBuffer(stencilSize, textureSize, usage);

	initTextureInfo();
}

TileStencilBatch::~TileStencilBatch()
{
	delete m_stencilVertices;
	delete m_stencilIndices;
	delete m_textureVertices;
	delete m_textureIndices;
}

void TileStencilBatch::add(const std::vector<Vector>& vertices, const std::vector<unsigned short>& indices,
						   int texID, const Vector& leftLow, const std::vector<unsigned int>& mesh)
{
	addStencil(vertices, indices);
	addTexture(texID, leftLow, mesh);
}

void TileStencilBatch::onDraw() const
{
	glPushMatrix();

  	glClearStencil(0);
  	glEnable(GL_STENCIL_TEST);
  
  	glClear(GL_STENCIL_BUFFER_BIT); 
  
  	glStencilFunc(GL_NEVER, 0x0, 0x0);
  	glStencilOp(GL_INCR, GL_INCR, GL_INCR);
  
  	drawStencil();
  
  	glStencilFunc(GL_NOTEQUAL, 0x0, 0x1);
  	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	drawTexture();

	glDisable(GL_STENCIL_TEST);

	glPopMatrix();
}

void TileStencilBatch::createBuffer(int stencilSize, int textureSize, int usage)
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

	m_stencilVertices = VertexBuffer::create(sizeof(Vector) * stencilSize, GL_ARRAY_BUFFER, gl_usage);
	m_stencilIndices = VertexBuffer::create(sizeof(GLushort) * 3 * stencilSize, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);

	m_textureVertices = VertexBuffer::create(sizeof(Vertex) * 4 * textureSize, GL_ARRAY_BUFFER, gl_usage);
	m_textureIndices = VertexBuffer::create(sizeof(GLushort) * 6 * textureSize, GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
}

void TileStencilBatch::initTextureInfo()
{
	m_texInfo.setSizer(256, 256);

	m_texInfo.addRegion(0, 128, 128, 128);
	m_texInfo.addRegion(128, 128, 128, 128);
	m_texInfo.addRegion(0, 0, 128, 128);
}

void TileStencilBatch::addStencil(const std::vector<Vector>& vertices, const std::vector<unsigned short>& indices)
{
	m_stencilVertices->bind();
	m_stencilVertices->fill(sizeof(Vector) * m_stencilVerticesCount, sizeof(Vector) * vertices.size(), &vertices[0]);
	m_stencilVertices->unbind();

	std::vector<unsigned short> indices_fix(indices);
	for (size_t i = 0, n = indices_fix.size(); i < n; ++i)
		indices_fix[i] += m_stencilVerticesCount;
	m_stencilIndices->bind();
	m_stencilIndices->fill(sizeof(unsigned short) * m_stencilIndicesCount, sizeof(unsigned short) * indices_fix.size(), &indices_fix[0]);
	m_stencilIndices->unbind();

	m_stencilVerticesCount += vertices.size();
	m_stencilIndicesCount += indices.size();
}

void TileStencilBatch::addTexture(int texID, const Vector& leftLow, const std::vector<unsigned int>& mesh)
{
	const TextureInfo::Region* pRegion = m_texInfo.getRegion(texID);

	std::vector<Vertex> vertices;
	std::vector<unsigned short> indices;
	vertices.reserve(mesh.size() * 4);
	indices.reserve(mesh.size() * 6);
	for (size_t i = 0, n = mesh.size(); i < n; ++i)
	{
		unsigned int pos = mesh[i];
		float left = leftLow.x + (pos & 0x0000ffff) * pRegion->width;
		float low = leftLow.y + (pos >> 16) * pRegion->height;

		Vertex leftLow, rightLow,
			leftUp, rightUp;

		leftLow.x = leftUp.x = left;
		rightLow.x = rightUp.x = left + pRegion->width;
		leftLow.y = rightLow.y = low;
		leftUp.y = rightUp.y = low + pRegion->height;

 		leftLow.u = leftUp.u = (float) pRegion->left / m_texInfo.getWidth();
 		rightLow.u = rightUp.u = (float) (pRegion->left + pRegion->width) / m_texInfo.getWidth();
 		leftLow.v = rightLow.v = (float) (m_texInfo.getHeight() - pRegion->top - pRegion->height) / m_texInfo.getHeight();
 		leftUp.v = rightUp.v = (float) (m_texInfo.getHeight() - pRegion->top) / m_texInfo.getHeight();

		const int base = m_textureVerticesCount + vertices.size();
		indices.push_back(base + 0);
		indices.push_back(base + 1);
		indices.push_back(base + 2);
		indices.push_back(base + 0);
		indices.push_back(base + 2);
		indices.push_back(base + 3);

		vertices.push_back(leftLow);
		vertices.push_back(rightLow);
		vertices.push_back(rightUp);
		vertices.push_back(leftUp);
	}

	m_textureVertices->bind();
	m_textureVertices->fill(sizeof(Vertex) * m_textureVerticesCount, sizeof(Vertex) * vertices.size(), &vertices[0]);
	m_textureVertices->unbind();

	m_textureIndices->bind();
	m_textureIndices->fill(sizeof(unsigned short) * m_textureIndicesCount, sizeof(unsigned short) * indices.size(), &indices[0]);
	m_textureIndices->unbind();

	m_textureVerticesCount += vertices.size();
	m_textureIndicesCount += indices.size();
}

void TileStencilBatch::drawStencil() const
{
	m_stencilVertices->bind();
	m_stencilIndices->bind();

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, 0, m_stencilVertices->getPointer(0));

	glDrawElements(GL_TRIANGLES, m_stencilIndicesCount, GL_UNSIGNED_SHORT, m_stencilIndices->getPointer(0));

	glDisableClientState(GL_VERTEX_ARRAY);

	m_stencilIndices->unbind();
	m_stencilVertices->unbind();
}

void TileStencilBatch::drawTexture() const
{
	const int color_offset = 0;
	const int vertex_offset = sizeof(unsigned char) * 4;
	const int texel_offset = sizeof(unsigned char) * 4 + sizeof(float) * 2;

	m_texture->bind();

	m_textureVertices->bind();
	m_textureIndices->bind();

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, sizeof(Vertex), m_textureVertices->getPointer(vertex_offset));

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), m_textureVertices->getPointer(texel_offset));

	glDrawElements(GL_TRIANGLES, m_textureIndicesCount, GL_UNSIGNED_SHORT, m_textureIndices->getPointer(0));

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	m_textureIndices->unbind();
	m_textureVertices->unbind();

	m_texture->unbind();
}