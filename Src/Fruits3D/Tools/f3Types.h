#ifndef _F3D_TOOLS_TYPES_H_
#define _F3D_TOOLS_TYPES_H_

namespace F3D
{
	struct f3Vec3
	{
		union {
			float val[3];

			struct {
				float x, y, z;
			};
		};

		f3Vec3() { memset(&val[0], 0, sizeof(float) * 3); }
		f3Vec3(float x, float y, float z) { set(x, y, z); }

		void set(float x, float y, float z) {
			val[0] = x;
			val[1] = y;
			val[2] = z;
		}

	}; // f3Vec3

	struct f3Vec4
	{
		union {
			float val[4];

			struct {
				float x, y, z, w;
			};
		};

		f3Vec4() { memset(&val[0], 0, sizeof(float) * 4); }
		f3Vec4(float x, float y, float z, float w) { set(x, y, z, w); }

		f3Vec4& operator = (const f3Vec4& p) {
			memcpy(&val[0], &p.val[0], sizeof(float) * 4);
			return *this;
		}

		void set(float x, float y, float z, float w) {
			val[0] = x;
			val[1] = y;
			val[2] = z;
			val[3] = w;
		}

		void normalize() {
			const float scale = sqrt(x * x + y * y + z * z);
			x /= scale;
			y /= scale;
			z /= scale;
			w = 1;
		}

	}; // f3Vec4

	inline std::istream& operator >> (std::istream& is, f3Vec4& pos)
	{
		is >> pos.x >> pos.y >> pos.z;
		pos.w = 1;
		return is;
	}
	inline std::ostream& operator << (std::ostream& os, const f3Vec4& pos)
	{
		os << pos.x << " " << pos.y << " " << pos.z;
		return os;
	}

	struct f3Plane
	{
		f3Vec3 p0;
		f3Vec3 n;

		void set(const f3Vec3& origin, const f3Vec3& vn) {
			p0 = origin;
			n = vn;
		}
	}; // f3Plane

	struct f3Matrix4X4
	{
		union {
			float val[4][4];

			struct {
				float m00, m01, m02, m03;
				float m10, m11, m12, m13;
				float m20, m21, m22, m23;
				float m30, m31, m32, m33;
			};
		};

		void set(
			float p00, float p01, float p02, float p03,
			float p10, float p11, float p12, float p13,
			float p20, float p21, float p22, float p23,
			float p30, float p31, float p32, float p33) {
			m00 = p00; m01 = p01; m02 = p02; m03 = p03;
			m10 = p10; m11 = p11; m12 = p12; m13 = p13;
			m20 = p20; m21 = p21; m22 = p22; m23 = p23;
			m30 = p30; m31 = p31; m32 = p32; m33 = p33;
		}

		void identity() {
			set(1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);
		}

		void buildTranslate(float x, float y, float z)
		{
			set(1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				x, y, z, 1);
		}

		void buildXRotation(float x) {
			set(1,		0,		0,		0,
				0,		cos(x), sin(x), 0,
				0,	   -sin(x), cos(x), 0,
				0,		0,		0,		1);
		}

		void buildYRotation(float y) {
			set(cos(y),	0,	   -sin(y),	0,
				0,		1,		0,		0,
				sin(y),	0,		cos(y), 0,
				0,		0,		0,		1);
		}

		void buildZRotation(float z) {
			set(cos(z),	sin(z),	0,		0,
			   -sin(z),	cos(z), 0,		0,
				0,		0,		1,		0,
				0,		0,		0,		1);
		}
	}; // f3Matrix4

	inline void f3Add(const f3Vec4& a0, const f3Vec4& a1, f3Vec4* sum)
	{
		sum->x = a0.x + a1.x;
		sum->y = a0.y + a1.y;
		sum->z = a0.z + a1.z;
		sum->w = 1.0f;
	}

	inline void f3Sub(const f3Vec4& a0, const f3Vec4& a1, f3Vec4* sub)
	{
		sub->x = a0.x - a1.x;
		sub->y = a0.y - a1.y;
		sub->z = a0.z - a1.z;
		sub->w = 1.0f;
	}

	inline void f3Cross(const f3Vec4& a0, const f3Vec4& a1, f3Vec4* cross)
	{
		cross->x = a0.y * a1.z - a0.z * a1.y;
		cross->y = a0.z * a1.x - a0.x * a1.z;
		cross->z = a0.x * a1.y - a0.y * a1.x;
		cross->w = 1.0f;
	}

