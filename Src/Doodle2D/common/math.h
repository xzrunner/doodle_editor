#ifndef _D2D_MATH_H_
#define _D2D_MATH_H_

#include "Vector.h"

#include <float.h>
#include <math.h>
#include <algorithm>

namespace d2d
{
	static const float BOX2D_SCALE_FACTOR = 20.0f;
	static const float BOX2D_SCALE_FACTOR_INVERSE = 1.0f / BOX2D_SCALE_FACTOR;

	static const float PI = 3.1415927f;
	static const float FLOAT_MAX = FLT_MAX;
	static const float radiansToDegrees = 180.0f / PI;
	static const float degreesToRadians = PI / 180.0f;

	inline double factorial(int num)
	{
		double fact = 1;
		for(int i = 1; i <= num; i++)
			fact *= i;
		return fact;
	}

	inline double taylorSin(double m)
	{
		int x = 1;
		for(int i = 3; i < 13; i=i+2)
		{
			m = m + pow(-1.0,x) * (pow(m,i)) / factorial(i);
			x++;
		}
		return m;
	}

	inline double taylorCos(double m)
	{
		double n = 1;
		int x = 1;

		for(int i = 2; i<12; i=i+2)
		{
			n = n + pow(-1.0,x) * (pow(m,i)) / factorial(i);
			x++;
		}
		return n;
	}

	inline void rotateVector(const Vector& src, float rad, Vector& dst)
	{
		dst.x = src.x * cos(rad) - src.y * sin(rad);
		dst.y = src.x * sin(rad) + src.y * cos(rad);
	}

	inline float getDistance(const Vector& p0, const Vector& p1)
	{
		const float dx = p0.x - p1.x,
			dy = p0.y - p1.y;
		return sqrt(dx * dx + dy * dy);
	}

	inline float getAngle(const Vector& center, const Vector& pa, const Vector& pb)
	{
		const float a = getDistance(center, pa),
			b = getDistance(center, pb),
			c = getDistance(pa, pb);

		float cosVal = (a * a + b * b - c * c) / (2 * a * b);
		cosVal = std::max(std::min(cosVal, 1.0f), -1.0f);

		return acos(cosVal);
	}

	inline float getLineAngle(const Vector& s, const Vector& e)
	{
		const Vector other(s.x + 1.0f, s.y);
		const float ang = getAngle(s, e, other);
		if (cross(other - s, e - s) > 0) return ang;
		else return -ang;
	}

	inline unsigned long getNextPOT(unsigned long x)
	{
		x = x - 1;
		x = x | (x >> 1);
		x = x | (x >> 2);
		x = x | (x >> 4);
		x = x | (x >> 8);
		x = x | (x >>16);
		return x + 1;
	}

	template <typename T>
	inline T RAND(const T& max)
	{
		return (rand() / (float(RAND_MAX) + 1)) * max;
	}

	template <typename T>
	inline T RAND(const T& min, const T& max)
	{
		return (rand() / (float(RAND_MAX) + 1)) * (max - min) + min;
	}
}

#endif // _D2D_MATH_H_