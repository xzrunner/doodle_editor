#include "LibraryImageList.h"
#include "LibraryImageItem.h"
#include "StagePanel.h"
#include "ToolbarPanel.h"
#include "LibraryPanel.h"

using namespace deditor::boundary_extraction;

LibraryImageList::LibraryImageList(wxWindow* parent)
	: wxgui::LibraryList(parent)
{
}

void LibraryImageList::loadFromTextFile(std::ifstream& fin)
{
	clear();

	size_t size;
	fin >> size;
	for (size_t i = 0; i < size; ++i)
	{
		std::string filename = StringTools::getLine(fin);
		LibraryImageItem* item = new LibraryImageItem(filename);
		insert(item);
	}
}

void LibraryImageList::storeToTextFile(std::ofstream& fout) const
{

}

void LibraryImageList::onListSelected(wxCommandEvent& event)
{
	if (m_items.empty()) return;

	LibraryItem* item = static_cast<LibraryItem*>(m_items[event.GetInt()]);
	m_stage->changeCurrItem(item);
	m_toolbar->changeCurrItem(item);
}

void LibraryImageList::registerContext(StagePanel* stage, ToolbarPanel* toolbar)
{
	m_stage = stage;
	m_toolbar = toolbar;
}