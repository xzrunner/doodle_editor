#ifndef _F3D_RENDER_LINE_H_
#define _F3D_RENDER_LINE_H_
#include "../Tools/Tools.h"
#include "../Tools/f3Types.h"

namespace F3D
{
	class f3Line4
	{
	public:
		f3Line4() : m_prev(NULL), m_next(NULL) {}

	public:
		f3Colorf m_color;

		f3Vec4 m_vlist[2];
		f3Vec4 m_tvlist[2];

		f3Line4 *m_prev, *m_next;
	}; // f3Line4
}

#endif // _F3D_RENDER_LINE_H_