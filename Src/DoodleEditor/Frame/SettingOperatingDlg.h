#ifndef _DEDITOR_SETTING_OPERATING_DLG_H_
#define _DEDITOR_SETTING_OPERATING_DLG_H_

#include <wx/wx.h>

namespace deditor
{
	class SettingOperatingDlg : public wxDialog
	{
	public:
		SettingOperatingDlg(wxWindow* parent);

	private:
		void onChangeZoomType(wxCommandEvent& event);

	}; // SettingOperatingDlg
}

#endif // _DEDITOR_SETTING_OPERATING_DLG_H_