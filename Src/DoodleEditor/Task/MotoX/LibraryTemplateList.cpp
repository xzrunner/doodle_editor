#include "LibraryTemplateList.h"
#include "TEDialog.h"
#include "LibraryTemplateItem.h"
#include "LibraryPanel.h"

using namespace deditor::motox;

LibraryTemplateList::LibraryTemplateList(wxWindow* parent)
	: wxgui::LibraryList(parent, LibraryPanel::TEMPLATE_LIST_NAME)
	, m_editPanel(NULL)
	, m_propertyPanel(NULL)
{
}

void LibraryTemplateList::onListDoubleClicked(wxCommandEvent& event)
{
	TEDialog dlg(this, static_cast<LibraryTemplateItem*>(m_items[event.GetInt()]), m_propertyPanel);
	dlg.ShowModal();
	if (m_editPanel)
		m_editPanel->resetCanvas();
}
