//#include "LibraryPanel.h"
//#include "LibraryImagePage.h"
//#include "LibraryFilePage.h"
//
//using namespace deditor::boundary_extraction;
//
//const wxString LibraryPanel::SYMBOL_LIST_NAME = wxT("image");
//const wxString LibraryPanel::ACTOR_LIST_NAME = wxT("file");
//
//LibraryPanel::LibraryPanel(wxWindow* parent, StagePanel* stage, ToolbarPanel* toolbar)
//	: wxPanel(parent, wxID_ANY)
//{
//	initLayout(stage, toolbar);
//}
//
//void LibraryPanel::loadFromTextFile(std::ifstream& fin)
//{
//	m_imagePage->loadFromTextFile(fin);
//	m_filePage->loadFromTextFile(fin);
//}
//
//void LibraryPanel::storeToTextFile(std::ofstream& fout) const
//{
//	m_imagePage->storeToTextFile(fout);
//	m_filePage->storeToTextFile(fout);
//}
//
//void LibraryPanel::clear()
//{
//	m_imagePage->clear();
//	m_filePage->clear();
//}
//
//void LibraryPanel::initLayout(StagePanel* stage, ToolbarPanel* toolbar)
//{
//	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
//
//	wxNotebook *notebook = new wxNotebook(this, wxID_ANY);
//	Connect(notebook->GetId(), wxEVT_COMMAND_NOTEBOOK_PAGE_CHANGED, 
//		wxBookCtrlEventHandler(LibraryPanel::onPageChanged));
//
//	m_imagePage = new LibraryImagePage(notebook, stage, toolbar);
//	notebook->AddPage(m_imagePage, wxT("Í¼Æ¬"));
//
//	m_filePage = new LibraryFilePage(notebook, stage, toolbar);
//	notebook->AddPage(m_filePage, wxT("ÎÄ¼þ"));
//
//	sizer->Add(notebook, 1, wxEXPAND);
//
//	SetSizer(sizer);
//}
//
//void LibraryPanel::onPageChanged(wxBookCtrlEvent& event)
//{
//	if (event.GetSelection() == 0)
//	{
//		m_imagePage->clickListSelection();
//	}
//	else if (event.GetSelection() == 1)
//	{
//		m_filePage->clickListSelection();
//	}
//}

#include "LibraryPanel.h"
#include "LibraryImageList.h"
#include "LibraryImagePage.h"
#include "LibraryFileList.h"
#include "LibraryFilePage.h"

#include <wx/notebook.h>

using namespace deditor::boundary_extraction;

LibraryPanel::LibraryPanel(wxWindow* parent, StagePanel* stage, 
						   ToolbarPanel* toolbar)
	: wxgui::LibraryPanel(parent)
{
	m_imagePage = new LibraryImagePage(getNotebook());
	static_cast<LibraryImageList*>(m_imagePage->getList())->registerContext(stage, toolbar);
	addPage(m_imagePage);

	m_filePage = new LibraryFilePage(getNotebook());
	static_cast<LibraryFileList*>(m_filePage->getList())->registerContext(stage, toolbar);
	addPage(m_filePage);
}

void LibraryPanel::loadFromTextFile(std::ifstream& fin)
{
	m_imagePage->loadFromTextFile(fin);
	m_filePage->loadFromTextFile(fin);
}

void LibraryPanel::storeToTextFile(std::ofstream& fout) const
{
	m_imagePage->storeToTextFile(fout);
	m_filePage->storeToTextFile(fout);
}

void LibraryPanel::onPageChanged(wxBookCtrlEvent& event)
{
	wxgui::LibraryPanel::onPageChanged(event);
	
	if (event.GetSelection() == 0)
		m_imagePage->clickListSelection();
	else if (event.GetSelection() == 1)
		m_filePage->clickListSelection();
}