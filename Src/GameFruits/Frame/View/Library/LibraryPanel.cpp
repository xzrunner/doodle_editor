#include "LibraryPanel.h"
#include "GamePage.h"
#include "ScenePage.h"
#include "LayersPage.h"
#include "SpritesPage.h"
#include "ImagesPage.h"
#include "SoundsPage.h"
#include "Dataset/DataConnection.h"
#include <wx/notebook.h>

using namespace GAME_FRUITS::VIEW;

LibraryPanel::LibraryPanel(wxWindow* parent)
	: wxPanel(parent, wxID_ANY)
{
	initLayout();
}

void LibraryPanel::initLayout()
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	initTitle(sizer);
	initTabPages(sizer);
	SetSizer(sizer);
}

void LibraryPanel::initTitle(wxSizer* sizer)
{
	wxStaticText* title = new wxStaticText(this, wxID_ANY, wxT("Library"));
	title->SetForegroundColour(*wxWHITE);
	title->SetBackgroundColour(*wxBLACK);
	sizer->Add(title, 0, wxEXPAND);
}

void LibraryPanel::initTabPages(wxSizer* sizer)
{
	wxNotebook *notebook = new wxNotebook(this, wxID_ANY);
	notebook->AddPage(new LIBRARY::GamePage(notebook), wxT("Game"));
 	notebook->AddPage(new LIBRARY::ScenePage(notebook), wxT("Scene"));
	notebook->AddPage(new LIBRARY::LayersPage(notebook), wxT("Layer"));
	notebook->AddPage(new LIBRARY::SpritesPage(notebook), wxT("Sprite"));
	notebook->AddPage(new LIBRARY::ImagesPage(notebook), wxT("Image"));
	notebook->AddPage(new LIBRARY::SoundsPage(notebook), wxT("Sound"));
	sizer->Add(notebook, 1, wxEXPAND);

	DataConnection::m_libraryNotebook = notebook;
}