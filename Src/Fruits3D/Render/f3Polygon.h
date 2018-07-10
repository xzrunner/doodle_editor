#ifndef _F3D_RENDER_POLYGON_H_
#define _F3D_RENDER_POLYGON_H_
#include "../Tools/Tools.h"
#include "../Tools/f3Types.h"

namespace F3D
{
	class f3Poly4V1
	{
	public:
		static const uint32_t ATTR_2SIDE				= 0x0001;
		static const uint32_t ATTR_TRANSPARENT			= 0x0002;
		static const uint32_t ATTR_8BITCOLOR			= 0x0004;
		static const uint32_t ATTR_RGB16				= 0x0008;
		static const uint32_t ATTR_RGB24				= 0x0010;

		static const uint32_t ATTR_SHADE_MODE_PURE		= 0x0020;
		static const uint32_t ATTR_SHADE_MODE_FLAT		= 0x0040;
		static const uint32_t ATTR_SHADE_MODE_GOURAUD	= 0x0080;
		static const uint32_t ATTR_SHADE_MODE_PHONG		= 0x0100;

		static const uint32_t STATE_ACTIVE				= 0x0001;
		static const uint32_t STATE_CLIPPED				= 0x0002;
		static const uint32_t STATE_BACKFACE			= 0x0004;

	public:
		f3Poly4V1() : m_state(STATE_ACTIVE), m_attr(0), m_prev(NULL), m_next(NULL) {}

		static bool isPolyValid(const f3Poly4V1* poly) {
			return (poly != NULL) 
				&& (poly->m_state & STATE_ACTIVE) 
				&& !(poly->m_state & STATE_CLIPPED) 
				&& !(poly->m_state & STATE_BACKFACE);
		}

//	private:
	public:
		uint32_t m_state;
		uint32_t m_attr;
		f3Colorf m_color;

		f3Vec4 m_vlist[3];
		f3Vec4 m_tvlist[3];

		f3Poly4V1 *m_prev, *m_next;

// 		friend class f3Transform;
// 		friend class f3Object4V1;
// 		friend class f3RenderList4V1;
// 		friend class f3Render;

	}; // f3Poly4V1

	class f3PolyF4V1
	{
	public:
		static const uint32_t ATTR_2SIDE				= 0x0001;
		static const uint32_t ATTR_TRANSPARENT			= 0x0002;
		static const uint32_t ATTR_8BITCOLOR			= 0x0004;
		static const uint32_t ATTR_RGB16				= 0x0008;
		static const uint32_t ATTR_RGB24				= 0x0010;

		static const uint32_t ATTR_SHADE_MODE_PURE		= 0x0020;
		static const uint32_t ATTR_SHADE_MODE_FLAT		= 0x0040;
		static const uint32_t ATTR_SHADE_MODE_GOURAUD	= 0x0080;
		static const uint32_t ATTR_SHADE_MODE_PHONG		= 0x0100;

		static const uint32_t STATE_ACTIVE				= 0x0001;
		static const uint32_t STATE_CLIPPED				= 0x0002;
		static const uint32_t STATE_BACKFACE			= 0x0004;

	public:
		f3PolyF4V1() : m_state(STATE_ACTIVE), m_attr(0) {}

		static bool isPolyValid(const f3PolyF4V1* poly) {
			return (poly != NULL) 
				&& (poly->m_state & STATE_ACTIVE) 
				&& !(poly->m_state & STATE_CLIPPED) 
				&& !(poly->m_state & STATE_BACKFACE);
		}

	private:
		uint32_t m_state;
		uint32_t m_attr;
		f3Colorf m_color;

		std::vector<f3Vec4>* m_vList;
		uint32_t m_vert[3];

		friend class f3Transform;
		friend class f3Object4V1;
		friend class f3Render;

	}; // f3PolyF4V1
}

#endif // _F3D_RENDER_POLYGON_H_