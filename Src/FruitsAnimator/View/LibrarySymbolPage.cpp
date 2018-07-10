#include "LibrarySymbolPage.h"
#include "LibrarySymbolList.h"
#include "Dataset/Symbol.h"

using namespace FRUITS_ANIMATOR;

LibrarySymbolPage::LibrarySymbolPage(wxWindow* parent)
	: ILibraryPage(parent)
{
	initLayout();

	wxSizer* sizer = GetSizer();
	m_symbolList = new LibrarySymbolList(this);
	sizer->Add(m_symbolList, 1, wxEXPAND);
	SetSizer(sizer);
}

void LibrarySymbolPage::loadFromTextFile(std::ifstream& fin)
{
	m_symbolList->loadFromTextFile(fin);
}

void LibrarySymbolPage::storeToTextFile(std::ofstream& fout) const
{
	m_symbolList->storeToTextFile(fout);
}

void LibrarySymbolPage::traverse(IVisitor& visitor) const
{
	m_symbolList->traverse(visitor);
}

Symbol* LibrarySymbolPage::getSymbol(int index) const
{
	return m_symbolList->getSymbol(index);
}

int LibrarySymbolPage::getIndex(Symbol* symbol) const
{
	return m_symbolList->getIndex(symbol);
}

void LibrarySymbolPage::reloadAllTexture()
{
	m_symbolList->reloadAllTexture();
}

void LibrarySymbolPage::setStagePanel(StagePanel* stagePanel)
{
	m_symbolList->setStagePanel(stagePanel);
}

void LibrarySymbolPage::clear()
{
	m_symbolList->clear();
}

void LibrarySymbolPage::onAddPress(wxCommandEvent& event)
{
	wxFileDialog dlg(this, wxT("Please choose a image"), wxEmptyString, wxEmptyString, wxT("*.png;*.jpg"), wxFD_OPEN | wxFD_MULTIPLE);
	if (dlg.ShowModal() == wxID_OK)
	{
		wxArrayString filenames;
		dlg.GetPaths(filenames);
		for (size_t i = 0, n = filenames.size(); i < n; ++i)
			m_symbolList->insert(new Symbol(filenames[i]));
	}
}

void LibrarySymbolPage::onDelPress(wxCommandEvent& event)
{
	m_symbolList->remove();
}