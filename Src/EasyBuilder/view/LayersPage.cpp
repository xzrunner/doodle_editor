#include "LayersPage.h"

using namespace ebuilder;

LayersPage::LayersPage(wxWindow* parent)
	: wxgui::ILibraryPage(parent, wxT("Layers"))
{
	initLayout();
}

bool LayersPage::isHandleSymbol(wxgui::ISymbol* symbol) const
{
	return false;
}

void LayersPage::onAddPress(wxCommandEvent& event)
{
}