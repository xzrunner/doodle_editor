#include "f3Object.h"
#include "f3Camera.h"

using namespace F3D;

void f3Object4V1::inputFromFile(const std::string& file)
{
	m_vlist_local.clear();
	m_vlist_trans.clear();
	m_plist.clear();

	std::ifstream fin(file.c_str());

	size_t vSize, pSize;
	fin >> vSize >> pSize;

	m_vlist_local.reserve(vSize);
	m_vlist_trans.resize(vSize);
	for (size_t i = 0; i < vSize; ++i)
	{
		f3Vec4 p;
		fin >> p;
		p.w = 1;
		m_vlist_local.push_back(p);
	}

	m_plist.reserve(pSize);
	for (size_t i = 0; i < pSize; ++i)
	{
		f3PolyF4V1 p;
		p.m_vList = &m_vlist_trans;
		fin >> p.m_vert[0] >> p.m_vert[1] >> p.m_vert[2];
		p.m_color = f3Colorf(1.0f, 0.0f, 0.0f);
		m_plist.push_back(p);
	}

	fin.close();
}

void f3Object4V1::cull(const f3Camera4& cam, uint32_t cull_type)
{
	f3Vec4 sphere_pos;
	f3Mul(m_world_pos, cam.m_mt_camera, &sphere_pos);

	if (cull_type & CULL_Z_PLANE)
	{
		if (sphere_pos.z - m_max_radius > cam.m_far_clip_z ||
			sphere_pos.z + m_max_radius < cam.m_near_clip_z)
		{
			m_state |= STATE_CULLED;
			return;
		}
	}

	if (cull_type & CULL_X_PLANE)
	{

		float z_test = 0.5f * cam.m_viewplane_w * sphere_pos.z / cam.m_view_dist;
		if (sphere_pos.x - m_max_radius > z_test ||
			sphere_pos.x + m_max_radius < -z_test)
		{
			m_state |= STATE_CULLED;
			return;
		}
	}

	if (cull_type & CULL_Y_PLANE)
	{

		float z_test = 0.5f * cam.m_viewplane_h * sphere_pos.z / cam.m_view_dist;
		if (sphere_pos.y - m_max_radius > z_test ||
			sphere_pos.y + m_max_radius < -z_test)
		{
			m_state |= STATE_CULLED;
			return;
		}
	}
}

void f3Object4V1::removebackfaces(const f3Camera4& cam)
{
	if (m_state & STATE_CULLED) return;

	for (size_t i = 0, size = m_plist.size(); i < size; ++i)
	{
		f3PolyF4V1& poly = m_plist[i];

// 		if (!f3PolyF4V1::isPolyValid(&poly) ||
// 			poly.m_attr & f3PolyF4V1::ATTR_2SIDE)
// 			continue;
		if (poly.m_attr & f3PolyF4V1::ATTR_2SIDE) continue;
		
		const int v0 = poly.m_vert[0],
			v1 = poly.m_vert[1],
			v2 = poly.m_vert[2];

		f3Vec4 u, v, n;
		f3Sub(m_vlist_trans[v1], m_vlist_trans[v0], &u);
		f3Sub(m_vlist_trans[v2], m_vlist_trans[v0], &v);
		f3Cross(u, v, &n);

		f3Vec4 view;
		f3Sub(m_vlist_trans[v0], cam.m_pos, &view);

		poly.m_state &= ~f3PolyF4V1::STATE_BACKFACE;
		if (f3Dot(n, view) < 0)
		{
			poly.m_state |= f3PolyF4V1::STATE_BACKFACE;
		}
	}
}

void f3Object4V1::reset()
{
	m_state &= !STATE_CULLED;
	for (size_t i = 0, n = m_plist.size(); i < n; ++i)
	{
		f3PolyF4V1& poly = m_plist[i];
		if (!(poly.m_state & f3PolyF4V1::STATE_ACTIVE)) continue;
		poly.m_state &= !f3PolyF4V1::STATE_CLIPPED;
		poly.m_state &= !f3PolyF4V1::STATE_BACKFACE;
	}
}