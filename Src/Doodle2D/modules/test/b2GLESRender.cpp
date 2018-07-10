#include "b2GLESRender.h"

#include <GLES/gl.h>

using namespace d2d;

b2GLESRender::b2GLESRender(float32 ratio)
	: m_ratio(ratio)
{
}


void b2GLESRender::DrawPolygon(const b2Vec2* old_vertices, int vertexCount, const b2Color& color)
{
	b2Vec2* vertices = new b2Vec2[vertexCount];
	for( int i = 0; i < vertexCount; i++) 
	{
		vertices[i] = old_vertices[i];
		vertices[i] *= m_ratio;
	}

	glColor4f(color.r, color.g, color.b,1);
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_LINE_LOOP, 0, vertexCount);	

	delete[] vertices;
}

void b2GLESRender::DrawSolidPolygon(const b2Vec2* old_vertices, int vertexCount, const b2Color& color)
{
	b2Vec2* vertices = new b2Vec2[vertexCount];
	for( int i = 0; i < vertexCount; i++) 
	{
		vertices[i] = old_vertices[i];
		vertices[i] *= m_ratio;
	}

	glVertexPointer(2, GL_FLOAT, 0, vertices);

	glColor4f(color.r, color.g, color.b,0.5f);
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);

	glColor4f(color.r, color.g, color.b,1);
	glDrawArrays(GL_LINE_LOOP, 0, vertexCount);

	delete[] vertices;
}

void b2GLESRender::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
	const float32 k_segments = 16.0f;
	int vertexCount=16;
	const float32 k_increment = 2.0f * b2_pi / k_segments;
	float32 theta = 0.0f;

	GLfloat* glVertices = new GLfloat[vertexCount*2];
	for (int i = 0; i < k_segments; ++i)
	{
		b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
		glVertices[i*2]=v.x * m_ratio;
		glVertices[i*2+1]=v.y * m_ratio;
		theta += k_increment;
	}

	glColor4f(color.r, color.g, color.b,1);
	glVertexPointer(2, GL_FLOAT, 0, glVertices);

	glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);

	delete[] glVertices;
}

void b2GLESRender::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
	const float32 k_segments = 16.0f;
	int vertexCount=16;
	const float32 k_increment = 2.0f * b2_pi / k_segments;
	float32 theta = 0.0f;

	GLfloat* glVertices = new GLfloat[vertexCount*2];
	for (int i = 0; i < k_segments; ++i)
	{
		b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
		glVertices[i*2]=v.x * m_ratio;
		glVertices[i*2+1]=v.y * m_ratio;
		theta += k_increment;
	}

	glColor4f(color.r, color.g, color.b,0.5f);
	glVertexPointer(2, GL_FLOAT, 0, glVertices);
	glDrawArrays(GL_TRIANGLE_FAN, 0, vertexCount);
	glColor4f(color.r, color.g, color.b,1);
	glDrawArrays(GL_LINE_LOOP, 0, vertexCount);

	// Draw the axis line
	DrawSegment(center, center+radius*axis, color);

	delete[] glVertices;
}

void b2GLESRender::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	glColor4f(color.r, color.g, color.b,1);
	GLfloat	glVertices[] = 
	{
		p1.x * m_ratio, p1.y * m_ratio,
		p2.x * m_ratio, p2.y * m_ratio
	};
	glVertexPointer(2, GL_FLOAT, 0, glVertices);
	glDrawArrays(GL_LINES, 0, 2);
}

void b2GLESRender::DrawTransform(const b2Transform& xf)
{
	b2Vec2 p1 = xf.p, p2;
	const float32 k_axisScale = 0.4f;

	p2 = p1 + k_axisScale * xf.q.GetXAxis();
	DrawSegment(p1, p2, b2Color(1,0,0));

	p2 = p1 + k_axisScale * xf.q.GetYAxis();
	DrawSegment(p1, p2, b2Color(0,1,0));
}

void b2GLESRender::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{
	glColor4f(color.r, color.g, color.b,1);
	glPointSize(size);
	GLfloat	glVertices[] = {
		p.x * m_ratio, p.y * m_ratio
	};
	glVertexPointer(2, GL_FLOAT, 0, glVertices);
	glDrawArrays(GL_POINTS, 0, 1);
	glPointSize(1.0f);
}

void b2GLESRender::DrawString(int x, int y, const char *string, ...)
{
}

void b2GLESRender::DrawAABB(b2AABB* aabb, const b2Color& c)
{
	glColor4f(c.r, c.g, c.b,1);

	GLfloat	glVertices[] = {
		aabb->lowerBound.x * m_ratio, aabb->lowerBound.y * m_ratio,
		aabb->upperBound.x * m_ratio, aabb->lowerBound.y * m_ratio,
		aabb->upperBound.x * m_ratio, aabb->upperBound.y * m_ratio,
		aabb->lowerBound.x * m_ratio, aabb->upperBound.y * m_ratio
	};
	glVertexPointer(2, GL_FLOAT, 0, glVertices);
	glDrawArrays(GL_LINE_LOOP, 0, 8);
}