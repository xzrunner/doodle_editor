#include "Task.h"
#include "StagePanel.h"
#include "ToolbarPanel.h"
#include "FileIO.h"
#include "Frame/defs.h"

using namespace deditor::automatic_merge;

Task::Task(wxFrame* parent)
	: BaseTask(parent)
{
	initLayout();
}

void Task::loadFromTextFile(const char* filename)
{
	std::ifstream fin(filename);
	FileIO::load(fin, m_stage, m_libraryPanel);
	fin.close();
}

void Task::storeToTextFile(const char* filename) const
{
	FileIO::store(filename, m_stage, m_toolbar->getImgType());
}

const wxString& Task::getFileTag() const
{
	return AUTOMATIC_MERGE_TASK_TAG;
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

	property = m_propertyPanel = new wxgui::PropertySettingPanel(leftHorizontalSplitter);

	stage = m_stage = new StagePanel(leftVerticalSplitter, m_propertyPanel, m_libraryPanel);

	toolbar = m_toolbar = new ToolbarPanel(rightVerticalSplitter, m_stage);
}