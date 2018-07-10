#include "f3Camera.h"
#include "../Tools/f3Math.h"

using namespace F3D;

void f3Camera4::init(uint32_t attr, const f3Vec4& pos, const f3Vec4& dir, 
					 const f3Vec4* target, float near_clip_z, float far_clip_z, 
					 float fov, float viewport_w, float viewport_h)
{
	m_u.set(1, 0, 0, 0);
	m_v.set(0, 1, 0, 0);
	m_n.set(0, 0, 1, 0);

	m_near_clip_z = near_clip_z;
	m_far_clip_z = far_clip_z;

	m_viewport_w = viewport_w;
	m_viewport_h = viewport_h;

	m_attr = attr;

	m_pos = pos;
	m_dir = dir;

	if (target != NULL) m_target = *target;

	m_viewport_x = (viewport_w - 1) * 0.5f;
	m_viewport_y = (viewport_h - 1) * 0.5f;

	m_aspect_ratio = viewport_w / viewport_h;

	m_mt_camera.identity();
	m_mt_perspective.identity();
	m_mt_screen.identity();

	m_fov = fov;

	m_viewplane_w = 2.0f;
	m_viewplane_h = 2.0f / m_aspect_ratio;

	const float tan_fov_dist = tan(fov * 0.5f * TRANS_DEG_TO_RAD);
	m_view_dist = 0.5f * m_viewplane_w * tan_fov_dist;

	f3Vec3 origin, vn;
	if (fov == 90.0f)
	{
		// right plane, x = z
		vn.set(1, 0, -1);
		m_right_clip.set(origin, vn);
		// left plane, -x = z
		vn.set(-1, 0, -1);
		m_left_clip.set(origin, vn);
		// top plane, y = z
		vn.set(0, 1, -1);
		m_top_clip.set(origin, vn);
		// down plane, -y = z
		vn.set(0, -1, -1);
		m_down_clip.set(origin, vn);
	}
	else
	{
		// right plane
		vn.set(m_view_dist, 0, - m_viewplane_w * 0.5f);
		m_right_clip.set(origin, vn);
		// left plane
		vn.set(-m_view_dist, 0, - m_viewplane_w * 0.5f);
		m_left_clip.set(origin, vn);
		// top plane
		vn.set(0, m_view_dist, - m_viewplane_h * 0.5f);
		m_top_clip.set(origin, vn);
		// down plane
		vn.set(0, -m_view_dist, - m_viewplane_h * 0.5f);
		m_down_clip.set(origin, vn);
	}
}

void f3Camera4::buildMatrixEuler(uint32_t rot_seq)
{
	f3Matrix4X4 mt_inv;
	mt_inv.set(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-m_pos.x, -m_pos.y, -m_pos.z, 1
		);
	
	float cos_theta = cos(m_dir.x),
		sin_theta = -sin(m_dir.x);
	f3Matrix4X4 mx_inv;
	mx_inv.set(
		1,			0,			0,			0,
		0,			cos_theta,	sin_theta,	0,
		0,			-sin_theta,	cos_theta,	0,
		0,			0,			0,			1
		);

	cos_theta = cos(m_dir.y);
	sin_theta = -sin(m_dir.y);
	f3Matrix4X4 my_inv;
	my_inv.set(
		cos_theta,	0,			-sin_theta,	0,
		0,			1,			0,			0,
		sin_theta,	0,			cos_theta,	0,
		0,			0,			0,			1
		);

	cos_theta = cos(m_dir.z);
	sin_theta = -sin(m_dir.z);
	f3Matrix4X4 mz_inv;
	mz_inv.set(
		cos_theta,	sin_theta,	0,			0,
		-sin_theta,	cos_theta,	0,			0,
		0,			0,			1,			0,
		0,			0,			0,			1
		);

	f3Matrix4X4 mtmp, mrot;
	switch (rot_seq)
	{
	case CAM_ROT_SEQ_XYZ:
		f3Mul(mx_inv, my_inv, &mtmp);
		f3Mul(mtmp, mz_inv, &mrot);
		break;
	case CAM_ROT_SEQ_YXZ:
		f3Mul(my_inv, mx_inv, &mtmp);
		f3Mul(mtmp, mz_inv, &mrot);
		break;
	case CAM_ROT_SEQ_XZY:
		f3Mul(mx_inv, mz_inv, &mtmp);
		f3Mul(mtmp, my_inv, &mrot);
		break;
	case CAM_ROT_SEQ_YZX:
		f3Mul(my_inv, mz_inv, &mtmp);
		f3Mul(mtmp, mx_inv, &mrot);
		break;
	case CAM_ROT_SEQ_ZYX:
		f3Mul(mz_inv, my_inv, &mtmp);
		f3Mul(mtmp, mx_inv, &mrot);
		break;
	case CAM_ROT_SEQ_ZXY:
		f3Mul(mz_inv, mx_inv, &mtmp);
		f3Mul(mtmp, my_inv, &mrot);
		break;
	}

	f3Mul(mt_inv, mrot, &m_mt_camera);
}

void f3Camera4::buildMatrixUVN(uint32_t mode)
{
	f3Matrix4X4 mt_inv;
	mt_inv.set(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		-m_pos.x, -m_pos.y, -m_pos.z, 1
		);

	if (mode == UVN_MODE_SPHERICAL)
	{
		float sin_phi = sin(m_dir.x), cos_phi = cos(m_dir.x);
		float sin_theta = sin(m_dir.y), cos_theta = cos(m_dir.y);

		m_target.x = -1 * sin_phi * sin_theta;
		m_target.y = 1 * cos_phi;
		m_target.z = 1 * sin_phi * cos_theta;
	}

	f3Sub(m_target, m_pos, &m_n);
	m_v.set(0, 1, 0, 1);
	f3Cross(m_v, m_n, &m_u);
	f3Cross(m_n, m_u, &m_v);

	m_u.normalize();
	m_v.normalize();
	m_n.normalize();

	f3Matrix4X4 mt_uvn;
	mt_uvn.set(
		m_u.x,	m_v.x,	m_n.x,	0,
		m_u.y,	m_v.y,	m_n.y,	0,
		m_u.z,	m_v.z,	m_n.z,	0,
		0,		0,		0,		1
		);

	f3Mul(mt_inv, mt_uvn, &m_mt_camera);
}