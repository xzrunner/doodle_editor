#include "Frame.h"
#include "View/Library/LibraryPanel.h"
#include "View/Stage/StagePanel.h"
#include "Output/DesignerPage.h"
#include "View/Backstage/BackstagePanel.h"
#include "View/Backstage/DstPanel.h"
#include "Dataset/InterimData.h"
#include "Dataset/DataConnection.h"
#include "Preview/MainDialog.h"
#include <wx/splitter.h>

using namespace GAME_FRUITS;

BEGIN_EVENT_TABLE(Frame, wxFrame)
	EVT_MENU(wxID_EXIT, Frame::onQuit)
	EVT_MENU(myID_MENU_PREVIEW, Frame::onPreview)
	EVT_MENU(myID_MENU_FULL, Frame::onFullScreenStage)
	EVT_MENU(wxID_HELP, Frame::onAbout)
END_EVENT_TABLE()

const float Frame::SASH_GRAVITY_HOR = 0.5F;
const float Frame::SASH_GRAVITY_VER = 0.15F;

Frame::Frame(const wxString& title)
	: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600))
{
	initMenuBar();
	initWorkingFrame();
}

void Frame::onQuit(wxCommandEvent& event)
{
	Close(true);
}

void Frame::onPreview(wxCommandEvent& event)
{
	PREVIEW::MainDialog preview(this);
	preview.loadFromScene(DataConnection::m_currScene);
	preview.ShowModal();

// 	PREVIEW::MainFrame* preview = new PREVIEW::MainFrame;
// 	preview->Show(true);
}

void Frame::onFullScreenStage(wxCommandEvent& event)
{
	if (m_splitter->IsSplit())
		m_splitter->Unsplit();
	else
	{
		m_top->Show(true);
		m_bottom->Show(true);
		m_splitter->SetSashGravity(SASH_GRAVITY_HOR);
		m_splitter->SplitHorizontally(m_top, m_bottom);
	}
}

void Frame::onAbout(wxCommandEvent& event)
{
	wxString msg;
	msg.Printf( wxT("Simplify the process of game development.\n(c) zz, 2012"));
	wxMessageBox(msg, wxT("About GameFruits"), wxOK | wxICON_INFORMATION, this);
}

void Frame::initMenuBar()
{
	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(initFileBar(), "&File");
	menuBar->Append(initViewBar(), "&View");
	menuBar->Append(initHelpBar(), "&Help");	
	SetMenuBar(menuBar);
}

wxMenu* Frame::initFileBar()
{
	wxMenu* fileMenu = new wxMenu;
	fileMenu->Append(wxID_NEW, wxT("&New\tCtrl+N"), wxT("Create a project"));
	fileMenu->Append(wxID_OPEN, wxT("&Open\tCtrl+O"), wxT("Open a project"));
	fileMenu->AppendSeparator();
	fileMenu->Append(wxID_CLOSE, wxT("&Close\tCtrl+C"), wxT("Close the project"));
	fileMenu->Append(wxID_SAVE, wxT("&Save\tCtrl+S"), wxT("Save the project"));
	fileMenu->Append(wxID_SAVEAS, wxT("&Save as...\tF12", wxT("Save to a new file")));
	fileMenu->AppendSeparator();
	fileMenu->Append(wxID_EXIT, wxT("E&xit\tAlt+X"), wxT("Quit GameFruits"));
	return fileMenu;
}

wxMenu* Frame::initViewBar()
{
	wxMenu* viewMenu = new wxMenu;
	viewMenu->Append(myID_MENU_PREVIEW, wxT("&Preview\tF5"), wxT("Play the project"));
	viewMenu->Append(myID_MENU_FULL, wxT("&Full Screen\tF6"), wxT("Full screen stage"));
	return viewMenu;
}

wxMenu* Frame::initHelpBar()
{
	wxMenu* helpMenu = new wxMenu;
	helpMenu->Append(wxID_HELP, wxT("&About...\tF1"), wxT("Show about dialog"));
	return helpMenu;
}

void Frame::initWorkingFrame()
{
	m_splitter = new wxSplitterWindow(this);

	wxSplitterWindow* stage = new wxSplitterWindow(m_splitter);
	VIEW::BackstagePanel* backstagePanel = new VIEW::BackstagePanel(m_splitter);
	backstagePanel->SetBackgroundColour(wxColour("#afafaf"));
	m_splitter->SetSashGravity(SASH_GRAVITY_HOR);
	m_splitter->SplitHorizontally(stage, backstagePanel);

	m_top = stage;
	m_bottom = backstagePanel;

	VIEW::StagePanel* stagePanel = new VIEW::StagePanel(stage);
	DataConnection::m_stage = stagePanel;
	stagePanel->SetBackgroundColour(wxColour("#afafaf"));
	VIEW::LibraryPanel* library = new VIEW::LibraryPanel(stage);
	library->SetBackgroundColour(wxColour("#afafaf"));
	stage->SetSashGravity(SASH_GRAVITY_VER);
	stage->SplitVertically(library, stagePanel);
}
