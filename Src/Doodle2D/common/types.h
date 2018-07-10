#ifndef _D2D_TYPES_H_
#define _D2D_TYPES_H_

#include "config.h"

#include <cstdlib>

#ifdef D2D_WINDOWS

typedef __int8 int8_t;
typedef __int16 int16_t;
typedef __int32 int32_t;
typedef __int64 int64_t;
typedef unsigned __int8 uint8_t;
typedef unsigned __int16 uint16_t;
typedef unsigned __int32 uint32_t;
typedef unsigned __int64 uint64_t;

typedef uint8_t byte;

#else

typedef unsigned char byte;

#endif

namespace d2d
{
	typedef int32_t status;

	const status STATUS_OK		= 0;
	const status STATUS_KO		= -1;
	const status STATUS_EXIT	= -2;

	static const int SCREEN_HEIGHT = 480;
	static const int SCREEN_WIDTH = 800;

	struct Vertex
	{
		unsigned char r, g, b, a;
		float x, y;
		float u, v;

		Vertex() : r(255), g(255), b(255), a(255) {}
	};
}

#endif // _D2D_TYPES_H_