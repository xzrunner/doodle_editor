#include "f3RenderList.h"
#include "f3Camera.h"

using namespace F3D;

f3RenderList4V1::~f3RenderList4V1()
{
	for (size_t i = 0, size = m_poly_ptrs.size(); i < size; ++i) delete m_poly_ptrs[i];
	for (size_t i = 0, size = m_line_ptrs.size(); i < size; ++i) delete m_line_ptrs[i];
}

void f3RenderList4V1::removebackfaces(const f3Camera4& cam)
{
	for (size_t i = 0, size = m_poly_ptrs.size(); i < size; ++i)
	{
		f3Poly4V1* poly = m_poly_ptrs[i];

		if (!f3Poly4V1::isPolyValid(poly) ||
			poly->m_attr & f3Poly4V1::ATTR_2SIDE)
			continue;

		f3Vec4 u, v, n;
		f3Sub(poly->m_tvlist[1], poly->m_tvlist[0], &u);
		f3Sub(poly->m_tvlist[2], poly->m_tvlist[0], &v);
		f3Cross(u, v, &n);

		f3Vec4 view;
		f3Sub(poly->m_tvlist[0], cam.m_pos, &view);

		if (f3Dot(n, view) < 0)
		{
			poly->m_state |= f3Poly4V1::STATE_BACKFACE;
		}
	}
}