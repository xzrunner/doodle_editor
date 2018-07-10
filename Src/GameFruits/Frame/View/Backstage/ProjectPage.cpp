#include "ProjectPage.h"
#include "Dataset/DataConnection.h"
#include "Frame/View/Backstage/DstPanel.h"
#include "Frame/View/Library/GamePage.h"

using namespace GAME_FRUITS;
using namespace GAME_FRUITS::VIEW::BACKSTAGE;

ProjectPage::ProjectPage(wxNotebook* parent)
	: DstPageBase(parent)
{
	m_parent = parent;
	buildPropertyPage();
}

void ProjectPage::buildPropertyPage()
{
	wxSizer* topSizer = m_propertyPage->GetSizer();
	buildNameItem(topSizer);
	buildSizeItem(topSizer);
}

void ProjectPage::buildNameItem(wxSizer* topSizer)
{
	wxBoxSizer* nameSizer = new wxBoxSizer(wxHORIZONTAL);
	wxStaticText* title = new wxStaticText(m_propertyPage, wxID_ANY, wxT("NAME"));
	nameSizer->Add(title, 0, wxALIGN_LEFT);
	nameSizer->AddStretchSpacer(2);
	wxTextCtrl* name = new wxTextCtrl(m_propertyPage, wxID_ANY, DataConnection::m_game.m_name, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	Connect(name->GetId(), wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(ProjectPage::onNameChange));
	nameSizer->Add(name, 5, wxALIGN_RIGHT);
	nameSizer->AddStretchSpacer(1);
	topSizer->Add(nameSizer, 0, wxEXPAND);
}

void ProjectPage::buildSizeItem(wxSizer* topSizer)
{
	topSizer->Add(new wxStaticText(m_propertyPage, wxID_ANY, wxT("SIZE")), 0, wxALIGN_LEFT);

	wxBoxSizer* widthSizer = new wxBoxSizer(wxHORIZONTAL);
	widthSizer->AddStretchSpacer(1);
	widthSizer->Add(new wxStaticText(m_propertyPage, wxID_ANY, wxT("width")), 0, wxALIGN_LEFT);
	widthSizer->AddStretchSpacer(1);
	widthSizer->Add(new wxTextCtrl(m_propertyPage, wxID_ANY, wxVariant(DataConnection::m_game.m_width).GetString()), 5, wxALIGN_RIGHT);
	widthSizer->AddStretchSpacer(1);
	topSizer->Add(widthSizer, 0, wxEXPAND);

	wxBoxSizer* heightSizer = new wxBoxSizer(wxHORIZONTAL);
	heightSizer->AddStretchSpacer(1);
	heightSizer->Add(new wxStaticText(m_propertyPage, wxID_ANY, wxT("height")), 0, wxALIGN_LEFT);
	heightSizer->AddStretchSpacer(1);
	heightSizer->Add(new wxTextCtrl(m_propertyPage, wxID_ANY, wxVariant(DataConnection::m_game.m_height).GetString()), 5, wxALIGN_RIGHT);
	heightSizer->AddStretchSpacer(1);
	topSizer->Add(heightSizer, 0, wxEXPAND);
}

void ProjectPage::onNameChange(wxCommandEvent& event)
{
	if (event.GetEventType() == wxEVT_COMMAND_TEXT_ENTER)
	{
		DataConnection::m_game.m_name = event.GetString();
		m_parent->SetPageText(0, event.GetString());
		LIBRARY::GamePage* page = dynamic_cast<LIBRARY::GamePage*>(DataConnection::m_libraryNotebook->GetPage(0));
		assert(page);
		page->setName(event.GetString());
	}
}