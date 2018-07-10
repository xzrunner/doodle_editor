#include "Task.h"
#include "LibraryPanel.h"
#include "StagePanel.h"
#include "ToolbarPanel.h"

#include "Frame/defs.h"

using namespace deditor::motox;

Task::Task(wxFrame* parent)
	: BaseTask(parent)
{
	wxgui::Settings::RESOURCE_PATH.insert(wxT("D:\\MyProject\\svn 2\\FruitsEditor\\MotoX\\MotoX\\editor\\"));
	wxgui::Settings::RESOURCE_PATH.insert(wxT("D:\\MyProject\\svn 2\\FruitsEditor\\MotoX\\MotoX\\editor\\Ê÷Ä£°å\\"));
	wxgui::Settings::RESOURCE_PATH.insert(wxT("D:\\MyProject\\svn 2\\FruitsEditor\\MotoX\\MotoX\\editor\\÷¼÷Ã\\"));
	initLayout();
}

void Task::loadFromTextFile(const char* filename)
{
}

void Task::storeToTextFile(const char* filename) const
{
}

const wxString& Task::getFileTag() const
{
	return MOTOX_TASK_TAG;
}

void Task::clear()
{
	wxgui::SymbolMgr::Instance()->clear();
	wxgui::BitmapMgr::Instance()->clear();
	wxgui::ImageMgr::Instance()->clear();

 	m_library->clear();
 	m_stage->clear();
 	m_library->Refresh();
 	m_stage->Refresh();
}

void Task::initWindows(wxSplitterWindow* leftHorizontalSplitter, 
					   wxSplitterWindow* leftVerticalSplitter, 
					   wxSplitterWindow* rightVerticalSplitter, 
					   wxWindow*& library, wxWindow*& property, 
					   wxWindow*& stage, wxWindow*& toolbar)
{
	library = m_library = new LibraryPanel(leftHorizontalSplitter);

	property = m_propertyPanel = new wxgui::PropertySettingPanel(leftHorizontalSplitter);
	stage = m_stage = new StagePanel(leftVerticalSplitter, m_library);
	m_library->registerContext(m_propertyPanel, m_stage);

	toolbar = m_toolbarPanel = new ToolbarPanel(rightVerticalSplitter, m_propertyPanel, m_stage, m_library);
	m_stage->setLayersMgr(m_toolbarPanel->getLayersMgr());
}