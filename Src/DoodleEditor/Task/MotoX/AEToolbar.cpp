#include "AEToolbar.h"
#include "AEPartsCMPT.h"
#include "AEJointsCMPT.h"
#include "AEParamsCMPT.h"
#include "AEEditPanel.h"
#include "AEPackageDlg.h"
#include "AETypes.h"

using namespace deditor::motox;

AEToolbar::AEToolbar(wxWindow* parent, AEEditPanel* editPanel,
					 wxgui::LibraryPanel* libraryPanel,
					 wxgui::PropertySettingPanel* propertyPanel)
	: wxgui::ToolbarPanel(parent, editPanel)
	, m_libraryPanel(libraryPanel)
{
	addChild(new AEPartsCMPT(this, wxT("部件导入"), editPanel, propertyPanel));
	addChild(new AEJointsCMPT(this, wxT("关节创建"), editPanel));
	addChild(new AEParamsCMPT(this, wxT("调参数"), editPanel));

	SetSizer(initLayout());	
}

wxSizer* AEToolbar::initLayout()
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	sizer->Add(initIOPanel());
	sizer->AddSpacer(20);
	sizer->Add(new wxgui::SelectDrawTypeWidget(this, m_editPanel->getCanvas()));
	sizer->AddSpacer(20);
	sizer->Add(initChildrenLayout());

	return sizer;
}

wxSizer* AEToolbar::initIOPanel()
{
	wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("IO"));
	wxBoxSizer* sizer = new wxStaticBoxSizer(bounding, wxVERTICAL);

	wxButton* btnOpen = new wxButton(this, wxID_ANY, wxT("导入..."));
	Connect(btnOpen->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
		wxCommandEventHandler(AEToolbar::onOpen));
	sizer->Add(btnOpen);

	wxButton* btnSave = new wxButton(this, wxID_ANY, wxT("导出..."));
	Connect(btnSave->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
		wxCommandEventHandler(AEToolbar::onSave));
	sizer->Add(btnSave);

	sizer->AddSpacer(10);

	wxButton* btnSaveBin = new wxButton(this, wxID_ANY, wxT("打包..."));
	Connect(btnSaveBin->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
		wxCommandEventHandler(AEToolbar::onBinaryPackage));
	sizer->Add(btnSaveBin);

	return sizer;
}

void AEToolbar::onOpen(wxCommandEvent& event)
{
	wxFileDialog dlg(this, wxT("打开Actor"), wxEmptyString, wxEmptyString, 
		wxT("*_") + ACTOR_FILE_TAG + wxT(".txt"), wxFD_OPEN);
	if (dlg.ShowModal() == wxID_OK)
	{
// 		wxgui::SymbolMgr::Instance()->clear();
// 		wxgui::BitmapMgr::Instance()->clear();
		m_libraryPanel->clear();
		m_editPanel->clear();

		std::ifstream fin(dlg.GetPath().fn_str());
		static_cast<AEEditPanel*>(m_editPanel)->loadDataFromFile(fin);
		fin.close();

		static_cast<AEEditPanel*>(m_editPanel)->getJoints().createAllJoints();

		m_libraryPanel->loadFromSymbolMgr(*wxgui::SymbolMgr::Instance());
	}
}

void AEToolbar::onSave(wxCommandEvent& event)
{
	wxFileDialog dlg(this, wxT("保存Actor"), wxEmptyString, wxEmptyString, 
		wxT("*_") + ACTOR_FILE_TAG + wxT(".txt"), wxFD_SAVE);
	if (dlg.ShowModal() == wxID_OK)
	{
		wxString fixed = wxgui::FilenameTools::getFilenameAddTag(dlg.GetPath(), ACTOR_FILE_TAG, "txt");
		std::ofstream fout(fixed.fn_str());
		static_cast<AEEditPanel*>(m_editPanel)->storeDataToFile(fout);
		fout.close();
	}
}

void AEToolbar::onBinaryPackage(wxCommandEvent& event)
{
	AEPackageDlg dlg(this, static_cast<AEEditPanel*>(m_editPanel)->getActorItem());
	dlg.ShowModal();
}