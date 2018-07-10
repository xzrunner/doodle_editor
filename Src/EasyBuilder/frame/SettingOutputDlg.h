#ifndef _EASY_BUILDER_SETTING_OUTPUT_DLG_H_
#define _EASY_BUILDER_SETTING_OUTPUT_DLG_H_

#include "Settings.h"

#include <wx/wx.h>

namespace ebuilder
{
	class SettingOutputDlg : public wxDialog
	{
	public:
		SettingOutputDlg(wxWindow* parent);

		Settings::CodeType getType() const;

	private:
		wxRadioBox* m_typeChoice;

	}; // SettingOutputDlg
}

#endif // _EASY_BUILDER_SETTING_OUTPUT_DLG_H_