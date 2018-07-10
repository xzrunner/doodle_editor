#include "LibraryCombinationPage.h"
#include "LibraryCombinationItem.h"
#include "LibraryCombinationList.h"

#include "Frame/defs.h"

using namespace deditor::motox;

LibraryCombinationPage::LibraryCombinationPage(wxWindow* parent)
	: ILibraryPage(parent, wxT("组合(打散)"))
{
	m_list = new LibraryCombinationList(this);
	initLayout();
}

bool LibraryCombinationPage::isHandleSymbol(wxgui::ISymbol* symbol) const
{
	return dynamic_cast<LibraryCombinationItem*>(symbol) != NULL;
}

void LibraryCombinationPage::onAddPress(wxCommandEvent& event)
{
	wxString filter = wxT("*_") + COMBINATION_TASK_TAG + wxT(".txt");
	wxFileDialog dlg(this, wxT("导入组合文件"), wxEmptyString, 
		wxEmptyString, filter, wxFD_OPEN | wxFD_MULTIPLE);
	if (dlg.ShowModal() == wxID_OK)
	{
		wxArrayString filenames;
		dlg.GetPaths(filenames);
		for (size_t i = 0, n = filenames.size(); i < n; ++i)
		{
			LibraryCombinationItem* item = new LibraryCombinationItem;
			item->loadFromFile(filenames[i]);
			m_list->insert(item);
		}
	}
}