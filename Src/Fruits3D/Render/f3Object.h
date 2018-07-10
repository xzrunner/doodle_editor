#ifndef _F3D_RENDER_OBJECT_H_
#define _F3D_RENDER_OBJECT_H_
#include "../Tools/Tools.h"
#include "../Tools/f3Types.h"
#include "f3Polygon.h"

namespace F3D
{
	class f3Camera4;

	class f3Object4V1
	{
	public:
		f3Object4V1() : m_state(STATE_ACTIVE), m_ux(1, 0, 0, 0), m_uy(0, 1, 0, 0), m_uz(0, 0, 1, 0) {}

		void inputFromFile(const std::string& file);

		void cull(const f3Camera4& cam, uint32_t cull_type);
		void removebackfaces(const f3Camera4& cam);

		void reset();

	public:
		static const uint32_t STATE_ACTIVE	= 0x0001;
		static const uint32_t STATE_VISIBLE	= 0x0002;
		static const uint32_t STATE_CULLED	= 0x0004;

		static const uint32_t CULL_X_PLANE = 0x0001;
		static const uint32_t CULL_Y_PLANE = 0x0002;
		static const uint32_t CULL_Z_PLANE = 0x0004;
		static const uint32_t CULL_XYZ_PLANES = CULL_X_PLANE | CULL_Y_PLANE | CULL_Z_PLANE;

	private:
		uint32_t m_id;
		std::string m_name;
		uint32_t m_state;
		uint32_t m_attr;
		float m_avg_radius, m_max_radius;

		f3Vec4 m_world_pos;
		f3Vec4 m_dir;
		f3Vec4 m_ux, m_uy, m_uz;

		std::vector<f3Vec4> m_vlist_local;
		std::vector<f3Vec4> m_vlist_trans;

		std::vector<f3PolyF4V1> m_plist;

		friend class f3Transform;
		friend class f3Render;

	}; // f3Object4V1
}

#endif // _F3D_RENDER_OBJECT_H_