#include "ToolbarPanel.h"
#include "BatchSettingDialog.h"
#include "StagePanel.h"
#include "LibrarySymbolList.h"
#include "CompressPicture.h"

#include <wx/filename.h>

using namespace deditor::compress_pictures;

ToolbarPanel::ToolbarPanel(wxWindow* parent, wxgui::EditPanel* editPanel)
	: wxgui::ToolbarPanel(parent, editPanel)
{
	SetSizer(initLayout());	
}

void ToolbarPanel::changeSymbol(const wxgui::ISymbol* symbol)
{
	const wxString& filePath = symbol->getFilepath();

	std::string ext = wxgui::FilenameTools::getExtension(filePath);
	StringTools::toLower(ext);
	if (ext == "jpg")
	{
		m_jpgSizer->Show(true);
		m_pngSizer->Show(false);
		m_paramsSizer->Show(true);
	}
	else if (ext == "png")
	{
		m_jpgSizer->Show(false);
		m_pngSizer->Show(true);
		m_paramsSizer->Show(true);
	}
	else
	{
		m_jpgSizer->Show(false);
		m_pngSizer->Show(false);
		m_paramsSizer->Show(false);
	}
	Layout();
}

void ToolbarPanel::setLibraryList(LibrarySymbolList* libraryList)
{
	m_libraryList = libraryList;
} 

void ToolbarPanel::updateParamsPanel(const wxString& src, const wxString& dst)
{
	wxFileName fileSrc(src), fileDst(dst);

	m_srcSizeText->ChangeValue(fileSrc.GetHumanReadableSize());
	m_dstSizeText->ChangeValue(fileDst.GetHumanReadableSize());

	float ratio = (float) fileDst.GetSize().GetValue() / fileSrc.GetSize().GetValue();
	m_compressRatio->ChangeValue(wxString::FromDouble((int) (ratio * 100)) + wxT("%"));
}

void ToolbarPanel::getCompressParams(CompressParams& params) const
{
	params.m_jpgQuality = m_jpgSlider->GetValue();
	params.m_pngColors = wxVariant(m_pngColorChoice->GetString(m_pngColorChoice->GetSelection())).GetInteger();
	params.m_pngSpeed = wxVariant(m_pngSpeedChoice->GetString(m_pngSpeedChoice->GetSelection())).GetInteger();
}

wxSizer* ToolbarPanel::initLayout()
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	initJpgPanel(sizer);
	initPngPanel(sizer);
	sizer->AddSpacer(20);
	initParamsPanel(sizer);
	sizer->AddSpacer(20);
	initBatchPanel(sizer);
	SetSizer(sizer);

	m_jpgSizer->Show(false);
	m_pngSizer->Show(false);
	m_paramsSizer->Show(false);

	return sizer;
}

void ToolbarPanel::initJpgPanel(wxSizer* topSizer)
{
	wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("设置"));
	wxBoxSizer* sizer = new wxStaticBoxSizer(bounding, wxVERTICAL);

	m_jpgSlider = new wxSlider(this, wxID_ANY, 80, 0, 100, 
		wxDefaultPosition, wxSize(0, 400), wxSL_VERTICAL | wxSL_INVERSE | wxSL_LABELS);
	Connect(m_jpgSlider->GetId(), wxEVT_COMMAND_SLIDER_UPDATED, 
		wxScrollEventHandler(ToolbarPanel::onChangeSettings));
	sizer->Add(m_jpgSlider);

	topSizer->Add(sizer);

	m_jpgSizer = sizer;
}

void ToolbarPanel::initPngPanel(wxSizer* topSizer)
{
	wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("设置"));
	wxBoxSizer* sizer = new wxStaticBoxSizer(bounding, wxVERTICAL);

	wxString colorChoices[8];
	for (size_t i = 0; i < 8; ++i)
		colorChoices[i] = wxString::FromDouble(pow(2.0f, float(i + 1)));
	wxSizer* colorSizer = new wxBoxSizer(wxHORIZONTAL);
	colorSizer->Add(new wxStaticText(this, wxID_ANY, wxT("颜色数：")));
 	m_pngColorChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 8, colorChoices);
 	m_pngColorChoice->SetSelection(7);
 	Connect(m_pngColorChoice->GetId(), wxEVT_COMMAND_CHOICE_SELECTED, 
 		wxCommandEventHandler(ToolbarPanel::onChangeSettings));
 	colorSizer->Add(m_pngColorChoice);
	sizer->Add(colorSizer);

	sizer->AddSpacer(10);

 	wxString speedChoices[10];
 	for (size_t i = 0; i < 10; ++i)
 		speedChoices[i] = wxString::FromDouble((int) (i + 1));
 	wxSizer* speedSizer = new wxBoxSizer(wxHORIZONTAL);
	speedSizer->Add(new wxStaticText(this, wxID_ANY, wxT("速度：")));
 	m_pngSpeedChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 10, speedChoices);
 	m_pngSpeedChoice->SetSelection(2);
 	Connect(m_pngSpeedChoice->GetId(), wxEVT_COMMAND_CHOICE_SELECTED, 
 		wxCommandEventHandler(ToolbarPanel::onChangeSettings));
 	speedSizer->Add(m_pngSpeedChoice);
 	sizer->Add(speedSizer);

	topSizer->Add(sizer);

	m_pngSizer = sizer;
}

void ToolbarPanel::initParamsPanel(wxSizer* topSizer)
{
	wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("参数"));
	wxBoxSizer* sizer = new wxStaticBoxSizer(bounding, wxVERTICAL);

	wxBoxSizer* srcSizer = new wxBoxSizer(wxHORIZONTAL);
	srcSizer->Add(new wxStaticText(this, wxID_ANY, wxT("初始：")));
	srcSizer->Add(m_srcSizeText = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY));
	sizer->Add(srcSizer);

	wxBoxSizer* dstSizer = new wxBoxSizer(wxHORIZONTAL);
	dstSizer->Add(new wxStaticText(this, wxID_ANY, wxT("压缩后：")));
	dstSizer->Add(m_dstSizeText = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY));
	sizer->Add(dstSizer);

	wxBoxSizer* ratioSizer = new wxBoxSizer(wxHORIZONTAL);
	ratioSizer->Add(new wxStaticText(this, wxID_ANY, wxT("压缩比：")));
	ratioSizer->Add(m_compressRatio = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY));
	sizer->Add(ratioSizer);

	topSizer->Add(sizer);

	m_paramsSizer = sizer;
}

void ToolbarPanel::initBatchPanel(wxSizer* topSizer)
{
	wxButton* btn = new wxButton(this, wxID_ANY, wxT("批量输出..."));
	Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
		wxCommandEventHandler(ToolbarPanel::onBatchBtnPress));
	topSizer->Add(btn);
}

void ToolbarPanel::onChangeSettings(wxCommandEvent& event)
{
	static_cast<StagePanel*>(m_editPanel)->compressSymbol();
}

void ToolbarPanel::onChangeSettings(wxScrollEvent& event)
{
	static_cast<StagePanel*>(m_editPanel)->compressSymbol();
}

void ToolbarPanel::onBatchBtnPress(wxCommandEvent& event)
{
	BatchSettingDialog dlg(this);
	if (dlg.ShowModal() == wxID_OK)
	{
		CompressParams params;
		dlg.getCompressParams(params);
		m_libraryList->compressAll(params, dlg.getOutputExt());
	}
}