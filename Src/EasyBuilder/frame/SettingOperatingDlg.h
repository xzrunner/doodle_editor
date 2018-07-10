#ifndef _EASY_BUILDER_SETTING_OPERATING_DLG_H_
#define _EASY_BUILDER_SETTING_OPERATING_DLG_H_

#include <wx/wx.h>

namespace ebuilder
{	
	class SettingOperatingDlg : public wxDialog
	{
	public:
		SettingOperatingDlg(wxWindow* parent);
		
	private:
		void onChangeZoomType(wxCommandEvent& event);

	}; // SettingOperatingDlg
}

#endif // _EASY_BUILDER_SETTING_OPERATING_DLG_H_