#include "GamePage.h"
#include "Dataset/DataConnection.h"
#include <wx/textctrl.h>

using namespace GAME_FRUITS::VIEW::LIBRARY;

GamePage::GamePage(wxWindow* parent)
	: wxPanel(parent)
{
	initLayout();
}

void GamePage::setName(const wxString& name)
{
	m_name->Clear();
	*m_name << name;
}

void GamePage::initLayout()
{
	wxSizer* sizerPage = new wxBoxSizer(wxVERTICAL);

	wxStaticText* textGame = new wxStaticText(this, wxID_ANY, wxT("Name: "));
	sizerPage->Add(textGame);
	m_name = new wxTextCtrl(this, wxID_ANY, DataConnection::m_game.m_name, wxDefaultPosition, wxDefaultSize, wxTE_READONLY);
	sizerPage->Add(m_name);

	SetSizer(sizerPage);
}