#ifndef _WX_GUI_LOG_H_
#define _WX_GUI_LOG_H_

#include <wx/wx.h>

namespace wxgui
{
	static void log(int info)
	{
		wxMessageBox(wxString::FromDouble(info));
	}

	static void log(const wxString& info)
	{
		wxMessageBox(info);
	}
}

#endif // _WX_GUI_LOG_H_