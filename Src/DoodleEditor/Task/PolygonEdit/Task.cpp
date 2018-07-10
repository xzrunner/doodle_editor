#include "Task.h"
#include "StagePanel.h"
#include "ToolbarPanel.h"
#include "FileIO.h"

#include "Frame/defs.h"

using namespace deditor::polygon_edit;

Task::Task(wxFrame* parent)
	: BaseTask(parent)
	, m_libraryPanel(NULL)
	, m_stage(NULL)
{
	wxgui::Settings::RESOURCE_PATH.insert(wxT("D:\\MyProject\\svn 2\\FruitsEditor\\MotoX\\MotoX\\editor\\"));

	initLayout();
}

void Task::loadFromTextFile(const char* filename)
{
	FileIO::load(filename, m_stage);
}

void Task::storeToTextFile(const char* filename) const
{
	FileIO::store(filename, m_stage);
}

const wxString& Task::getFileTag() const
{
	return FILLING_POLYGON_TASK_TAG;
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

	toolbar = m_toolbarPanel = new ToolbarPanel(rightVerticalSplitter, m_stage);
	m_stage->setLayersMgr(m_toolbarPanel->getLayersMgr());
}