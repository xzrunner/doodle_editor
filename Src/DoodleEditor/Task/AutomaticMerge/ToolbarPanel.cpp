#include "ToolbarPanel.h"
#include "StagePanel.h"
#include "PackageFileIO.h"

#include "Frame/defs.h"

using namespace deditor::automatic_merge;

ToolbarPanel::ToolbarPanel(wxWindow* parent, StagePanel* stagePanel)
	: wxgui::ToolbarPanel(parent, stagePanel)
{
	SetSizer(initLayout());
	onChangeOutputImageSize(wxCommandEvent());
}

ToolbarPanel::IMG_TYPE ToolbarPanel::getImgType() const
{
	switch (m_formatChoice->GetSelection())
	{
	case 0:
		return e_bmp;
	case 1:
		return e_jpg;
	case 2:
		return e_png;
	default:
		assert(0);
	}
}

wxSizer* ToolbarPanel::initLayout()
{
	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	initSizeSettingPanel(sizer);
	sizer->AddSpacer(20);
	initFormatChoicePanel(sizer);
	sizer->AddSpacer(20);
	initRearrangePanel(sizer);
	sizer->AddSpacer(10);
	initLoadListPanel(sizer);
	sizer->AddSpacer(20);
	initPackagePanel(sizer);

	return sizer;
}

void ToolbarPanel::initSizeSettingPanel(wxSizer* topSizer)
{
	wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("输出大小"));
	wxBoxSizer* sizer = new wxStaticBoxSizer(bounding, wxVERTICAL);

	wxString choices[TOTLE_EDGE_TYPES];
	for (size_t i = 0; i < TOTLE_EDGE_TYPES; ++i)
		choices[i] = wxString::FromDouble(BASE_EDGE * pow(2.0f, float(i)));

	wxSizer* widthSizer = new wxBoxSizer(wxHORIZONTAL);
	widthSizer->Add(new wxStaticText(this, wxID_ANY, wxT("宽：")));
	m_widthChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 6, choices);
	m_widthChoice->SetSelection(3);
	Connect(m_widthChoice->GetId(), wxEVT_COMMAND_CHOICE_SELECTED, 
		wxCommandEventHandler(ToolbarPanel::onChangeOutputImageSize));
	widthSizer->Add(m_widthChoice);
	sizer->Add(widthSizer);

	wxSizer* heightSizer = new wxBoxSizer(wxHORIZONTAL);
	heightSizer->Add(new wxStaticText(this, wxID_ANY, wxT("高：")));
	m_heightChoice = new wxChoice(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 6, choices);
	m_heightChoice->SetSelection(3);
	Connect(m_heightChoice->GetId(), wxEVT_COMMAND_CHOICE_SELECTED, 
		wxCommandEventHandler(ToolbarPanel::onChangeOutputImageSize));
	heightSizer->Add(m_heightChoice);
	sizer->Add(heightSizer);

	topSizer->Add(sizer);
}

void ToolbarPanel::initFormatChoicePanel(wxSizer* topSizer)
{
	wxArrayString choices;
	choices.Add(wxT("bmp"));
	choices.Add(wxT("jpg"));
	choices.Add(wxT("png"));
	m_formatChoice = new wxRadioBox(this, wxID_ANY, wxT("输出格式"), 
		wxDefaultPosition, wxDefaultSize, choices, 1, wxRA_SPECIFY_COLS);
	topSizer->Add(m_formatChoice);
}

void ToolbarPanel::initRearrangePanel(wxSizer* topSizer)
{
	wxButton* btn = new wxButton(this, wxID_ANY, wxT("重新排列"));
	Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ToolbarPanel::onRearrange));
	topSizer->Add(btn);
}

void ToolbarPanel::initLoadListPanel(wxSizer* topSizer)
{
	wxButton* btn = new wxButton(this, wxID_ANY, wxT("从列表加载"));
	Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ToolbarPanel::onLoadLibraryList));
	topSizer->Add(btn);
}

void ToolbarPanel::initPackagePanel(wxSizer* topSizer)
{
	wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("打包"));
	wxBoxSizer* sizer = new wxStaticBoxSizer(bounding, wxVERTICAL);
	{
		m_boundCheck = new wxCheckBox(this, wxID_ANY, wxT("输出边界坐标"));
		m_boundCheck->SetValue(true);
		sizer->Add(m_boundCheck);
	}
	sizer->AddSpacer(10);
	{
		wxButton* btn = new wxButton(this, wxID_ANY, wxT("输出..."));
		Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ToolbarPanel::onPackageOutput));
		sizer->Add(btn);
	}
	topSizer->Add(sizer);
}

void ToolbarPanel::onChangeOutputImageSize(wxCommandEvent& event)
{
	int width = wxVariant(m_widthChoice->GetString(m_widthChoice->GetSelection())).GetInteger(),
		height = wxVariant(m_heightChoice->GetString(m_heightChoice->GetSelection())).GetInteger();
	static_cast<StagePanel*>(m_editPanel)->setOutputImageSize(width, height);
	m_editPanel->Refresh();
}

void ToolbarPanel::onRearrange(wxCommandEvent& event)
{
	static_cast<StagePanel*>(m_editPanel)->arrangeAllSprites(true);
	m_editPanel->Refresh();
}

void ToolbarPanel::onLoadLibraryList(wxCommandEvent& event)
{
	static_cast<StagePanel*>(m_editPanel)->loadLibraryList();
	m_editPanel->Refresh();
}

void ToolbarPanel::onPackageOutput(wxCommandEvent& event)
{
	wxString filter = "*_" + AUTOMATIC_MERGE_TASK_TAG + ".bin";
	wxFileDialog dlg(this, wxT("选择输出文件"), wxEmptyString, wxEmptyString, filter, wxFD_SAVE);
	if (dlg.ShowModal() == wxID_OK)
	{
		wxString fixed = wxgui::FilenameTools::getFilenameAddTag(dlg.GetPath(), AUTOMATIC_MERGE_TASK_TAG, "bin");
		PackageFileIO package(static_cast<StagePanel*>(m_editPanel), m_boundCheck->IsChecked());
		package.storeToFile(fixed);
	}
}