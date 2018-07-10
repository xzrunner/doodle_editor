#include "AEPackageDlg.h"
#include "Frame/defs.h"

#include <wxGUI/wxGUI.h>

using namespace deditor::motox;

AEPackageDlg::AEPackageDlg(wxWindow* parent, const LibraryActorItem& params)
 	: wxDialog(parent, wxID_ANY, "���"), m_packImpl(params)
{
	initLayout();
}

void AEPackageDlg::initLayout()
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	wxButton* btnLoadText = new wxButton(this, wxID_ANY, wxT("�����ͼ�ļ�..."));
	Connect(btnLoadText->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
		wxCommandEventHandler(AEPackageDlg::onLoadFromAutomaticFile));
	sizer->Add(btnLoadText);

	wxButton* btnStoreBin = new wxButton(this, wxID_ANY, wxT("��������ļ�..."));
	Connect(btnStoreBin->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
		wxCommandEventHandler(AEPackageDlg::onStoreToBinFile));
	sizer->Add(btnStoreBin);

	SetSizer(sizer);
}

void AEPackageDlg::onLoadFromAutomaticFile(wxCommandEvent& event)
{
	wxString filter = "*_" + AUTOMATIC_MERGE_TASK_TAG + ".txt";
	wxFileDialog dlg(this, wxT("ѡ���ͼ�ļ�"), wxEmptyString, wxEmptyString, filter, wxFD_OPEN);
	if (dlg.ShowModal() == wxID_OK)
	{
		m_packImpl.loadFromTextFile(dlg.GetPath());
	}
}

void AEPackageDlg::onStoreToBinFile(wxCommandEvent& event)
{
	wxString filter = wxT("*.bin");
	wxFileDialog dlg(this, wxT("ѡ������ļ�"), wxEmptyString, wxEmptyString, filter, wxFD_SAVE);
	if (dlg.ShowModal() == wxID_OK)
	{
		wxString fixed = wxgui::FilenameTools::getFilenameAddTag(dlg.GetPath(), "", "bin");
		m_packImpl.storeToBinaryFile(fixed);
	}
}
