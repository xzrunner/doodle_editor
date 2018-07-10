#include "ToolbarPanel.h"
#include "StagePanel.h"

using namespace deditor::manual_compose;

ToolbarPanel::ToolbarPanel(wxWindow* parent, wxgui::EditPanel* editPanel)
	: wxgui::ToolbarPanel(parent, editPanel)
{
	SetSizer(initLayout());	
}

wxSizer* ToolbarPanel::initLayout()
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	wxButton* btnSetBg = new wxButton(this, wxID_ANY, wxT("±≥æ∞..."));
	Connect(btnSetBg->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
		wxCommandEventHandler(ToolbarPanel::onChooseBackground));
	sizer->Add(btnSetBg, 0);

	return sizer;
}

void ToolbarPanel::onChooseBackground(wxCommandEvent& event)
{
 	wxFileDialog dlg(this, wxT("—°‘Ò“ª’≈Õº∆¨"), wxEmptyString, wxEmptyString, wxT("*.png;*.jpg;*.bmp"), wxFD_OPEN);
 	if (dlg.ShowModal() == wxID_OK)
 	{
		static_cast<StagePanel*>(m_editPanel)->setBackground(dlg.GetPath());
 	}
}