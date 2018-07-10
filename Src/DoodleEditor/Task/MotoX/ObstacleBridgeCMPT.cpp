#include "ObstacleBridgeCMPT.h"
#include "ObstacleBridgeOP.h"
#include "StagePanel.h"

using namespace deditor::motox;

ObstacleBridgeCMPT::ObstacleBridgeCMPT(wxWindow* parent, const wxString& name, StagePanel* editPanel)
	: AbstractEditCMPT(parent, name, editPanel)
{
	m_editOP = new ObstacleBridgeOP(editPanel, this);
}

wxSizer* ObstacleBridgeCMPT::initLayout()
{
	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	{
		wxButton* btn = new wxButton(this, wxID_ANY, wxT("¼ÓÔØtile..."));
		Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(ObstacleBridgeCMPT::onLoadTileSymbol));
		sizer->Add(btn);
	}
	sizer->AddSpacer(10);
	{
		sizer->Add(new wxStaticText(this, wxID_ANY, wxT("tileÎÄ¼þ£º")));
		sizer->Add(m_currFilenameCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY));
	}
	return sizer;
}

void ObstacleBridgeCMPT::onLoadTileSymbol(wxCommandEvent& event)
{
	wxString formatFilter = wxT("*.png;*.jpg");
	wxFileDialog dlg(this, wxT("Please choose a image"), wxEmptyString, 
		wxEmptyString, formatFilter, wxFD_OPEN);
	if (dlg.ShowModal() == wxID_OK)
	{
		m_tile = static_cast<wxgui::ImageSymbol*>(wxgui::SymbolMgr::Instance()->getSymbol(dlg.GetPath()));
		m_currFilenameCtrl->ChangeValue(wxgui::FilenameTools::getFilename(dlg.GetPath()));
	}
}