#include "GraphicsSprite.h"
#include "Texture.h"

#include "common/math.h"

#include <GLES/gl.h>

using namespace d2d;

GraphicsSprite::GraphicsSprite(Texture* pTexture)
	: m_angle(0.0f)
	, m_scale(1.0f)
	, m_xMirror(false)
	, m_yMirror(false)
	, m_texture(pTexture)
	, m_quad(pTexture->getWidth(), pTexture->getHeight(), 1.0f)
{
	if (pTexture->isFlipY())
		m_quad.flipVertical();
}

GraphicsSprite::GraphicsSprite(Texture* pTexture, int left, int top, int width, int height,
							   int totWidth, int totHeight, float scale /*= 1.0f*/)
	: m_angle(0.0f)
	, m_scale(scale)
	, m_xMirror(false)
	, m_yMirror(false)
	, m_texture(pTexture)
	, m_quad(left, top, width, height, totWidth, totHeight, scale)
{
	if (pTexture->isFlipY())
		m_quad.flipVertical();
}

void GraphicsSprite::onDraw() const
{
	m_texture->bind();

	glPushMatrix();
	glTranslatef(m_location.x, m_location.y, 0.0f);
	glRotatef(m_angle * radiansToDegrees, 0, 0, 1);
	glScalef(m_scale, m_scale, 1.0f);

 	const Vertex* buffer = m_quad.getVertices();
 	const byte* ptr = reinterpret_cast<byte*>(const_cast<Vertex*>(buffer));

	unsigned short indices[6] = {
		0, 1, 2, 0, 2, 3
	};

	const int color_offset = 0;
	const int vertex_offset = sizeof(unsigned char) * 4;
	const int texel_offset = sizeof(unsigned char) * 4 + sizeof(float) * 2;

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(2, GL_FLOAT, sizeof(Vertex), ptr + vertex_offset);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, sizeof(Vertex), ptr + texel_offset);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);

	glPopMatrix();
}

void GraphicsSprite::translate(const Vector& offset)
{
	m_location += offset;
}

void GraphicsSprite::rotate(float delta)
{
	m_angle += delta;
}

void GraphicsSprite::setTransform(const Vector& location, float angle)
{
	if (m_location != location) translate(location - m_location);
	if (m_angle != angle) rotate(angle - m_angle);
}

void GraphicsSprite::setScale(float scale)
{
	m_scale = scale;
}

void GraphicsSprite::setMirror(bool xMirror, bool yMirror)
{
	if (xMirror != m_xMirror)
		m_quad.flipHorizontal();
	if (yMirror != m_yMirror)
		m_quad.flipVertical();

	m_xMirror = xMirror;
	m_yMirror = yMirror;
}