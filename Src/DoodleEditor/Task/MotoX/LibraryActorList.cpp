#include "LibraryActorList.h"
#include "AEDialog.h"
#include "LibraryActorItem.h"
#include "LibraryPanel.h"

using namespace deditor::motox;

LibraryActorList::LibraryActorList(wxWindow* parent)
	: wxgui::LibraryList(parent, LibraryPanel::ACTOR_LIST_NAME)
	, m_editPanel(NULL)
	, m_propertyPanel(NULL)
{
}

void LibraryActorList::onListDoubleClicked(wxCommandEvent& event)
{
	AEDialog dlg(this, static_cast<LibraryActorItem*>(m_items[event.GetInt()]), m_propertyPanel);
	dlg.ShowModal();
	if (m_editPanel)
		m_editPanel->resetCanvas();
}
