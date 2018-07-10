#include "SettingOperatingDlg.h"

#include <wxGUI/wxGUI.h>

using namespace deditor;

SettingOperatingDlg::SettingOperatingDlg(wxWindow* parent)
	: wxDialog(parent, wxID_ANY, wxT("��������"))
{
	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	{
		wxArrayString choices;
		choices.Add(wxT("���"));
		choices.Add(wxT("��� + ����"));

		wxRadioBox* editChoice = new wxRadioBox(this, wxID_ANY, wxT("���ŷ�ʽ"), wxDefaultPosition, wxDefaultSize, choices, 1, wxRA_SPECIFY_COLS);
		if (wxgui::Settings::bZoomOnlyUseMouseWheel)
			editChoice->SetSelection(0);
		else
			editChoice->SetSelection(1);
		Connect(editChoice->GetId(), wxEVT_COMMAND_RADIOBOX_SELECTED, wxCommandEventHandler(SettingOperatingDlg::onChangeZoomType));
		sizer->Add(editChoice, 0, wxCENTRE | wxALL, 20);
	}
	SetSizer(sizer);
}

void SettingOperatingDlg::onChangeZoomType(wxCommandEvent& event)
{
	if (event.GetInt() == 0)
		wxgui::Settings::bZoomOnlyUseMouseWheel = true;
	else
		wxgui::Settings::bZoomOnlyUseMouseWheel = false;
}