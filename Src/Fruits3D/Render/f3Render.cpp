#include "f3Render.h"
#include "f3RenderList.h"
#include "f3Object.h"

#include <windows.h>
#include <GL/gl.h>

using namespace F3D;

void f3Render::draw(const f3Object4V1& object)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, 1);

	for (size_t i = 0, n = object.m_plist.size(); i < n; ++i)
	{
		const f3PolyF4V1& poly = object.m_plist[i];
		if (!f3PolyF4V1::isPolyValid(&poly)) continue;

		const uint32_t v0 = poly.m_vert[0],
			v1 = poly.m_vert[1],
			v2 = poly.m_vert[2];

		glBegin(GL_LINE_LOOP);
			glColor3f(poly.m_color.r, poly.m_color.g, poly.m_color.b); glVertex3f((*poly.m_vList)[v0].x, (*poly.m_vList)[v0].y, 0);
			glColor3f(poly.m_color.r, poly.m_color.g, poly.m_color.b); glVertex3f((*poly.m_vList)[v1].x, (*poly.m_vList)[v1].y, 0);
			glColor3f(poly.m_color.r, poly.m_color.g, poly.m_color.b); glVertex3f((*poly.m_vList)[v2].x, (*poly.m_vList)[v2].y, 0);
		glEnd();
	}
}

void f3Render::draw(const f3RenderList4V1& renderlist, bool renderFace/* = false*/, float alpha/* = 1.0f*/)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0, 0, 1);

	// poly
	if (renderFace)
	{
		glBegin(GL_TRIANGLES);
		for (size_t i = 0, n = renderlist.m_poly_ptrs.size(); i < n; ++i)
		{
			f3Poly4V1* poly = renderlist.m_poly_ptrs[i];
			if (!f3Poly4V1::isPolyValid(poly)) continue;

			glColor4f(poly->m_color.r, poly->m_color.g, poly->m_color.b, alpha); glVertex3f(poly->m_tvlist[0].x, poly->m_tvlist[0].y, 0);
			glColor4f(poly->m_color.r, poly->m_color.g, poly->m_color.b, alpha); glVertex3f(poly->m_tvlist[1].x, poly->m_tvlist[1].y, 0);
			glColor4f(poly->m_color.r, poly->m_color.g, poly->m_color.b, alpha); glVertex3f(poly->m_tvlist[2].x, poly->m_tvlist[2].y, 0);
		}
		glEnd();
	}
	else
	{
		glBegin(GL_LINE_LOOP);
		for (size_t i = 0, n = renderlist.m_poly_ptrs.size(); i < n; ++i)
		{
			f3Poly4V1* poly = renderlist.m_poly_ptrs[i];
			if (!f3Poly4V1::isPolyValid(poly)) continue;

			glColor3f(poly->m_color.r, poly->m_color.g, poly->m_color.b); glVertex3f(poly->m_tvlist[0].x, poly->m_tvlist[0].y, 0);
			glColor3f(poly->m_color.r, poly->m_color.g, poly->m_color.b); glVertex3f(poly->m_tvlist[1].x, poly->m_tvlist[1].y, 0);
			glColor3f(poly->m_color.r, poly->m_color.g, poly->m_color.b); glVertex3f(poly->m_tvlist[2].x, poly->m_tvlist[2].y, 0);
		}
		glEnd();
	}

	// line
	glBegin(GL_LINES);
	for (size_t i = 0, n = renderlist.m_line_ptrs.size(); i < n; ++i)
	{
		f3Line4* line = renderlist.m_line_ptrs[i];
		glColor3f(line->m_color.r, line->m_color.g, line->m_color.b); glVertex3f(line->m_tvlist[0].x, line->m_tvlist[0].y, 0);
		glColor3f(line->m_color.r, line->m_color.g, line->m_color.b); glVertex3f(line->m_tvlist[1].x, line->m_tvlist[1].y, 0);
	}
	glEnd();
}