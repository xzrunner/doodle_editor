#include "Task.h"
#include "StagePanel.h"
#include "ToolbarPanel.h"
#include "FileIO.h"

#include "Frame/defs.h"
#include "Tools/ManualComposeFileAdapter.h"

#include <json/json.h>

using namespace deditor::manual_compose;

Task::Task(wxFrame* parent)
	: BaseTask(parent)
	, m_libraryPanel(NULL)
	, m_stage(NULL)
{
	initLayout();
}

void Task::loadFromTextFile(const char* filename)
{
 	ManualComposeFileAdapter fileAdapter;
 	fileAdapter.load(filename);
 	FileIO::load(fileAdapter, m_stage, m_libraryPanel);

	//////////////////////////////////////////////////////////////////////////

// 	std::ifstream fin(filename);
// 	Json::Value value;
// 	Json::Reader reader;
// 	reader.parse(fin, value);
// 	fin.close();
// 
// 	std::string bg = value["background"].asString();
// 
// 	std::vector<std::string> sprites;
// 	int i = 0;
// 	Json::Value spriteValue = value["sprite"][i++];
// 	while (!spriteValue.isNull())
// 	{
// 		sprites.push_back(spriteValue["filepath"].asString());
// 		spriteValue = value["sprite"][i++];
// 	}
// 
// 	int zz = 0;
}

void Task::storeToTextFile(const char* filename) const
{
	std::ofstream fout(filename);
	FileIO::store(fout, m_stage);
	fout.close();
}

const wxString& Task::getFileTag() const
{
	return MANUAL_COMPOSE_TASK_TAG;
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

	toolbar = new ToolbarPanel(rightVerticalSplitter, m_stage);
}