#include "BatchSettingDialog.h"
#include "CompressPicture.h"

#include <wx/spinctrl.h>

using namespace deditor::compress_pictures;

BatchSettingDialog::BatchSettingDialog(wxWindow* parent)
	: wxDialog(parent, wxID_ANY, "批量输出参数")
{
	initLayout();
}

void BatchSettingDialog::getCompressParams(CompressParams& params) const
{
	params.m_jpgQuality = m_jpgSpin->GetValue();
	params.m_pngColors = wxVariant(m_pngColorChoice->GetString(m_pngColorChoice->GetSelection())).GetInteger();
	params.m_pngSpeed = wxVariant(m_pngSpeedChoice->GetString(m_pngSpeedChoice->GetSelection())).GetInteger();
}

wxString BatchSettingDialog::getOutputExt() const
{
	return m_extCtrl->GetLineText(0);
}

void BatchSettingDialog::initLayout()
{
	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);	
	initJpgPanel(topSizer);
	topSizer->AddSpacer(20);
	initPngPanel(topSizer);
	topSizer->AddSpacer(20);

	wxBoxSizer* extSizer = new wxBoxSizer(wxHORIZONTAL);
	extSizer->Add(new wxStaticText(this, wxID_ANY, wxT("输出后缀：")));
	extSizer->Add(m_extCtrl = new wxTextCtrl(this, wxID_ANY, wxT("_compressed")));
	topSizer->Add(extSizer);

	wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
	btnSizer->Add(new wxButton(this, wxID_OK), wxALL, 5);
	btnSizer->Add(new wxButton(this, wxID_CANCEL), wxALL, 5);
	topSizer->Add(btnSizer, 0, wxALL, 5);

	SetSizer(topSizer);
	topSizer->Fit(this);
}

void BatchSettingDialog::initJpgPanel(wxSizer* topSizer)
{
	wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("Jpeg"));
	wxBoxSizer* sizer = new wxStaticBoxSizer(bounding, wxHORIZONTAL);
	sizer->Add(new wxStaticText(this, wxID_ANY, wxT("质量：")));
	sizer->Add(m_jpgSpin = new wxSpinCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS | wxALIGN_RIGHT, 0, 100, 80));
	topSizer->Add(sizer);
}

void BatchSettingDialog::initPngPanel(wxSizer* topSizer)
{
	wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("Png"));
	wxBoxSizer* sizer = new wxStaticBoxSizer(bounding, wxHORIZONTAL);
	
	wxString colorChoices[8];
	for (size_t i = 0; i < 8; ++i)
		colorChoices[i] = wxString::FromDouble(pow(2.0f, float(i + 1)));
	wxSizer* colorSizer = new wxBoxSizer(wxHORIZONTAL);
	colorSizer->Add(new wxStaticText(this, wxID_ANY, wxT("颜色数：")));
	m_pngColorChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 8, colorChoices);
	m_pngColorChoice->SetSelection(7);
	colorSizer->Add(m_pngColorChoice);
	sizer->Add(colorSizer);

	sizer->AddSpacer(10);

	wxString speedChoices[10];
	for (size_t i = 0; i < 10; ++i)
		speedChoices[i] = wxString::FromDouble((int) (i + 1));
	wxSizer* speedSizer = new wxBoxSizer(wxHORIZONTAL);
	speedSizer->Add(new wxStaticText(this, wxID_ANY, wxT("速度：")));
	m_pngSpeedChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 10, speedChoices);
	m_pngSpeedChoice->SetSelection(0);
	speedSizer->Add(m_pngSpeedChoice);
	sizer->Add(speedSizer);

	topSizer->Add(sizer);
}