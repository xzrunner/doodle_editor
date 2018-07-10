#include "LibraryActorPage.h"
#include "LibraryActorList.h"
#include "LibraryActorItem.h"
#include "AEDialog.h"
#include "AETypes.h"

using namespace deditor::motox;

LibraryActorPage::LibraryActorPage(wxWindow* parent)
	: ILibraryPage(parent, wxT("人和车"))
{
	m_list = new LibraryActorList(this);
	initLayout();
}

bool LibraryActorPage::isHandleSymbol(wxgui::ISymbol* symbol) const
{
	return dynamic_cast<LibraryActorItem*>(symbol) != NULL;
}

void LibraryActorPage::registerContext(wxgui::PropertySettingPanel* propertyPanel,
									   wxgui::EditPanel* editPanel) 
{
	m_propertyPanel = propertyPanel;
	m_editPanel = editPanel;
	static_cast<LibraryActorList*>(m_list)->registerContext(propertyPanel, editPanel);
}

void LibraryActorPage::initLayout(bool draggable /*= true*/)
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	{
		wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);

		wxButton* btnNew = new wxButton(this, wxID_ANY, "new", wxDefaultPosition, wxSize(40, 20));
		Connect(btnNew->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(LibraryActorPage::onNewBtnPress));
		btnSizer->Add(btnNew, 0, wxRIGHT, 10);

		initButtons(btnSizer);

		sizer->Add(btnSizer, 0, wxALIGN_RIGHT);
	}
	{
		sizer->Add(m_list, 1, wxEXPAND);
	}
	SetSizer(sizer);
}

void LibraryActorPage::onAddPress(wxCommandEvent& event)
{
	wxString filter = wxT("*_") + ACTOR_FILE_TAG + wxT(".txt");
	wxFileDialog dlg(this, wxT("导入Actor文件"), wxEmptyString, 
		wxEmptyString, filter, wxFD_OPEN);
	if (dlg.ShowModal() == wxID_OK)
	{
		LibraryActorItem* params = new LibraryActorItem();
		params->loadFromFile(dlg.GetPath());
		m_list->insert(params);
	}
}

void LibraryActorPage::onNewBtnPress(wxCommandEvent& event)
{
	LibraryActorItem* params = new LibraryActorItem();
	m_list->insert(params);

	AEDialog dlg(this, params, m_propertyPanel);
	dlg.ShowModal();
	if (m_editPanel) 
		m_editPanel->resetCanvas();
}