#ifndef _F3D_RENDER_CAMERA_H_
#define _F3D_RENDER_CAMERA_H_
#include "../Tools/Tools.h"
#include "../Tools/f3Types.h"

namespace F3D
{
	class f3Camera4
	{
	public:
		static const uint32_t CAM_ROT_SEQ_XYZ = 0;
		static const uint32_t CAM_ROT_SEQ_YXZ = 1;
		static const uint32_t CAM_ROT_SEQ_XZY = 2;
		static const uint32_t CAM_ROT_SEQ_YZX = 3;
		static const uint32_t CAM_ROT_SEQ_ZYX = 4;
		static const uint32_t CAM_ROT_SEQ_ZXY = 5;

		static const uint32_t UVN_MODE_SPHERICAL = 0;

	public:
		void init(
			uint32_t attr,
			const f3Vec4& pos, const f3Vec4& dir,
			const f3Vec4* target,
			float near_clip_z, float far_clip_z,
			float fov,
			float viewport_w, float viewport_h
			);

		void buildMatrixEuler(uint32_t cam_rot_seq);
		void buildMatrixUVN(uint32_t mode);

		void setPos(const f3Vec4& pos) { m_pos = pos; }
		void setDir(const f3Vec4& dir) { m_dir = dir; }

	private:
		uint32_t m_state;
		uint32_t m_attr;

		f3Vec4 m_pos;
		f3Vec4 m_dir;

		f3Vec4 m_u, m_v, m_n;
		f3Vec4 m_target;

//		float m_view_dist_h, m_view_dist_w;
		float m_view_dist;

		float m_fov;

		float m_near_clip_z, m_far_clip_z;

		f3Plane m_left_clip, m_right_clip, m_top_clip, m_down_clip;

		float m_viewplane_w, m_viewplane_h;

		float m_viewport_w, m_viewport_h;
		float m_viewport_x, m_viewport_y;

		float m_aspect_ratio;

		f3Matrix4X4 m_mt_camera, m_mt_perspective, m_mt_screen;

		friend class f3Transform;
		friend class f3Object4V1;
		friend class f3RenderList4V1;

	}; // f3Camera4
}

#endif // _F3D_RENDER_CAMERA_H_