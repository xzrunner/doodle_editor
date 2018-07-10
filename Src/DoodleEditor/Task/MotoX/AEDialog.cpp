#include "AEDialog.h"
#include "AEEditPanel.h"
#include "AEToolbar.h"

#include <wxGUI/wxGUI.h>
#include <wx/splitter.h>

using namespace deditor::motox;

BEGIN_EVENT_TABLE(AEDialog, wxDialog)
	EVT_SIZE(AEDialog::onSize)
END_EVENT_TABLE()

AEDialog::AEDialog(wxWindow* parent, LibraryActorItem* params,
				   wxgui::PropertySettingPanel* propertyPanel)
 	: wxDialog(parent, wxID_ANY, "Edit Actor", wxDefaultPosition, 
	wxSize(800, 600), wxCLOSE_BOX | wxCAPTION | wxMAXIMIZE_BOX)
	, m_propertyPanel(propertyPanel)
{
	m_params = params;
	m_editPanel = NULL;
	initLayout();
}

AEDialog::~AEDialog()
{
	delete m_editPanel;
}

void AEDialog::onSize(wxSizeEvent& event)
{
	Layout();
	Refresh();
}

void AEDialog::initLayout()
{
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

	wxgui::LibraryPanel* libraryPanel = new wxgui::LibraryPanel(this);
	libraryPanel->addPage(new wxgui::LibraryImagePage(libraryPanel->getNotebook()));
	libraryPanel->loadFromSymbolMgr(*wxgui::SymbolMgr::Instance());
	sizer->Add(libraryPanel, 1, wxEXPAND);

	m_editPanel = new AEEditPanel(this, libraryPanel, *m_params);
	sizer->Add(m_editPanel, 5, wxEXPAND);
	
	sizer->Add(new AEToolbar(this, m_editPanel, libraryPanel, m_propertyPanel));

	SetSizer(sizer);
}