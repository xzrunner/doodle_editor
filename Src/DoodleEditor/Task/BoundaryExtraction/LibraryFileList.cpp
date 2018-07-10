#include "LibraryFileList.h"
#include "LibraryFileItem.h"
#include "StagePanel.h"
#include "ToolbarPanel.h"
#include "LibraryPanel.h"

using namespace deditor::boundary_extraction;

LibraryFileList::LibraryFileList(wxWindow* parent)
	: wxgui::LibraryList(parent)
{
}

void LibraryFileList::loadFromTextFile(std::ifstream& fin)
{
	clear();

	size_t size;
	fin >> size;
	for (size_t i = 0; i < size; ++i)
	{
		std::string filename = StringTools::getLine(fin);
		LibraryFileItem* item = new LibraryFileItem(filename);
		insert(item);
	}
}

void LibraryFileList::storeToTextFile(std::ofstream& fout) const
{

}

void LibraryFileList::onListSelected(wxCommandEvent& event)
{
	LibraryItem* item = static_cast<LibraryItem*>(m_items[event.GetInt()]);
	m_stage->changeCurrItem(item);
	m_toolbar->changeCurrItem(item);
}

void LibraryFileList::registerContext(StagePanel* stage, ToolbarPanel* toolbar)
{
	m_stage = stage;
	m_toolbar = toolbar;
}