#include "LibraryPanel.h"
#include "LibraryCombinationPage.h"
#include "LibraryTemplatePage.h"
#include "LibraryBreakablePage.h"
#include "LibraryActorPage.h"

using namespace deditor::motox;

const wxString LibraryPanel::COMBINATION_LIST_NAME = wxT("combination");
const wxString LibraryPanel::TEMPLATE_LIST_NAME = wxT("template");
const wxString LibraryPanel::BREAKABLE_LIST_NAME = wxT("breakable");
const wxString LibraryPanel::ACTOR_LIST_NAME = wxT("actor");

LibraryPanel::LibraryPanel(wxWindow* parent)
	: wxgui::LibraryPanel(parent)
{
	addPage(new wxgui::LibraryImagePage(getNotebook()));
	addPage(new LibraryCombinationPage(getNotebook()));
	addPage(m_templatePage = new LibraryTemplatePage(getNotebook()));
	addPage(new wxgui::LibraryCombinationPage(getNotebook()));
	addPage(new LibraryBreakablePage(getNotebook()));
	addPage(m_actorPage = new LibraryActorPage(getNotebook()));
}

void LibraryPanel::registerContext(wxgui::PropertySettingPanel* propertyPanel,
								   wxgui::EditPanel* editPanel)
{
	m_actorPage->registerContext(propertyPanel, editPanel);
	m_templatePage->registerContext(propertyPanel, editPanel);
}