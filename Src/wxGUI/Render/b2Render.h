#ifndef _BOX2D_RENDER_H_
#define _BOX2D_RENDER_H_
 
#include <Box2D/Box2D.h>

struct b2AABB;

class b2GLRender : public b2Draw
{
public:
	b2GLRender(float32 ratio);

	virtual void DrawPolygon(const b2Vec2* vertices, int vertexCount, const b2Color& color);

	virtual void DrawSolidPolygon(const b2Vec2* vertices, int vertexCount, const b2Color& color);

	virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);

	virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);

	virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);

	virtual void DrawTransform(const b2Transform& xf);

	virtual void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color);

	virtual void DrawString(int x, int y, const char* string, ...); 

	virtual void DrawAABB(b2AABB* aabb, const b2Color& color);

private:
	float32 m_ratio;

}; // b2GLRender

#endif // _BOX2D_RENDER_H_
