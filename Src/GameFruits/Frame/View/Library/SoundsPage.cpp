#include "SoundsPage.h"

using namespace GAME_FRUITS::VIEW::LIBRARY;

SoundsPage::SoundsPage(wxWindow* parent)
	: LibraryPageBase(parent)
{
	Connect(m_add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(SoundsPage::onAddSound));
	Connect(m_del->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(SoundsPage::onDelSound));
}

void SoundsPage::onAddSound(wxCommandEvent& event)
{
	wxMessageBox(wxT("todo: onAddSound"));
}

void SoundsPage::onDelSound(wxCommandEvent& event)
{
	wxMessageBox(wxT("todo: onDelSound"));
}
