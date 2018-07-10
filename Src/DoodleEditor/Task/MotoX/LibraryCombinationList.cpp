#include "LibraryCombinationList.h"
#include "LibraryPanel.h"

using namespace deditor::motox;

LibraryCombinationList::LibraryCombinationList(wxWindow* parent)
	: wxgui::LibraryList(parent, LibraryPanel::COMBINATION_LIST_NAME)
{
}
