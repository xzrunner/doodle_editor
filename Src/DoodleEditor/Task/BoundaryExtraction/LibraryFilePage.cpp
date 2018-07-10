#include "LibraryFilePage.h"
#include "LibraryFileList.h"
#include "LibraryFileItem.h"
#include "FileIO.h"

#include "Frame/defs.h"

using namespace deditor::boundary_extraction;

LibraryFilePage::LibraryFilePage(wxWindow* parent)
	: ILibraryPage(parent, wxT("文件"))
{
	m_list = new LibraryFileList(this);
	initLayout();
}

void LibraryFilePage::loadFromTextFile(std::ifstream& fin)
{
	m_list->loadFromTextFile(fin);
}

void LibraryFilePage::storeToTextFile(std::ofstream& fout) const
{
	traverse(FileIO::StoreItemVisitor(fout));
}

bool LibraryFilePage::isHandleSymbol(wxgui::ISymbol* symbol) const
{
	return dynamic_cast<LibraryFileItem*>(symbol) != NULL;
}

void LibraryFilePage::clickListSelection()
{
	int index = m_list->GetSelection();
	if (index != -1)
	{
		wxCommandEvent event;
		event.SetInt(index);
		m_list->onListSelected(event);
	}
}

void LibraryFilePage::onAddPress(wxCommandEvent& event)
{
	wxString formatFilter;
	formatFilter += wxT("人工拼图文件 (*_") + MANUAL_COMPOSE_TASK_TAG + wxT(".txt)") + wxT(" | *_") + MANUAL_COMPOSE_TASK_TAG + wxT(".txt");
	wxFileDialog dlg(this, wxT("选择文件"), wxEmptyString, 
		wxEmptyString, formatFilter, wxFD_OPEN | wxFD_MULTIPLE);
	if (dlg.ShowModal() == wxID_OK)
	{
		wxArrayString filenames;
		dlg.GetPaths(filenames);
		for (size_t i = 0, n = filenames.size(); i < n; ++i)
		{
			LibraryFileItem* item = new LibraryFileItem(filenames[i]);
			m_list->insert(item);
		}
	}
}