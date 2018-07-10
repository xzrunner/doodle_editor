#include "Task.h"
#include "LibraryPanel.h"
#include "StagePanel.h"
#include "ToolbarPanel.h"
#include "FileIO.h"
#include "Frame/defs.h"

using namespace deditor::boundary_extraction;

Task::Task(wxFrame* parent)
	: BaseTask(parent)
{
	initLayout();
}

void Task::loadFromTextFile(const char* filename)
{
	std::ifstream fin(filename);
	FileIO::load(fin, m_library);
	fin.close();
}

void Task::storeToTextFile(const char* filename) const
{
	std::ofstream fout(filename);
	FileIO::store(fout, m_library);
	fout.close();
}

const wxString& Task::getFileTag() const
{
	return BOUNDARY_EXTRACTION_TASK_TAG;
}

void Task::clear()
{
	m_library->clear();
	m_stage->changeCurrItem(NULL);
	m_library->Refresh();
	m_stage->Refresh();
}

void Task::initWindows(wxSplitterWindow* leftHorizontalSplitter, 
					   wxSplitterWindow* leftVerticalSplitter, 
					   wxSplitterWindow* rightVerticalSplitter, 
					   wxWindow*& library, wxWindow*& property, 
					   wxWindow*& stage, wxWindow*& toolbar)
{
	property = new wxgui::PropertySettingPanel(leftHorizontalSplitter);

	stage = m_stage = new StagePanel(leftVerticalSplitter);

	ToolbarPanel* toolbarPanel = new ToolbarPanel(rightVerticalSplitter, m_stage);
	toolbar = toolbarPanel;

	library = m_library = new LibraryPanel(leftHorizontalSplitter, m_stage, toolbarPanel);
}