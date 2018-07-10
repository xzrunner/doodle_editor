#ifndef _D2D_VECTOR_H_
#define _D2D_VECTOR_H_

#include <cmath>

namespace d2d
{
	class Vector
	{
	public:
		Vector();
		Vector(float x, float y);
		Vector(int x, int y);

		void set(float x, float y);

		float getLength() const;
		float normalize();

		bool operator != (const Vector& v) const;
		bool operator == (const Vector& v) const;

		Vector operator + (const Vector& v) const;
		Vector operator - (const Vector& v) const;
		Vector operator * (float s) const;
		Vector operator / (float s) const;
		Vector operator - () const;
		void operator += (const Vector& v);
		void operator -= (const Vector& v);
		void operator *= (float s);
		void operator /= (float s);

	public:
		float x, y;

	}; // Vector

	inline Vector::Vector()
	{
		x = 0.0f;
		y = 0.0f;
	}

	inline Vector::Vector(float x, float y)
	{
		set(x, y);
	}

	inline Vector::Vector(int x, int y)
	{
		set(static_cast<float>(x), static_cast<float>(y));
	}

	inline void Vector::set(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	inline float Vector::getLength() const
	{
		return sqrt(x*x + y*y);
	}

	inline float Vector::normalize()
	{
		float len = getLength();
		if (len > 0)
			(*this) /= len;
		return len;
	}

	inline bool Vector::operator != (const Vector& v) const
	{
		return x != v.x || y != v.y;
	}

	inline bool Vector::operator == (const Vector& v) const
	{
		return x == v.x && y == v.y;
	}

	inline Vector Vector::operator + (const Vector& v) const
	{
		return Vector(x + v.x, y + v.y);
	}

	inline Vector Vector::operator - (const Vector& v) const
	{
		return Vector(x - v.x, y - v.y);
	}

	inline Vector Vector::operator * (float s) const
	{
		return Vector(x*s, y*s);
	}

	inline Vector Vector::operator / (float s) const
	{
		return Vector(x/s, y/s);
	}

	inline Vector Vector::operator - () const
	{
		return Vector(-x, -y);
	}

	inline void Vector::operator += (const Vector& v)
	{
		x += v.x;
		y += v.y;
	}

	inline void Vector::operator -= (const Vector& v)
	{
		x -= v.x;
		y -= v.y;
	}

	inline void Vector::operator *= (float s)
	{
		x *= s;
		y *= s;
	}

	inline void Vector::operator /= (float s)
	{
		x /= s;
		y /= s;
	}

	inline float cross(const Vector& a, const Vector& b)
	{
		return a.x * b.y - a.y * b.x;
	}

	inline float dot(const Vector& a, const Vector& b)
	{
		return a.x * b.x + a.y * b.y;
	}
}

#endif // _D2D_VECTOR_H_