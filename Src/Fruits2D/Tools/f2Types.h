#ifndef _F2D_TYPES_H_
#define _F2D_TYPES_H_

#include <float.h>
#include <math.h>
#include <iostream>

namespace F2D
{
	static const float PI = 3.1415926f;
	static const float FLOAT_MAX = FLT_MAX;
	static const float EPSILON = FLT_EPSILON;
	static const float LARGE_EPSILON = 0.001f;
	static const float TRANS_DEG_TO_RAD = PI / 180.0f;
	static const float TRANS_RAD_TO_DEG = 180.0f / PI;
	static const float BOX2D_SCALE_FACTOR = 20.0f;

	class f2Vec2
	{
	public:
		f2Vec2() : x(0), y(0) {}
		f2Vec2(float x, float y) : x(x), y(y) {}
		f2Vec2(int x, int y) : x(static_cast<float>(x)), y(static_cast<float>(y)) {}
		f2Vec2(const f2Vec2& p) : x(p.x), y(p.y) {}

		f2Vec2& operator = (const f2Vec2& p) {
			x = p.x;
			y = p.y;
			return *this;
		}

		void setInvalid() { x = y = FLOAT_MAX; }
		bool isValid() const { return x != FLOAT_MAX && y != FLOAT_MAX; }

		void set(float _x, float _y) { x = _x; y = _y; }

		bool operator != (const f2Vec2& v) const
		{
			return x != v.x || y != v.y;
		}
		bool operator == (const f2Vec2& v) const
		{
			return x == v.x && y == v.y;
		}

		void operator += (const f2Vec2& v)
		{
			x += v.x; y += v.y;
		}

		void operator *= (float f)
		{
			x *= f; y *= f;
		}

		void operator /= (float f)
		{
			x /= f; y /= f;
		}

		f2Vec2 operator + (const f2Vec2& v) const
		{
			return f2Vec2(x + v.x, y + v.y);
		}

		f2Vec2 operator - (const f2Vec2& v) const
		{
			return f2Vec2(x - v.x, y - v.y);
		}

		f2Vec2 operator * (float scale) const
		{
			return f2Vec2(x * scale, y * scale);
		}

		f2Vec2 operator / (float scale) const
		{
			return f2Vec2(x / scale, y / scale);
		}

		f2Vec2 operator - () const
		{
			return f2Vec2(-x, -y);
		}

		float length() const
		{
			return sqrt(x * x + y * y);
		}

		void normalize() 
		{
			const float len = length();
			x /= len;
			y /= len;
		}

		void turnLeft90Deg() 
		{
			const float tmp = x;
			x = -y;
			y = tmp;
		}

		void toInteger() 
		{
			x = floor(x + 0.5f);
			y = floor(y + 0.5f);
		}

		float x, y;

	}; // f2Vec2

	//inline f2Vec2 operator + (const f2Vec2& a, const f2Vec2& b)
	//{
	//	return f2Vec2(a.x + b.x, a.y + b.y);
	//}

	//inline f2Vec2 operator - (const f2Vec2& a, const f2Vec2& b)
	//{
	//	return f2Vec2(a.x - b.x, a.y - b.y);
	//}

 //	inline f2Vec2 operator * (const f2Vec2& v, float s)
 //	{
 //		return f2Vec2(v.x * s, v.y * s);
 //	}

	inline float f2Cross(const f2Vec2& a, const f2Vec2& b)
	{
		return a.x * b.y - a.y * b.x;
	}

	inline float f2Dot(const f2Vec2& a, const f2Vec2& b)
	{
		return a.x * b.x + a.y * b.y;
	}

	inline std::istream& operator >> (std::istream& is, f2Vec2& pos)
	{
		is >> pos.x >> pos.y;
		return is;
	}
	inline std::ostream& operator << (std::ostream& os, const f2Vec2& pos)
	{
		os << pos.x << " " << pos.y;
		return os;
	}

	class PosCmp
	{
	public:
		bool operator () (const f2Vec2& p0, const f2Vec2& p1) const {
			return p0.x < p1.x || p0.x == p1.x && p0.y < p1.y;
		}
	}; // PosCmp

	class f2AABB
	{
	public:
		float xMin, xMax;
		float yMin, yMax;

