#include "SettingViewDlg.h"

#include <wx/spinctrl.h>

using namespace deditor;

SettingViewDlg::SettingViewDlg(wxWindow* parent, wxgui::GLCanvas* canvas)
	: wxDialog(parent, wxID_ANY, wxT("显示设置"))
	, m_canvas(canvas)
	, m_ctlPointSize(NULL)
{
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->AddSpacer(20);
	sizer->Add(initDisplayTypePanel(), 0, wxCENTRE/* | wxALL, 20*/);
	sizer->AddSpacer(20);
	sizer->Add(initStylePanel(), 0, wxCENTRE/* | wxALL, 20*/);
	SetSizer(sizer);

	sizer->Layout();
	Refresh();
}

wxSizer* SettingViewDlg::initDisplayTypePanel()
{
	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	wxArrayString choices;
	choices.Add(wxT("物理+图片"));
	choices.Add(wxT("物理"));
	choices.Add(wxT("图片"));

	wxRadioBox* drawChoice = new wxRadioBox(this, wxID_ANY, wxT("显示方式"), 
		wxDefaultPosition, wxDefaultSize, choices, 1, wxRA_SPECIFY_COLS);
	Connect(drawChoice->GetId(), wxEVT_COMMAND_RADIOBOX_SELECTED, 
		wxCommandEventHandler(SettingViewDlg::onChangeDisplayType));
	drawChoice->SetSelection(wxgui::Settings::drawType);

	sizer->Add(drawChoice);

	return sizer;
}

wxSizer* SettingViewDlg::initStylePanel()
{
	wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("显示样式"));
	wxBoxSizer* topSizer = new wxStaticBoxSizer(bounding, wxVERTICAL);
	{
		wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("折线"));
		wxBoxSizer* lineSizer = new wxStaticBoxSizer(bounding, wxVERTICAL);
		{
			wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
			sizer->Add(new wxStaticText(this, wxID_ANY, wxT("节点大小：")));

			m_ctlPointSize = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize(50, -1), 
				wxSP_ARROW_KEYS, 0, 30, wxgui::Settings::ctlPosSize);
			Connect(m_ctlPointSize->GetId(), wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler(SettingViewDlg::onChangeStyle));
			sizer->Add(m_ctlPointSize);

			lineSizer->Add(sizer);
		}
		topSizer->Add(lineSizer);
	}
	topSizer->AddSpacer(10);
	{
		wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("多边形"));
		wxBoxSizer* sizer = new wxStaticBoxSizer(bounding, wxVERTICAL);
		{
			wxCheckBox* trisCheck = new wxCheckBox(this, wxID_ANY, wxT("三角剖分线"));
			trisCheck->SetValue(wxgui::Settings::bDisplayTrisEdge);
			Connect(trisCheck->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(SettingViewDlg::onChangeDisplayTriangles));
			sizer->Add(trisCheck);
		}
		topSizer->AddSpacer(5);
		{
			wxCheckBox* boundCheck = new wxCheckBox(this, wxID_ANY, wxT("边界"));
			boundCheck->SetValue(wxgui::Settings::bDisplayPolyBound);
			Connect(boundCheck->GetId(), wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler(SettingViewDlg::onChangeDisplayPolygonBound));
			sizer->Add(boundCheck);
		}
		topSizer->Add(sizer);
	}
	return topSizer;
}

void SettingViewDlg::onChangeDisplayType(wxCommandEvent& event)
{
	wxgui::Settings::drawType = static_cast<wxgui::Settings::DrawType>(event.GetSelection());

	if (m_canvas) 
		m_canvas->Refresh();
}

void SettingViewDlg::onChangeStyle(wxSpinEvent& event)
{
	wxgui::Settings::ctlPosSize = m_ctlPointSize->GetValue();
	if (m_canvas) m_canvas->Refresh();
}

void SettingViewDlg::onChangeDisplayTriangles(wxCommandEvent& event)
{
	wxgui::Settings::bDisplayTrisEdge = event.IsChecked();
	if (m_canvas) m_canvas->Refresh();
}

void SettingViewDlg::onChangeDisplayPolygonBound(wxCommandEvent& event)
{
	wxgui::Settings::bDisplayPolyBound = event.IsChecked();
	if (m_canvas) m_canvas->Refresh();
}