#include "TEToolbar.h"
#include "TEEditPanel.h"
#include "TEFileAdapter.h"
#include "TETypes.h"

#include <wx/spinctrl.h>

using namespace deditor::motox;

TEToolbar::TEToolbar(wxWindow* parent, TEEditPanel* editPanel, 
					 wxgui::LibraryPanel* libraryPanel,
					 wxgui::PropertySettingPanel* propertyPanel)
	: wxgui::ToolbarPanel(parent, editPanel)
	, m_editPanel(editPanel)
	, m_libraryPanel(libraryPanel)
{
	addChild(new PasteTileCMPT(this, wxT("粘贴"), editPanel, m_libraryPanel));
	addChild(new wxgui::UniversalCMPT(this, wxT("调整"), editPanel, 
		new wxgui::ArrangeSpriteOP<wxgui::SelectSpritesOP>(editPanel, editPanel, propertyPanel)));

	SetSizer(initLayout());
}

wxSizer* TEToolbar::initLayout()
{
	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->AddSpacer(5);
	{
		wxButton* btn = new wxButton(this, wxID_ANY, wxT("导入..."));
		Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(TEToolbar::onLoadText));
		sizer->Add(btn);
	}
	sizer->AddSpacer(5);
	{
		wxButton* btn = new wxButton(this, wxID_ANY, wxT("导出..."));
		Connect(btn->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
			wxCommandEventHandler(TEToolbar::onStoreText));
		sizer->Add(btn);
	}
	sizer->AddSpacer(10);
	{
		sizer->Add(new wxStaticText(this, wxID_ANY, wxT("当前文件：")));
		sizer->Add(m_currFilenameCtrl = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY));
	}
	sizer->AddSpacer(15);
	sizer->Add(initChildrenLayout());
	return sizer;
}

void TEToolbar::onLoadText(wxCommandEvent& event)
{
	wxString filter = wxT("*_") + TEMPLATE_FILE_TAG + wxT(".txt");
	wxFileDialog dlg(this, wxT("导入模板文件"), wxEmptyString, wxEmptyString, filter, wxFD_OPEN);
	if (dlg.ShowModal() == wxID_OK)
	{
		loadFromTextFile(dlg.GetPath());
		m_currFilenameCtrl->ChangeValue(wxgui::FilenameTools::getFilename(dlg.GetPath()));
	}
}

void TEToolbar::onStoreText(wxCommandEvent& event)
{
	wxString filter = wxT("*_") + TEMPLATE_FILE_TAG + wxT(".txt");
	wxFileDialog dlg(this, wxT("导出模板文件"), wxEmptyString, wxEmptyString, filter, wxFD_SAVE);
	if (dlg.ShowModal() == wxID_OK)
	{
		wxString fixed = wxgui::FilenameTools::getFilenameAddTag(dlg.GetPath(), TEMPLATE_FILE_TAG, "txt");
		storeToTextFile(fixed);

		wxString filename = wxgui::FilenameTools::getFilename(fixed);
		m_editPanel->setItemName(filename);
		m_currFilenameCtrl->ChangeValue(filename);
	}
}

void TEToolbar::loadFromTextFile(const wxString& filepath)
{
	TEFileAdapter adapter;
	adapter.resolve(filepath);
	for (size_t i = 0, n = adapter.m_data.size(); i < n; ++i)
	{
		const TEFileAdapter::Entry& entry = adapter.m_data[i];

 		wxgui::ISymbol* symbol = wxgui::SymbolMgr::Instance()->getSymbol(entry.filepath);
		wxgui::ISprite* sprite = wxgui::SpriteFactory::create(symbol);
 		sprite->setTransform(entry.pos, entry.angle);
 		sprite->setScale(entry.scale);
 
 		m_editPanel->insertSprite(sprite);
 		sprite->release();
	}

	m_editPanel->setItemName(wxgui::FilenameTools::getFilename(filepath));

	m_libraryPanel->loadFromSymbolMgr(*wxgui::SymbolMgr::Instance());
	m_editPanel->resetCanvas();
}

void TEToolbar::storeToTextFile(const wxString& filepath) const
{
	std::vector<wxgui::ISprite*> sprites;
	m_editPanel->traverseSprites(FetchAllVisitor<wxgui::ISprite>(sprites));

	std::ofstream fout(filepath.fn_str());
	fout << sprites.size() << '\n';
	for (size_t i = 0, n = sprites.size(); i < n; ++i)
	{
		wxgui::ISprite* sprite = sprites[i];
		fout << sprite->getSymbol().getFilepath() << '\n';
		fout << sprite->getPosition() << " " << sprite->getAngle() << " " << sprite->getScale() << '\n';
	}
	fout.close();
}

//////////////////////////////////////////////////////////////////////////
// class TEToolbar::PasteTileCMPT
//////////////////////////////////////////////////////////////////////////

TEToolbar::PasteTileCMPT::
PasteTileCMPT(wxWindow* parent, const wxString& name, TEEditPanel* editPanel, 
			  wxgui::LibraryPanel* libraryPanel)
	: AbstractEditCMPT(parent, name, editPanel)
{
	addChild(new wxgui::PasteSymbolScaleCMPT(this, wxT("普通"), editPanel, editPanel, libraryPanel));
	addChild(new wxgui::PasteSymbolRandomCMPT(this, wxT("随机"), editPanel, editPanel, libraryPanel));
}

wxSizer* TEToolbar::PasteTileCMPT::
initLayout()
{
	return initChildrenLayout();
}