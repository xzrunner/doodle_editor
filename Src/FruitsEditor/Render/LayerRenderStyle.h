#ifndef _FEDITOR_LAYER_RENDER_STYLE_H_
#define _FEDITOR_LAYER_RENDER_STYLE_H_
#include <Fruits2D/Fruits2D.h>

namespace FEDITOR
{
	class LayerRenderStyle
	{
	public:
		LayerRenderStyle();

	public:
		struct RenderStyle
		{
			f2Colorf color;
			float size;
		}; // RenderStyle

	public:
		RenderStyle m_pointStyle;
		RenderStyle m_chainStyle, m_ctlposStyle;
		RenderStyle m_triangleStyle;

		bool m_bDrawShape;
		bool m_bDrawCtlPos;
		bool m_bDrawAABB;
		bool m_bShapeMask;
		
	}; // LayerRenderStyle

	inline LayerRenderStyle::LayerRenderStyle()
	{
		m_pointStyle.color = f2Colorf(0, 0, 1);
		m_pointStyle.size = 3;

		m_chainStyle.color = f2Colorf(1, 0, 0);
		m_chainStyle.size = 3;

		m_ctlposStyle.color = f2Colorf(0, 1, 0);
		m_ctlposStyle.size = 5;

		m_triangleStyle.color = f2Colorf(0, 0, 0.5f);

		m_bDrawShape = true;
		m_bDrawCtlPos = true;
		m_bDrawAABB = false;
		m_bShapeMask = false;
	}
}

#endif // _FEDITOR_LAYER_RENDER_STYLE_H_