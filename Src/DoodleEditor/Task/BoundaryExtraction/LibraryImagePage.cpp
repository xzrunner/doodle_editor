#include "LibraryImagePage.h"
#include "LibraryImageList.h"
#include "LibraryImageItem.h"
#include "FileIO.h"

using namespace deditor::boundary_extraction;

LibraryImagePage::LibraryImagePage(wxWindow* parent)
	: ILibraryPage(parent, wxT("ͼƬ"))
{
	m_list = new LibraryImageList(this);
	initLayout();
}

void LibraryImagePage::loadFromTextFile(std::ifstream& fin)
{
	m_list->loadFromTextFile(fin);
}

void LibraryImagePage::storeToTextFile(std::ofstream& fout) const
{
	traverse(FileIO::StoreItemVisitor(fout));
}

bool LibraryImagePage::isHandleSymbol(wxgui::ISymbol* symbol) const
{
	return dynamic_cast<LibraryImageItem*>(symbol) != NULL;
}

void LibraryImagePage::clickListSelection()
{
	int index = m_list->GetSelection();
	if (index != -1)
	{
		wxCommandEvent event;
		event.SetInt(index);
		m_list->onListSelected(event);
	}
}

void LibraryImagePage::onAddPress(wxCommandEvent& event)
{
	wxFileDialog dlg(this, wxT("ѡ��ͼƬ"), wxEmptyString, 
		wxEmptyString, wxT("*.png;*.jpg;*.bmp"), wxFD_OPEN | wxFD_MULTIPLE);
	if (dlg.ShowModal() == wxID_OK)
	{
		wxArrayString filenames;
		dlg.GetPaths(filenames);
		for (size_t i = 0, n = filenames.size(); i < n; ++i)
		{
			LibraryImageItem* item = new LibraryImageItem(filenames[i]);
			m_list->insert(item);
		}
	}
}