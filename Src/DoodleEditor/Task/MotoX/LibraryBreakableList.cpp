#include "LibraryBreakableList.h"
#include "LibraryPanel.h"

using namespace deditor::motox;

LibraryBreakableList::LibraryBreakableList(wxWindow* parent)
	: wxgui::LibraryList(parent, LibraryPanel::BREAKABLE_LIST_NAME)
{
}
