#include "TileIOCMPT.h"
#include "StagePanel.h"
#include "TileFileAdapter.h"

#include "Frame/defs.h"

using namespace deditor::hill_climb;

TileIOCMPT::TileIOCMPT(wxWindow* parent, const wxString& name, 
					   StagePanel* editPanel, wxgui::LibraryPanel* libraryPanel)
	: AbstractEditCMPT(parent, name, editPanel)
	, m_libraryPanel(libraryPanel)
{
	m_editOP = new wxgui::ZoomViewOP(editPanel, true);
}

wxSizer* TileIOCMPT::initLayout()
{
	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	{
		wxButton* btn = new wxButton(this, wxID_ANY, wxT("导入txt..."));
		Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(TileIOCMPT::onLoadText));
		sizer->Add(btn);
	}
	sizer->AddSpacer(5);
	{
		wxButton* btn = new wxButton(this, wxID_ANY, wxT("导出txt..."));
		Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(TileIOCMPT::onStoreText));
		sizer->Add(btn);
	}
	return sizer;
}

void TileIOCMPT::onLoadText(wxCommandEvent& event)
{
	wxString filter = wxT("*_") + HILL_CLIMB_TASK_TAG + wxT(".txt");
	wxFileDialog dlg(this, wxT("导入tile文件"), wxEmptyString, wxEmptyString, filter, wxFD_OPEN);
	if (dlg.ShowModal() == wxID_OK)
	{
		loadFromTextFile(dlg.GetPath());
	}
}

void TileIOCMPT::onStoreText(wxCommandEvent& event)
{
	wxString filter = wxT("*_") + HILL_CLIMB_TASK_TAG + wxT(".txt");
	wxFileDialog dlg(this, wxT("导出tile文件"), wxEmptyString, wxEmptyString, filter, wxFD_SAVE);
	if (dlg.ShowModal() == wxID_OK)
	{
		wxString fixed = wxgui::FilenameTools::getFilenameAddTag(dlg.GetPath(), HILL_CLIMB_TASK_TAG, "txt");
		storeToTextFile(fixed);
	}
}

void TileIOCMPT::loadFromTextFile(const wxString& filepath)
{
 	wxgui::SymbolMgr::Instance()->clear();
 	wxgui::BitmapMgr::Instance()->clear();

	StagePanel* editPanel = static_cast<StagePanel*>(m_editPanel);

	TileFileAdapter adapter;
	adapter.resolve(filepath);
	for (size_t i = 0, n = adapter.m_sprites.size(); i < n; ++i)
		editPanel->insertSprite(adapter.m_sprites[i]);

	m_libraryPanel->loadFromSymbolMgr(*wxgui::SymbolMgr::Instance());
}

void TileIOCMPT::storeToTextFile(const wxString& filepath) const
{
	std::vector<wxgui::ISprite*> sprites;
	static_cast<StagePanel*>(m_editPanel)->traverseSprites(FetchAllVisitor<wxgui::ISprite>(sprites));

	std::ofstream fout(filepath.fn_str());
	fout << sprites.size() << '\n';
	for (size_t i = 0, n = sprites.size(); i < n; ++i)
	{
		wxgui::ISprite* sprite = sprites[i];
		fout << sprite->getSymbol().getFilepath() << '\n';
		fout << sprite->getPosition() << '\n';
	}
	fout.close();
}