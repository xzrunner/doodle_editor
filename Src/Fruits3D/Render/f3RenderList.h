#ifndef _F3D_RENDER_RENDERLIST_H_
#define _F3D_RENDER_RENDERLIST_H_
#include "../Tools/Tools.h"
#include "f3Polygon.h"
#include "f3Line.h"

namespace F3D
{
	class f3Camera4;

	class f3RenderList4V1
	{
	public:
		~f3RenderList4V1();

		void removebackfaces(const f3Camera4& cam);

		void addPoly(f3Poly4V1* poly) { m_poly_ptrs.push_back(poly); }
		void addLine(f3Line4* line) { m_line_ptrs.push_back(line); }

	private:
		uint32_t state;
		uint32_t attr;

		std::vector<f3Poly4V1*> m_poly_ptrs;
		std::vector<f3Line4*> m_line_ptrs;

		friend class f3Transform;
		friend class f3Render;
	};
}

#endif // _F3D_RENDER_RENDERLIST_H_