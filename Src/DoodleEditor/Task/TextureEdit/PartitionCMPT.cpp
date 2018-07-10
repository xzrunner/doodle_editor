#include "PartitionCMPT.h"
#include "StagePanel.h"
#include "PartitionImage.h"

#include <wx/spinctrl.h>

using namespace deditor::texture_edit;

PartitionCMPT::PartitionCMPT(wxWindow* parent, const wxString& name,
							 StagePanel* editPanel)
	: wxgui::AbstractEditCMPT(parent, name, editPanel)
{
	m_editOP = new wxgui::ZoomViewOP(editPanel, true);
}

wxSizer* PartitionCMPT::initLayout()
{
	wxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	{
		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		sizer->Add(new wxStaticText(this, wxID_ANY, wxT("行数：")));

		m_rowNum = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), 
			wxSP_ARROW_KEYS, 1, 30, 1);
		sizer->Add(m_rowNum);

		topSizer->Add(sizer);
	}
	topSizer->AddSpacer(5);
	{
		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		sizer->Add(new wxStaticText(this, wxID_ANY, wxT("列数：")));

		m_colNum = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), 
			wxSP_ARROW_KEYS, 1, 30, 1);
		sizer->Add(m_colNum);

		topSizer->Add(sizer);
	}
	topSizer->AddSpacer(30);
	{
		wxButton* btnOK = new wxButton(this, wxID_ANY, wxT("划分"));
		Connect(btnOK->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(PartitionCMPT::onPartitionImage));
		topSizer->Add(btnOK);
	}
	return topSizer;
}

void PartitionCMPT::onPartitionImage(wxCommandEvent& event)
{
	wxgui::Image* image = static_cast<StagePanel*>(m_editPanel)->getTexture();
	PartitionImage::partition(image->filepath(), 
		m_rowNum->GetValue(), m_colNum->GetValue());
}