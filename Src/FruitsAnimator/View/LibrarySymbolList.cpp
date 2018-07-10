#include "LibrarySymbolList.h"
#include "SymbolEditDialog.h"
#include "StagePanel.h"
#include "LibraryPanel.h"
#include "Dataset/Symbol.h"

using namespace FRUITS_ANIMATOR;

LibrarySymbolList::LibrarySymbolList(wxWindow* parent)
	: wxgui::VerticalImageList(parent, LibraryPanel::SYMBOL_LIST_NAME)
{
}

void LibrarySymbolList::loadFromTextFile(std::ifstream& fin)
{
	clear();

	std::string flag;
	size_t size;
	fin >> flag >> size;
	for (size_t i = 0; i < size; ++i)
	{
		Symbol* symbol = new Symbol;
		symbol->loadFromTextFile(fin);
		insert(symbol);
	}
}

void LibrarySymbolList::storeToTextFile(std::ofstream& fout) const
{
	fout << "symbol " << m_items.size() << '\n';
	for (size_t i = 0, n = m_items.size(); i < n; ++i)
	{
		Symbol* symbol = static_cast<Symbol*>(m_items[i]);
		symbol->storeToTextFile(fout);
	}
}

Symbol* LibrarySymbolList::getSymbol(int index) const
{
	if (index < 0 || index >= m_items.size()) return NULL;
	else return static_cast<Symbol*>(m_items[index]);
}

int LibrarySymbolList::getIndex(Symbol* symbol) const
{
	return STLTools::getArrayIndex(m_items, static_cast<wxgui::ListItem*>(symbol));
}

void LibrarySymbolList::reloadAllTexture()
{
	for (size_t i = 0, n = m_items.size(); i < n; ++i)
		static_cast<Symbol*>(m_items[i])->reloadTexture();
}

void LibrarySymbolList::setStagePanel(StagePanel* stagePanel)
{
	m_stagePanel = stagePanel;
}

void LibrarySymbolList::onListDoubleClicked(wxCommandEvent& event)
{
	SymbolEditDialog dlg(this, static_cast<Symbol*>(m_items[event.GetInt()]));
	dlg.ShowModal();
	m_stagePanel->resetCanvas();
}