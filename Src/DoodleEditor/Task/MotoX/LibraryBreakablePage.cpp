#include "LibraryBreakablePage.h"
#include "LibraryBreakableItem.h"
#include "LibraryBreakableList.h"

using namespace deditor::motox;

LibraryBreakablePage::LibraryBreakablePage(wxWindow* parent)
	: ILibraryPage(parent, wxT("破碎"))
{
	m_list = new LibraryBreakableList(this);
	initLayout();
}

bool LibraryBreakablePage::isHandleSymbol(wxgui::ISymbol* symbol) const
{
	return dynamic_cast<LibraryBreakableItem*>(symbol) != NULL;
}

void LibraryBreakablePage::onAddPress(wxCommandEvent& event)
{
	wxString filter = wxT("*_") + LibraryBreakableItem::TAG + wxT(".txt");
	wxFileDialog dlg(this, wxT("导入破碎文件"), wxEmptyString, 
		wxEmptyString, filter, wxFD_OPEN | wxFD_MULTIPLE);
	if (dlg.ShowModal() == wxID_OK)
	{
		wxArrayString filenames;
		dlg.GetPaths(filenames);
		for (size_t i = 0, n = filenames.size(); i < n; ++i)
		{
 			LibraryBreakableItem* item = new LibraryBreakableItem;
 			item->loadFromFile(filenames[i]);
 			m_list->insert(item);
		}
	}
}