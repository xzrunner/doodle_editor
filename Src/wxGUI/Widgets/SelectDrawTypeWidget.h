#ifndef _WX_GUI_SELECT_DRAW_TYPE_WIDGET_H_
#define _WX_GUI_SELECT_DRAW_TYPE_WIDGET_H_

#include "AbstractWidget.h"

namespace wxgui
{
	class GLCanvas;

	class SelectDrawTypeWidget : public AbstractWidget
	{
	public:
		SelectDrawTypeWidget(wxWindow* parent, GLCanvas* canvas);

	private:
		void onSetDrawType(wxCommandEvent& event);

	private:
		GLCanvas* m_canvas;

	}; // SelectDrawTypeWidget
}

#endif // _WX_GUI_SELECT_DRAW_TYPE_WIDGET_H_