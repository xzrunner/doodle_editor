#ifndef _F3D_RENDER_REBDER_H_
#define _F3D_RENDER_REBDER_H_
#include "../Tools/Tools.h"

namespace F3D
{
	class f3RenderList4V1;
	class f3Object4V1;

	class f3Render
	{
	public:
		static void draw(const f3Object4V1& object);
		static void draw(const f3RenderList4V1& renderlist, bool renderFace = false, float alpha = 1.0f);
	}; // f3Render
}

#endif // _F3D_RENDER_REBDER_H_