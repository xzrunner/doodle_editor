#include "LibraryPageBase.h"
#include <wx/listctrl.h>

using namespace GAME_FRUITS::VIEW;

LibraryPageBase::LibraryPageBase(wxWindow* parent)
	: wxWindow(parent, wxID_ANY)
{
	initLayout();
}

void LibraryPageBase::registerListener(wxChoice* lsn)
{
	m_listeners.push_back(lsn);

	std::vector<wxString> items;
	getAllItemsText(items);
	update(lsn, items);
}

void LibraryPageBase::updateListeners()
{
	std::vector<wxString> items;
	getAllItemsText(items);
	for (size_t i = 0, n = m_listeners.size(); i < n; ++i)
		update(m_listeners[i], items);
}

void LibraryPageBase::initLayout()
{
	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);

	wxBoxSizer* btnSizer = new wxBoxSizer(wxHORIZONTAL);
	m_add = new wxButton(this, wxID_ANY, "+", wxDefaultPosition, wxSize(20, 20));
	btnSizer->Add(m_add, 0, wxALL, 5);
	m_del = new wxButton(this, wxID_ANY, "-", wxDefaultPosition, wxSize(20, 20));
	btnSizer->Add(m_del, 0, wxALL, 5);
	topSizer->Add(btnSizer, 0, wxALIGN_RIGHT);

	m_listCtrl = new wxListCtrl(this);
	topSizer->Add(m_listCtrl, 1, wxEXPAND);

	SetSizer(topSizer);
}

void LibraryPageBase::getAllItemsText(std::vector<wxString>& items) const
{
	long item = -1;
	while (true)
	{
		item = m_listCtrl->GetNextItem(item);
		if (item == -1)
			break;

		wxListItem entry;
		entry.SetId(item);
		entry.SetMask(wxLIST_MASK_TEXT);
		m_listCtrl->GetItem(entry);
		items.push_back(entry.GetText());
	}
}

void LibraryPageBase::update(wxChoice* list, const std::vector<wxString>& items)
{
	list->Clear();
	for (size_t i = 0, n = items.size(); i < n; ++i)
		list->Append(items[i]);
	if (!items.empty()) list->SetSelection(0);
}