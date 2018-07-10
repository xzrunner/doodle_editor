#include "SpritesPage.h"

using namespace GAME_FRUITS::VIEW::LIBRARY;

SpritesPage::SpritesPage(wxWindow* parent)
	: LibraryPageBase(parent)
{
	Connect(m_add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(SpritesPage::onAddSprite));
	Connect(m_del->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(SpritesPage::onDelSprite));
}

void SpritesPage::onAddSprite(wxCommandEvent& event)
{
	wxMessageBox(wxT("todo: onAddSprite"));
}

void SpritesPage::onDelSprite(wxCommandEvent& event)
{
	wxMessageBox(wxT("todo: onDelSprite"));
}