#include "FrameAnimSprite.h"
#include "Texture.h"
#include "common/Log.h"

#include <GLES/gl.h>

using namespace d2d;

FrameAnimSprite::FrameAnimSprite(Texture* pTexture, int32_t pHeight, int32_t pWidth, Vector* pLocation) 
	: GraphicsSprite(pTexture)
{
	m_location = pLocation;

	m_height = pHeight;
	m_width = pWidth;
	m_frameCount = m_frameXCount = m_frameYCount = 0;

	m_animStartFrame = m_animFrameCount = 0;
	m_animSpeed = m_animFrame = 0;
	m_animLoop = false;
}

void FrameAnimSprite::load() 
{
	m_frameXCount = m_texture->getWidth() / m_width;
	m_frameYCount = m_texture->getHeight() / m_height;
	m_frameCount = (m_texture->getHeight() / m_height) * (m_texture->getWidth() / m_width);
}

void FrameAnimSprite::onDraw(float pTimeStep)
{
 	int32_t lCurrentFrame, lCurrentFrameX, lCurrentFrameY;

 	// Updates animation in loop mode.
 	m_animFrame += pTimeStep * m_animSpeed;
 	if (m_animLoop) 
 	{
 		lCurrentFrame = (m_animStartFrame + int32_t(m_animFrame) % m_animFrameCount);
 	}
 	// Updates animation in one-shot mode.
 	else 
 	{
 		// If animation ended.
 		if (animationEnded())
 			lCurrentFrame = m_animStartFrame + (m_animFrameCount-1);
 		else
 			lCurrentFrame = m_animStartFrame + int32_t(m_animFrame);
 	}

 	// Computes frame X and Y indexes from its id.
 	lCurrentFrameX = lCurrentFrame % m_frameXCount;
 	// lCurrentFrameY is converted from OpenGL coordinates to top-left coordinates.
 	lCurrentFrameY = m_frameYCount - 1 - (lCurrentFrame / m_frameXCount);
 	// Draws selected sprite frame.
 	m_texture->bind();

//	drawES11(lCurrentFrameX, lCurrentFrameY);
	drawES20(lCurrentFrameX, lCurrentFrameY);

	m_texture->unbind();
}

void FrameAnimSprite::setAnimation(int32_t pStartFrame, int32_t pFrameCount, float pSpeed, bool pLoop) 
{
	m_animStartFrame = pStartFrame;
	m_animFrame = 0.0f, m_animSpeed = pSpeed, m_animLoop = pLoop;

	int32_t lMaxFrameCount = m_frameCount - pStartFrame;
	if ((pFrameCount > -1) && (pFrameCount <= lMaxFrameCount)) 
		m_animFrameCount = pFrameCount;
	else
		m_animFrameCount = lMaxFrameCount;
}

bool FrameAnimSprite::animationEnded() 
{
	return m_animFrame > (m_animFrameCount - 1);
}

// void FrameAnimSprite::drawES11(int32_t lCurrentFrameX, int32_t lCurrentFrameY)
// {
//  	int32_t lCrop[] = { lCurrentFrameX * m_width, lCurrentFrameY * m_height, m_width, m_height };
//  	glTexParameteriv(GL_TEXTURE_2D, GL_TEXTURE_CROP_RECT_OES, lCrop);
//  	glDrawTexfOES(m_location->x - (m_width / 2), m_location->y - (m_height / 2), 0.0f, m_width, m_height);
// }

void FrameAnimSprite::drawES20(int32_t lCurrentFrameX, int32_t lCurrentFrameY)
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	const float hw = (float)m_width / 2, hh = (float)m_height / 2;
	const float x = m_location->x - hw,
		y = m_location->y - hh;
	GLfloat vertices[2 * 3 * 2];
	int index = 0;
	vertices[index++] = x - hw;
	vertices[index++] = y + hh;
	vertices[index++] = x - hw;
	vertices[index++] = y - hh;
	vertices[index++] = x + hw;
	vertices[index++] = y - hh;
	vertices[index++] = x + hw;
	vertices[index++] = y - hh;
	vertices[index++] = x + hw;
	vertices[index++] = y + hh;
	vertices[index++] = x - hw;
	vertices[index++] = y + hh;

	const float left = 1.0f / m_frameXCount * lCurrentFrameX,
		right = 1.0f / m_frameXCount * (lCurrentFrameX + 1),
		down = 1.0f / m_frameYCount * lCurrentFrameY,
		up = 1.0f / m_frameYCount * (lCurrentFrameY + 1);

	GLfloat texCoords[2 * 3 * 2];
	index = 0;
	texCoords[index++] = left;
	texCoords[index++] = up;
	texCoords[index++] = left;
	texCoords[index++] = down;
	texCoords[index++] = right;
	texCoords[index++] = down;
	texCoords[index++] = right;
	texCoords[index++] = down;
	texCoords[index++] = right;
	texCoords[index++] = up;
	texCoords[index++] = left;
	texCoords[index++] = up;

	glVertexPointer(2, GL_FLOAT, 0, &vertices[0]);
	glTexCoordPointer(2, GL_FLOAT, 0, &texCoords[0]);

	glDrawArrays(GL_TRIANGLES, 0, 2 * 3);

	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}