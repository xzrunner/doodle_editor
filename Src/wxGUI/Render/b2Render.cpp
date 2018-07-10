#include "b2Render.h"
#include "GL10.h"

using namespace std;
using namespace wxgui;

b2GLRender::b2GLRender(float32 ratio)
	: m_ratio(ratio)
{
}


void b2GLRender::DrawPolygon(const b2Vec2* old_vertices, int vertexCount, const b2Color& color)
{
	b2Vec2* vertices = new b2Vec2[vertexCount];
	for( int i = 0; i < vertexCount; i++) 
	{
		vertices[i] = old_vertices[i];
		vertices[i] *= m_ratio;
	}

	GL10::Color4f(color.r, color.g, color.b,1);
	GL10::VertexPointer(2, GL10::GL_FLOAT, 0, vertices);
	GL10::DrawArrays(GL10::GL_LINE_LOOP, 0, vertexCount);	

	delete[] vertices;
}

void b2GLRender::DrawSolidPolygon(const b2Vec2* old_vertices, int vertexCount, const b2Color& color)
{
	b2Vec2* vertices = new b2Vec2[vertexCount];
	for( int i = 0; i < vertexCount; i++) 
	{
		vertices[i] = old_vertices[i];
		vertices[i] *= m_ratio;
	}

	GL10::VertexPointer(2, GL10::GL_FLOAT, 0, vertices);

	GL10::Color4f(color.r, color.g, color.b,0.5f);
	GL10::DrawArrays(GL10::GL_TRIANGLE_FAN, 0, vertexCount);

	GL10::Color4f(color.r, color.g, color.b,1);
	GL10::DrawArrays(GL10::GL_LINE_LOOP, 0, vertexCount);

	delete[] vertices;
}

void b2GLRender::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color)
{
	const float32 k_segments = 16.0f;
	int vertexCount=16;
	const float32 k_increment = 2.0f * b2_pi / k_segments;
	float32 theta = 0.0f;

	float* vertices = new float[vertexCount*2];
	for (int i = 0; i < k_segments; ++i)
	{
		b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
		vertices[i*2]=v.x * m_ratio;
		vertices[i*2+1]=v.y * m_ratio;
		theta += k_increment;
	}

	GL10::Color4f(color.r, color.g, color.b,1);
	GL10::VertexPointer(2, GL10::GL_FLOAT, 0, vertices);

	GL10::DrawArrays(GL10::GL_TRIANGLE_FAN, 0, vertexCount);

	delete[] vertices;
}

void b2GLRender::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color)
{
	const float32 k_segments = 16.0f;
	int vertexCount=16;
	const float32 k_increment = 2.0f * b2_pi / k_segments;
	float32 theta = 0.0f;

	float* vertices = new float[vertexCount*2];
	for (int i = 0; i < k_segments; ++i)
	{
		b2Vec2 v = center + radius * b2Vec2(cosf(theta), sinf(theta));
		vertices[i*2]=v.x * m_ratio;
		vertices[i*2+1]=v.y * m_ratio;
		theta += k_increment;
	}

	GL10::Color4f(color.r, color.g, color.b,0.5f);
	GL10::VertexPointer(2, GL10::GL_FLOAT, 0, vertices);
	GL10::DrawArrays(GL10::GL_TRIANGLE_FAN, 0, vertexCount);
	GL10::Color4f(color.r, color.g, color.b,1);
	GL10::DrawArrays(GL10::GL_LINE_LOOP, 0, vertexCount);

	// Draw the axis line
	DrawSegment(center, center+radius*axis, color);

	delete[] vertices;
}

void b2GLRender::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color)
{
	GL10::Color4f(color.r, color.g, color.b,1);
	float vertices[] = 
	{
		p1.x * m_ratio, p1.y * m_ratio,
		p2.x * m_ratio, p2.y * m_ratio
	};
	GL10::VertexPointer(2, GL10::GL_FLOAT, 0, vertices);
	GL10::DrawArrays(GL10::GL_LINES, 0, 2);
}

void b2GLRender::DrawTransform(const b2Transform& xf)
{
	b2Vec2 p1 = xf.p, p2;
	const float32 k_axisScale = 0.4f;

	p2 = p1 + k_axisScale * xf.q.GetXAxis();
	DrawSegment(p1, p2, b2Color(1,0,0));

	p2 = p1 + k_axisScale * xf.q.GetYAxis();
	DrawSegment(p1, p2, b2Color(0,1,0));
}

void b2GLRender::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color)
{
	GL10::Color4f(color.r, color.g, color.b,1);
	GL10::PointSize(size);
	float vertices[] = {
		p.x * m_ratio, p.y * m_ratio
	};
	GL10::VertexPointer(2, GL10::GL_FLOAT, 0, vertices);
	GL10::DrawArrays(GL10::GL_POINTS, 0, 1);
	GL10::PointSize(1.0f);
}

void b2GLRender::DrawString(int x, int y, const char *string, ...)
{
}

void b2GLRender::DrawAABB(b2AABB* aabb, const b2Color& c)
{
	GL10::Color4f(c.r, c.g, c.b,1);

	float vertices[] = {
		aabb->lowerBound.x * m_ratio, aabb->lowerBound.y * m_ratio,
		aabb->upperBound.x * m_ratio, aabb->lowerBound.y * m_ratio,
		aabb->upperBound.x * m_ratio, aabb->upperBound.y * m_ratio,
		aabb->lowerBound.x * m_ratio, aabb->upperBound.y * m_ratio
	};
	GL10::VertexPointer(2, GL10::GL_FLOAT, 0, vertices);
	GL10::DrawArrays(GL10::GL_LINE_LOOP, 0, 8);
}