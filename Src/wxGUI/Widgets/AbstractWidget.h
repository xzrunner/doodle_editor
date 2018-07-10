#ifndef _WX_GUI_ABSTRACT_WIDGET_H_
#define _WX_GUI_ABSTRACT_WIDGET_H_

#include <wx/wx.h>

namespace wxgui
{
	class AbstractWidget : public wxPanel
	{
	public:
		AbstractWidget(wxWindow* parent) : wxPanel(parent) {}
		virtual ~AbstractWidget() {}

	}; // AbstractWidget
}

#endif // _WX_GUI_ABSTRACT_WIDGET_H_