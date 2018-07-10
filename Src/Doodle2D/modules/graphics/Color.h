#ifndef _D2D_COLOR_H_
#define _D2D_COLOR_H_

namespace d2d
{
	class Color
	{
	public:
		Color() : r(0), g(0), b(0), a(1) {}
		Color(int red, int green, int blue, int alpha)
			: r(red), g(green), b(blue), a(alpha) {}

		void unpack(unsigned int color) {
			r = (color & 0xff000000) >> 24;
			g = (color & 0x00ff0000) >> 16;
			b = (color & 0x0000ff00) >> 8;
			a = (color & 0x000000ff);
		}

	public:
		unsigned char r, g, b, a;

	}; // Color
}

#endif // _D2D_COLOR_H_