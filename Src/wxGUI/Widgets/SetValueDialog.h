#ifndef _WX_GUI_SET_VALUE_DIALOG_H_
#define _WX_GUI_SET_VALUE_DIALOG_H_
#include <wx/wx.h>

namespace wxgui
{
	class SetValueDialog : public wxDialog
	{
	public:
		SetValueDialog(wxWindow* parent, const wxString& title, const wxString& oldVal, const wxPoint& pos);

		wxString getText() const;

	private:
		void initLayout(const wxString& oldVal);

	private:
		wxTextCtrl* m_textCtrl;

	}; // SetValueDialog
}

#endif // _WX_GUI_SET_VALUE_DIALOG_H_