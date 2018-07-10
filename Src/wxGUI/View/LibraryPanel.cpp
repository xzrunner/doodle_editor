#include "LibraryPanel.h"
#include "ILibraryPage.h"
#include "LibraryList.h"
#include "LibraryImagePage.h"

#include "Dataset/SymbolMgr.h"
#include "Dataset/ImageSymbol.h"

using namespace wxgui;

LibraryPanel::LibraryPanel(wxWindow* parent)
	: wxPanel(parent, wxID_ANY)
	, m_selected(NULL)
{
	initLayout();
}

void LibraryPanel::loadFromTextFile(std::ifstream& fin)
{

}

void LibraryPanel::storeToTextFile(std::ofstream& fout) const
{

}

void LibraryPanel::onPageChanged(wxBookCtrlEvent& event)
{
	m_selected = m_pages[event.GetSelection()];
}

void LibraryPanel::clear()
{
	for (size_t i = 0, n = m_pages.size(); i < n; ++i)
		m_pages[i]->clear();
}

void LibraryPanel::reloadTexture() const
{
	if (m_selected)
		m_selected->reloadTexture();
}

void LibraryPanel::addPage(ILibraryPage* page)
{
	if (m_notebook->GetPageCount() == 0)
		m_selected = page;

	m_notebook->AddPage(page, page->getName());
	m_pages.push_back(page);
}

ISymbol* LibraryPanel::getSymbol(int index/* = -1*/) const
{
	if (m_selected)
		return m_selected->getSymbol(index);
	else
		return NULL;
}

void LibraryPanel::loadFromSymbolMgr(const SymbolMgr& mgr)
{
	std::vector<ISymbol*> symbols;
	mgr.traverse(FetchAllVisitor<ISymbol>(symbols));
	for (size_t i = 0, n = symbols.size(); i < n; ++i)
	{
		ISymbol* symbol = symbols[i];
		for (size_t j = 0, m = m_pages.size(); j < m; ++j)
		{
			ILibraryPage* page = m_pages[j];
			if (page->isHandleSymbol(symbol))
			{
				page->getList()->insert(symbol);
				break;
			}
		}
	}
}

void LibraryPanel::traverse(IVisitor& visitor) const
{
	if (m_selected)
		m_selected->traverse(visitor);
}

void LibraryPanel::initLayout()
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	m_notebook = new wxNotebook(this, wxID_ANY);
	Connect(m_notebook->GetId(), wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, wxBookCtrlEventHandler(LibraryPanel::onPageChanged));

	sizer->Add(m_notebook, 1, wxEXPAND);

	SetSizer(sizer);
}