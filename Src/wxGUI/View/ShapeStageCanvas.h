#ifndef _WX_GUI_SHAPE_STAGE_CANVAS_H_
#define _WX_GUI_SHAPE_STAGE_CANVAS_H_

#include "GLCanvas.h"

namespace wxgui
{
	class EditPanel;
	class MultiShapesImpl;

	class ShapeStageCanvas : public GLCanvas
	{
	public:
		ShapeStageCanvas(EditPanel* editPanel, MultiShapesImpl* shapesImpl, 
			const f2Colorf& color = f2Colorf(0.0f, 0.0f, 0.0f));

	protected:
		virtual void onDraw();

	protected:
		f2Colorf m_color;

		MultiShapesImpl* m_shapesImpl;

	}; // ShapeStageCanvas
}

#endif // _WX_GUI_SHAPE_STAGE_CANVAS_H_