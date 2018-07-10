#include "ObstacleSoftCMPT.h"
#include "ObstacleSoftOP.h"
#include "StagePanel.h"

#include <wx/spinctrl.h>

using namespace deditor::motox;

ObstacleSoftCMPT::ObstacleSoftCMPT(wxWindow* parent, const wxString& name, StagePanel* editPanel,
								   wxgui::LibraryPanel* libraryPanel)
	: AbstractEditCMPT(parent, name, editPanel)
{
	m_editOP = new ObstacleSoftOP(editPanel, libraryPanel, this);
}

void ObstacleSoftCMPT::getSettings(SoftSettings& settings) const
{
	settings.shape = static_cast<SoftSettings::Type>(m_shapeChoice->GetSelection());
	settings.edge = m_edgeCtrl->GetValue();
	settings.frequencyHz = m_frequencyHzCtrl->GetValue() * 0.1f;
	settings.dampingRatio = m_dampingRatioCtrl->GetValue() * 0.1f;
}

wxSizer* ObstacleSoftCMPT::initLayout()
{
	wxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	{
		wxArrayString choices;
		choices.Add(wxT("矩形"));
		choices.Add(wxT("圆形"));
	
		m_shapeChoice = new wxRadioBox(this, wxID_ANY, wxT("形状"), wxDefaultPosition, wxDefaultSize, choices, 1, wxRA_SPECIFY_COLS);
		topSizer->Add(m_shapeChoice);
	}
	topSizer->AddSpacer(20);
	{
		wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("参数设置"));
		wxBoxSizer* settingSizer = new wxStaticBoxSizer(bounding, wxVERTICAL);
		{
			wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
			sizer->Add(new wxStaticText(this, wxID_ANY, wxT("边长: ")));
			sizer->Add(m_edgeCtrl = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS | wxALIGN_RIGHT, 10, 100, 20));
			settingSizer->Add(sizer);
		}
		settingSizer->AddSpacer(10);
		{
			wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
			sizer->Add(new wxStaticText(this, wxID_ANY, wxT("Hz: ")));
			sizer->Add(m_frequencyHzCtrl = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS | wxALIGN_RIGHT, 0, 500, 200));
			settingSizer->Add(sizer);
		}
		settingSizer->AddSpacer(5);
		{
			wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
			sizer->Add(new wxStaticText(this, wxID_ANY, wxT("Damping: ")));
			sizer->Add(m_dampingRatioCtrl = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS | wxALIGN_RIGHT, 0, 10, 5));
			settingSizer->Add(sizer);
		}
		topSizer->Add(settingSizer);
	}
	return topSizer;
}
