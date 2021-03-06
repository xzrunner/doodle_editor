#include "Task.h"
#include "StagePanel.h"
#include "ToolbarPanel.h"
#include "FileIO.h"

#include "Frame/defs.h"

using namespace deditor::combination;

Task::Task(wxFrame* parent)
	: BaseTask(parent)
	, m_libraryPanel(NULL)
	, m_stage(NULL)
{
	initLayout();
}

void Task::loadFromTextFile(const char* filename)
{
	wxgui::CombinationFileAdapter adapter;
 	adapter.load(filename);
 	FileIO::load(adapter, m_stage, m_libraryPanel);
}

void Task::storeToTextFile(const char* filename) const
{
 	std::ofstream fout(filename);
 	FileIO::store(fout, m_stage);
 	fout.close();
}

const wxString& Task::getFileTag() const
{
	return COMBINATION_TASK_TAG;
}

void Task::clear()
{
	m_libraryPanel->clear();
	m_stage->clear();
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
	m_libraryPanel->addPage(new wxgui::LibraryImagePage(m_libraryPanel->getNotebook()));
	m_libraryPanel->addPage(new wxgui::LibraryShapePage(m_libraryPanel->getNotebook()));
	m_libraryPanel->addPage(new wxgui::LibraryMeshPage(m_libraryPanel->getNotebook()));

	property = m_propertyPanel = new wxgui::PropertySettingPanel(leftHorizontalSplitter);

	stage = m_stage = new StagePanel(leftVerticalSplitter, m_propertyPanel, m_libraryPanel);

	toolbar = new ToolbarPanel(rightVerticalSplitter, m_stage, m_libraryPanel, m_propertyPanel);
}