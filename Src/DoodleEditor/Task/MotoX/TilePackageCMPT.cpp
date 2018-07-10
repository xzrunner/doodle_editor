#include "TilePackageCMPT.h"
#include "PackageFileIOUtils.h"
#include "StagePanel.h"
#include "TileFileAdapter.h"
#include "TileIOCMPT.h"

#include "Frame/defs.h"

using namespace deditor::motox;

TilePackageCMPT::TilePackageCMPT(wxWindow* parent, const wxString& name, 
								 StagePanel* editPanel)
	: AbstractEditCMPT(parent, name, editPanel)
	, m_editPanel(editPanel)
{
	m_editOP = new wxgui::ZoomViewOP(editPanel, true);
}

void TilePackageCMPT::packageToBin(StagePanel* editPanel, const wxString& src, 
								   const wxString& mergeFile, const wxString& dst)
{
	TileIOCMPT::loadToEditpanel(editPanel, src);

	automatic_merge::FileAdapter merged;
	merged.resolve(mergeFile);

	PackageFileIOUtils fileIO(editPanel, merged, 200);

	//// single layer
	//std::vector<wxgui::ISprite*> sprites;
	//editPanel->traverseSprites(FetchTilesVisitor(sprites));
	//fileIO.storeToFileSingleLayer(dst, sprites);

	// multi layers
	std::vector<wxgui::Layer*> layers;
	editPanel->getLayersMgr()->getAllLayers(layers);
	fileIO.storeToFileMultiLayers(dst, layers);

	editPanel->clear();
}

wxSizer* TilePackageCMPT::initLayout()
{
	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	{
		wxButton* btn = new wxButton(this, wxID_ANY, wxT("导出bin..."));
		Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(TilePackageCMPT::onStoreToBinFile));
		sizer->Add(btn);
	}
	sizer->AddSpacer(5);
	{
		wxButton* btn = new wxButton(this, wxID_ANY, wxT("导入bin..."));
		Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(TilePackageCMPT::onLoadFromBinFile));
		sizer->Add(btn);
	}
	sizer->AddSpacer(10);
	{
		wxButton* btn = new wxButton(this, wxID_ANY, wxT("导入合图文件..."));
		Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(TilePackageCMPT::onLoadMergedFile));
		sizer->Add(btn);
	}
	return sizer;
}

void TilePackageCMPT::onStoreToBinFile(wxCommandEvent& event)
{
	wxString filter = wxT("*_") + MOTOX_TASK_TAG + wxT(".bin");
	wxFileDialog dlg(this, wxT("导出tile二进制文件"), wxEmptyString, wxEmptyString, filter, wxFD_SAVE);
	if (dlg.ShowModal() == wxID_OK)
	{
		wxString fixed = wxgui::FilenameTools::getFilenameAddTag(dlg.GetPath(), MOTOX_TASK_TAG, "bin");

		PackageFileIOUtils fileIO(m_editPanel, m_merged, 200);

// 		// single layer
// 		std::vector<wxgui::ISprite*> sprites;
// 		m_editPanel->traverseSprites(FetchAllVisitor<wxgui::ISprite>(sprites));
// 		fileIO.storeToFileSingleLayer(fixed, sprites);

		// multi layers
		std::vector<wxgui::Layer*> layers;
		m_editPanel->getLayersMgr()->getAllLayers(layers);
		fileIO.storeToFileMultiLayers(fixed, layers);
	}
}

void TilePackageCMPT::onLoadFromBinFile(wxCommandEvent& event)
{
	wxString filter = wxT("*_") + MOTOX_TASK_TAG + wxT(".bin");
	wxFileDialog dlg(this, wxT("导入tile二进制文件"), wxEmptyString, wxEmptyString, filter, wxFD_OPEN);
	if (dlg.ShowModal() == wxID_OK)
	{
		PackageFileIOUtils fileIO(m_editPanel, m_merged, 200);
		fileIO.loadFromFileMultiLayers(dlg.GetPath());
		m_editPanel->Refresh();
	}
}

void TilePackageCMPT::onLoadMergedFile(wxCommandEvent& event)
{
	wxString filter = "*_" + AUTOMATIC_MERGE_TASK_TAG + ".txt";
	wxFileDialog dlg(this, wxT("选择合图文件"), wxEmptyString, wxEmptyString, filter, wxFD_OPEN);
	if (dlg.ShowModal() == wxID_OK)
	{
		m_merged.resolve(dlg.GetPath());
	}
}