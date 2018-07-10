#include "LayersPage.h"

using namespace GAME_FRUITS::VIEW::LIBRARY;

LayersPage::LayersPage(wxWindow* parent)
	: LibraryPageBase(parent)
{
	Connect(m_add->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LayersPage::onAddLayer));
	Connect(m_del->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LayersPage::onDelLayer));
}

void LayersPage::onAddLayer(wxCommandEvent& event)
{
	wxMessageBox(wxT("todo: onAddLayer"));
}

void LayersPage::onDelLayer(wxCommandEvent& event)
{
	wxMessageBox(wxT("todo: onDelLayer"));
}