	inline float f3Dot(const f3Vec4& a0, const f3Vec4& a1)
	{
		return a0.x * a1.x +  a0.y * a1.y +  a0.z * a1.z;
	}

	inline void f3Mul(const f3Vec4& p, const f3Matrix4X4& m, f3Vec4* ret)
	{
		ret->val[0] = p.val[0] * m.m00 + p.val[1] * m.m10 + p.val[2] * m.m20 + p.val[3] * m.m30;
		ret->val[1] = p.val[0] * m.m01 + p.val[1] * m.m11 + p.val[2] * m.m21 + p.val[3] * m.m31;
		ret->val[2] = p.val[0] * m.m02 + p.val[1] * m.m12 + p.val[2] * m.m22 + p.val[3] * m.m32;
		ret->val[3] = p.val[0] * m.m03 + p.val[1] * m.m13 + p.val[2] * m.m23 + p.val[3] * m.m33;
	}

	inline void f3Mul(const f3Matrix4X4& ma, const f3Matrix4X4& mb, f3Matrix4X4* mprod)
	{
		mprod->m00 = ma.m00 * mb.m00 + ma.m01 * mb.m10 + ma.m02 * mb.m20 + ma.m03 * mb.m30;
		mprod->m01 = ma.m00 * mb.m01 + ma.m01 * mb.m11 + ma.m02 * mb.m21 + ma.m03 * mb.m31;
		mprod->m02 = ma.m00 * mb.m02 + ma.m01 * mb.m12 + ma.m02 * mb.m22 + ma.m03 * mb.m32;
		mprod->m03 = ma.m00 * mb.m03 + ma.m01 * mb.m13 + ma.m02 * mb.m23 + ma.m03 * mb.m33;

		mprod->m10 = ma.m10 * mb.m00 + ma.m11 * mb.m10 + ma.m12 * mb.m20 + ma.m13 * mb.m30;
		mprod->m11 = ma.m10 * mb.m01 + ma.m11 * mb.m11 + ma.m12 * mb.m21 + ma.m13 * mb.m31;
		mprod->m12 = ma.m10 * mb.m02 + ma.m11 * mb.m12 + ma.m12 * mb.m22 + ma.m13 * mb.m32;
		mprod->m13 = ma.m10 * mb.m03 + ma.m11 * mb.m13 + ma.m12 * mb.m23 + ma.m13 * mb.m33;

		mprod->m20 = ma.m20 * mb.m00 + ma.m21 * mb.m10 + ma.m22 * mb.m20 + ma.m23 * mb.m30;
		mprod->m21 = ma.m20 * mb.m01 + ma.m21 * mb.m11 + ma.m22 * mb.m21 + ma.m23 * mb.m31;
		mprod->m22 = ma.m20 * mb.m02 + ma.m21 * mb.m12 + ma.m22 * mb.m22 + ma.m23 * mb.m32;
		mprod->m23 = ma.m20 * mb.m03 + ma.m21 * mb.m13 + ma.m22 * mb.m23 + ma.m23 * mb.m33;

		mprod->m30 = ma.m30 * mb.m00 + ma.m31 * mb.m10 + ma.m32 * mb.m20 + ma.m33 * mb.m30;
		mprod->m31 = ma.m30 * mb.m01 + ma.m31 * mb.m11 + ma.m32 * mb.m21 + ma.m33 * mb.m31;
		mprod->m32 = ma.m30 * mb.m02 + ma.m31 * mb.m12 + ma.m32 * mb.m22 + ma.m33 * mb.m32;
		mprod->m33 = ma.m30 * mb.m03 + ma.m31 * mb.m13 + ma.m32 * mb.m23 + ma.m33 * mb.m33;
	}

	struct f3Colorf
	{
		float r, g, b;

		f3Colorf() 
			: r(0.0f), g(0.0f), b(0.0f) {}
		f3Colorf(float _r, float _g, float _b) 
			: r(_r), g(_g), b(_b) {}

		void set(float pr, float pg, float pb) {
			r = pr;
			g = pg;
			b = pb;
		}
	}; // f3Colorf
}

#endif // _F3D_TOOLS_TYPES_H_