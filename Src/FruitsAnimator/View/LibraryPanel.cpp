#include "LibraryPanel.h"
#include "LibrarySymbolPage.h"
#include "LibrarySkeletonPage.h"

#include <wx/notebook.h>

using namespace FRUITS_ANIMATOR;

const wxString LibraryPanel::SYMBOL_LIST_NAME = wxT("symbol");
const wxString LibraryPanel::SKELETON_LIST_NAME = wxT("skeleton");

LibraryPanel::LibraryPanel(wxWindow* parent)
	: wxPanel(parent, wxID_ANY)
{
	initLayout();
}

void LibraryPanel::loadFromTextFile(std::ifstream& fin)
{
	wxgui::BitmapMgr::Instance()->clear();
	m_symbolPage->loadFromTextFile(fin);
	m_skeletonPage->loadFromTextFile(fin);
}

void LibraryPanel::storeToTextFile(std::ofstream& fout) const
{
	m_symbolPage->storeToTextFile(fout);
	m_skeletonPage->storeToTextFile(fout);
}

Symbol* LibraryPanel::getSymbol(int index) const
{
	return m_symbolPage->getSymbol(index);
}

WholeSkeleton* LibraryPanel::getSkeleton(int index) const
{
	return m_skeletonPage->getSkeleton(index);
}

int LibraryPanel::getIndex(Symbol* symbol) const
{
	return m_symbolPage->getIndex(symbol);
}

int LibraryPanel::getIndex(WholeSkeleton* skeleton) const
{
	return m_skeletonPage->getIndex(skeleton);
}

void LibraryPanel::reloadAllTexture()
{
	m_symbolPage->reloadAllTexture();
}

void LibraryPanel::setStagePanel(StagePanel* stagePanel)
{
	m_symbolPage->setStagePanel(stagePanel);
	m_skeletonPage->setStagePanel(stagePanel);
}

void LibraryPanel::initLayout()
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	initTitle(sizer);
	initTabPages(sizer);
	SetSizer(sizer);
}

void LibraryPanel::clear()
{
	m_symbolPage->clear();
	m_skeletonPage->clear();
}

void LibraryPanel::initTitle(wxSizer* sizer)
{
	wxStaticText* title = new wxStaticText(this, wxID_ANY, wxT("Library"));
	title->SetForegroundColour(*wxWHITE);
	title->SetBackgroundColour(*wxBLACK);
	sizer->Add(title, 0, wxEXPAND);
}

void LibraryPanel::initTabPages(wxSizer* sizer)
{
	wxNotebook *notebook = new wxNotebook(this, wxID_ANY);

	m_symbolPage = new LibrarySymbolPage(notebook);
	notebook->AddPage(m_symbolPage, wxT("Ԫ��"));

   	m_skeletonPage = new LibrarySkeletonPage(notebook, this);
   	notebook->AddPage(m_skeletonPage, wxT("����"));

	sizer->Add(notebook, 1, wxEXPAND);
}