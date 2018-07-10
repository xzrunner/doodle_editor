#include "RegularListItem.h"
#include <wx/statline.h>

using namespace GAME_FRUITS;

const wxString RegularListItem::TIP_DRAG_BEHAVIOR = wxT("drag in a behavior");

const wxSize RegularListItem::TIP_SIZE = wxSize(200, -1);

RegularListItem::RegularListItem(const wxString& name)
	: m_name(name)
{
	SetWidth(200);
	SetBackgroundColour(*wxBLACK);
}

void RegularListItem::createPanel(wxWindow* parent)
{
	REGULAR::CollapsiblePane* panel = new REGULAR::CollapsiblePane(parent, m_name);
	wxWindow* extend = panel->GetPane();
	wxSizer* sizer = createExtend(extend);
	extend->SetSizer(sizer);
	panel->Collapse(false);

	parent->GetSizer()->Add(new wxStaticLine(parent), 0, wxEXPAND);
	parent->GetSizer()->Add(panel, 0, wxEXPAND);
	parent->GetSizer()->Add(new wxStaticLine(parent), 0, wxEXPAND);
	parent->GetSizer()->AddSpacer(10);

	parent->Layout();
	parent->Refresh();
}