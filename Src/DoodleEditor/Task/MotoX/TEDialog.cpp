#include "TEDialog.h"
#include "TEEditPanel.h"
#include "TEToolbar.h"

#include <wxGUI/wxGUI.h>

using namespace deditor::motox;

BEGIN_EVENT_TABLE(TEDialog, wxDialog)
	EVT_SIZE(TEDialog::onSize)
END_EVENT_TABLE()

TEDialog::TEDialog(wxWindow* parent, LibraryTemplateItem* templateItem,
				   wxgui::PropertySettingPanel* propertyPanel)
 	: wxDialog(parent, wxID_ANY, "Edit Template", wxDefaultPosition, 
	wxSize(800, 600), wxCLOSE_BOX | wxCAPTION | wxMAXIMIZE_BOX)
	, m_propertyPanel(propertyPanel)
{
	initLayout(templateItem);
}

void TEDialog::onSize(wxSizeEvent& event)
{
	Layout();
	Refresh();
}

void TEDialog::initLayout(LibraryTemplateItem* templateItem)
{
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

	wxgui::LibraryPanel* libraryPanel = new wxgui::LibraryPanel(this);
	libraryPanel->addPage(new wxgui::LibraryImagePage(libraryPanel->getNotebook()));
	libraryPanel->loadFromSymbolMgr(*wxgui::SymbolMgr::Instance());
	sizer->Add(libraryPanel, 1, wxEXPAND);

	TEEditPanel* editPanel = new TEEditPanel(this, libraryPanel, templateItem);
	sizer->Add(editPanel, 5, wxEXPAND);
	
	sizer->Add(new TEToolbar(this, editPanel, libraryPanel, m_propertyPanel));

	SetSizer(sizer);
}