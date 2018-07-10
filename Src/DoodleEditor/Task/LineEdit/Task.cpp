#include "Task.h"
#include "StagePanel.h"
#include "ToolbarPanel.h"
#include "FileIO.h"

#include "Frame/defs.h"

using namespace deditor::line_edit;

Task::Task(wxFrame* parent)
	: BaseTask(parent)
	, m_libraryPanel(NULL)
	, m_stage(NULL)
{
	initLayout();
}

void Task::loadFromTextFile(const char* filename)
{
	std::ifstream fin(filename);
	FileIO::load(fin, m_stage);
	fin.close();
}

void Task::storeToTextFile(const char* filename) const
{
	std::ofstream fout(filename);
	FileIO::store(fout, m_stage);
	fout.close();
}

const wxString& Task::getFileTag() const
{
	return EDIT_SHAPE_TASK_TAG;
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

	property = new wxgui::PropertySettingPanel(leftHorizontalSplitter);

	stage = m_stage = new StagePanel(leftVerticalSplitter);

	toolbar = new ToolbarPanel(rightVerticalSplitter, m_stage);
}