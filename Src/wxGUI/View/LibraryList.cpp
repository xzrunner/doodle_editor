#include "LibraryList.h"

#include "Dataset/ISymbol.h"

using namespace wxgui;

LibraryList::LibraryList(wxWindow* parent,
						 const wxString& filter/* = wxT("symbol")*/,
						 bool draggable /*= true*/)
	: VerticalImageList(parent, filter, draggable)
{
}

void LibraryList::loadFromTextFile(std::ifstream& fin)
{

}

void LibraryList::storeToTextFile(std::ofstream& fout) const
{

}

ListItem* LibraryList::getItem(int index/* = -1*/) const
{
	if (index == -1)
		index = GetSelection();

	if (index < 0 || index >= (int)m_items.size()) 
		return NULL;
	else 
		return m_items[index];
}

ISymbol* LibraryList::getSymbol(int index/* = -1*/) const
{
	ListItem* item = getItem(index);
	if (item)
		return static_cast<ISymbol*>(item);
	else
		return NULL;
}

void LibraryList::reloadTexture() const
{
	for (size_t i = 0, n = m_items.size(); i < n; ++i)
		static_cast<ISymbol*>(m_items[i])->reloadTexture();
}