		f2AABB() { makeInfinite(); }
		f2AABB(const f2Vec2& p0, const f2Vec2& p1) {
			xMin = std::min(p0.x, p1.x);
			yMin = std::min(p0.y, p1.y);
			xMax = std::max(p0.x, p1.x);
			yMax = std::max(p0.y, p1.y);
		}
		f2AABB(const f2Vec2& center, float hWidth, float hHeight) {
			xMin = center.x - hWidth;
			xMax = center.x + hWidth;
			yMin = center.y - hHeight;
			yMax = center.y + hHeight;
		}

		const f2AABB& operator = (const f2AABB& aabb)
		{
			xMin = aabb.xMin;
			xMax = aabb.xMax;
			yMin = aabb.yMin;
			yMax = aabb.yMax;
			return *this;
		}

		void operator *= (float scale)
		{
			const float cx = xCenter(),
				cy = yCenter();
			const float dx = xLength() * scale * 0.5f,
				dy = yLength() * scale * 0.5f;
			xMin = cx - dx;
			xMax = cx + dx;
			yMin = cy - dy;
			yMax = cy + dy;
		}

		bool isValid() const {
			return xMin != FLOAT_MAX && yMin != FLOAT_MAX
				&& xMax != - FLOAT_MAX && yMax != - FLOAT_MAX;
		}
		void makeInfinite() {
			xMin = yMin = FLOAT_MAX;
			xMax = yMax = - FLOAT_MAX;
		}

		float xLength() const { return xMax - xMin; }
		float yLength() const { return yMax - yMin; }

		float xCenter() const { return (xMin + xMax) * 0.5f; }
		float yCenter() const { return (yMin + yMax) * 0.5f; }

		void translate(const f2Vec2& offset)
		{
			xMin += offset.x;
			xMax += offset.x;
			yMin += offset.y;
			yMax += offset.y;
		}

		void combine(const f2Vec2& pos)
		{
			if (pos.x < xMin) xMin = pos.x;
			if (pos.x > xMax) xMax = pos.x;
			if (pos.y < yMin) yMin = pos.y;
			if (pos.y > yMax) yMax = pos.y;
		}
		void combine(const f2AABB& aabb)
		{
			if (aabb.xMin < xMin) xMin = aabb.xMin;
			if (aabb.xMax > xMax) xMax = aabb.xMax;
			if (aabb.yMin < yMin) yMin = aabb.yMin;
			if (aabb.yMax > yMax) yMax = aabb.yMax;
		}

	}; // f2AABB

	struct f2Colorf
	{
		float r, g, b, a;

		f2Colorf() 
			: r(0), g(0), b(0), a(1) {}
		f2Colorf(float _r, float _g, float _b) 
			: r(_r), g(_g), b(_b), a(1) {}
		f2Colorf(float _r, float _g, float _b, float _a) 
			: r(_r), g(_g), b(_b), a(_a) {}

		const f2Colorf& operator = (const f2Colorf& color)
		{
			r = color.r;
			g = color.g;
			b = color.b;
			a = color.a;
			return *this;
		}

		void set(float pr, float pg, float pb, float pa) {
			r = pr;
			g = pg;
			b = pb;
			a = pa;
		}

		void set(float pr, float pg, float pb) {
			r = pr;
			g = pg;
			b = pb;
		}

		unsigned int pack() const {
			return ((int)(r * 255 + 0.5f) << 24) | ((int)(g * 255 + 0.5f) << 16) | ((int)(b * 255 + 0.5f) << 8) | ((int)(r * 255 + 0.5f));
		}
		void unpack(unsigned int color) {
			r = ((color & 0xff000000) >> 24) / 255.0f;
			g = ((color & 0x00ff0000) >> 16) / 255.0f;
			b = ((color & 0x0000ff00) >> 8) / 255.0f;
			a = ((color & 0x000000ff)) / 255.0f;
		}

	}; // f2Colorf

	inline std::istream& operator >> (std::istream& is, f2Colorf& color)
	{
		is >> color.r >> color.g >> color.b >> color.a;
		return is;
	}
	inline std::ostream& operator << (std::ostream& os, const f2Colorf& color)
	{
		os << color.r << " " << color.g << " " << color.b << " " << color.a;
		return os;
	}

	struct f2Colori
	{
		int r, g, b, a;

		void set(int pr, int pg, int pb, int pa) {
			r = pr;
			g = pg;
			b = pb;
			a = pa;
		}

		void set(const f2Colori& c) { set(c.r, c.g, c.b, c.a); }

	}; // f2Colori
}

#endif // _F2D_TYPES_H_