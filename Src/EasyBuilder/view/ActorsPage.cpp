#include "ActorsPage.h"
#include "ActorItem.h"
#include "ActorsList.h"

using namespace ebuilder;

ActorsPage::ActorsPage(wxWindow* parent)
	: wxgui::ILibraryPage(parent, wxT("Actors"))
{
	initLayout();
}

bool ActorsPage::isHandleSymbol(wxgui::ISymbol* symbol) const
{
	return dynamic_cast<ActorItem*>(symbol) != NULL;
}

void ActorsPage::initLayout(bool draggable /*= true*/)
{
	wxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	initButtons(sizer);

	if (!m_list)
		m_list = new ActorsList(this);
	sizer->Add(m_list, 1, wxEXPAND);

	SetSizer(sizer);
}

void ActorsPage::onAddPress(wxCommandEvent& event)
{
}

void ActorsPage::initButtons(wxSizer* sizer)
{
	wxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);

// 	m_btnAdd = new wxButton(this, wxID_ANY, "+", wxDefaultPosition, wxSize(20, 20));
// 	Connect(m_btnAdd->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(ILibraryPage::onAddPress));
// 	btnSizer->Add(m_btnAdd, 0, wxLEFT | wxRIGHT, 5);

	m_btnDel = new wxButton(this, wxID_ANY, "-", wxDefaultPosition, wxSize(20, 20));
	Connect(m_btnDel->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, 
		wxCommandEventHandler(ActorsPage::onDelPress));
	btnSizer->Add(m_btnDel, 0, wxLEFT | wxRIGHT, 5);

	sizer->Add(btnSizer, 0, wxALIGN_RIGHT);
}