#include "Task.h"
#include "LibrarySymbolPage.h"
#include "LibrarySymbolList.h"
#include "StagePanel.h"
#include "ToolbarPanel.h"
#include "Frame/defs.h"

using namespace deditor::compress_pictures;

Task::Task(wxFrame* parent)
	: BaseTask(parent)
{
	initLayout();
}

const wxString& Task::getFileTag() const
{
	return COMPRESS_PICTURES_TASK_TAG;
}

void Task::clear()
{
	m_libraryPanel->clear();
	m_stage->changeSymbol(NULL);
	m_libraryPanel->Refresh();
	m_stage->Refresh();
}

void Task::initWindows(wxSplitterWindow* leftHorizontalSplitter, 
					   wxSplitterWindow* leftVerticalSplitter, 
					   wxSplitterWindow* rightVerticalSplitter, 
					   wxWindow*& library, wxWindow*& property, 
					   wxWindow*& stage, wxWindow*& toolbar)
{
	library = m_libraryPanel = new wxgui::LibraryPanel(leftHorizontalSplitter);
	wxgui::ILibraryPage* page = new LibrarySymbolPage(m_libraryPanel->getNotebook());
	m_libraryPanel->addPage(page);

	property = new wxgui::PropertySettingPanel(leftHorizontalSplitter);

	stage = m_stage = new StagePanel(leftVerticalSplitter);

	ToolbarPanel* toolbarPanel = new ToolbarPanel(rightVerticalSplitter, m_stage);
	m_stage->setToolbar(toolbarPanel);
	toolbar = toolbarPanel;

	LibrarySymbolList* list = static_cast<LibrarySymbolList*>(page->getList());
	list->registerContext(m_stage, toolbarPanel);
	toolbarPanel->setLibraryList(list);
}