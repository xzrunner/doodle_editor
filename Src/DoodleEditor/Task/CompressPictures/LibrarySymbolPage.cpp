#include "LibrarySymbolPage.h"
#include "LibrarySymbolList.h"

using namespace deditor::compress_pictures;

LibrarySymbolPage::LibrarySymbolPage(wxWindow* parent)
	: wxgui::LibraryImagePage(parent, false)
{
	GetSizer()->DeleteWindows();

	m_list = new LibrarySymbolList(this);
	initLayout();
}