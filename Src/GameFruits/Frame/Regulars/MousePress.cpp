#include "MousePress.h"
#include <wx/statline.h>

using namespace GAME_FRUITS;
using namespace GAME_FRUITS::REGULAR;

MousePress::MousePress()
	: RegularListItem(wxT("Mouse Press"))
{
	SetText(m_name);
}

void MousePress::addRegular(RegularListItem* regular, bool isImpl)
{
	if (isImpl) m_implList.push_back(regular);
	else m_noImplList.push_back(regular);
}

bool MousePress::isDownChange() const
{
	return m_stateList->GetSelection() == 0;
}

const std::vector<RegularListItem*>& MousePress::getAllRegulars(bool isImpl) const
{
	if (isImpl) return m_implList;
	else return m_noImplList;
}

wxSizer* MousePress::createExtend(wxWindow* extend)
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	sizer->Add(createMouseStateListItem(extend));
	sizer->Add(new wxStaticLine(extend), 0, wxEXPAND);
	sizer->Add(createImplItem(extend));
	sizer->Add(new wxStaticLine(extend), 0, wxEXPAND);
	sizer->Add(createNotImplItem(extend));

	for (size_t i = 0, n = m_implList.size(); i < n; ++i)
		m_implList[i]->createPanel(m_extendImpl);
	for (size_t i = 0, n = m_noImplList.size(); i < n; ++i)
		m_noImplList[i]->createPanel(m_extendNoImpl);

	return sizer;
}

wxSizer* MousePress::createMouseStateListItem(wxWindow* extend)
{
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

	sizer->Add(new wxStaticText(extend, wxID_ANY, wxT("Mouse Event ")));

	wxString strings[2];
	strings[0] = "press";
	strings[1] = "lift";
	m_stateList = new wxChoice(extend, wxID_ANY, wxDefaultPosition, wxDefaultSize, 2, strings);
	m_stateList->SetSelection(0);
	sizer->Add(m_stateList);

	return sizer;
}

wxSizer* MousePress::createImplItem(wxWindow* extend)
{
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	CollapsiblePane* panel = new CollapsiblePane(extend, wxT("Satisfy"));

	m_extendImpl = panel->GetPane();
	m_extendImpl->SetDropTarget(new DragTarget(m_extendImpl, this, true));
	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	wxTextCtrl* text = new wxTextCtrl(panel->GetPane(), wxID_ANY, TIP_DRAG_BEHAVIOR, wxDefaultPosition, TIP_SIZE, wxTE_READONLY);
	topSizer->Add(text);
	m_extendImpl->SetSizer(topSizer);

	sizer->Add(panel);
	return sizer;
}

wxSizer* MousePress::createNotImplItem(wxWindow* extend)
{
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	CollapsiblePane* panel = new CollapsiblePane(extend, wxT("Not Satisfy"));

	m_extendNoImpl = panel->GetPane();
	m_extendNoImpl->SetDropTarget(new DragTarget(m_extendNoImpl, this, false));
	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	wxTextCtrl* text = new wxTextCtrl(panel->GetPane(), wxID_ANY, TIP_DRAG_BEHAVIOR, wxDefaultPosition, TIP_SIZE, wxTE_READONLY);
	topSizer->Add(text);
	m_extendNoImpl->SetSizer(topSizer);

	sizer->Add(panel);
	return sizer;
}

//////////////////////////////////////////////////////////////////////////
// class MousePress::DragTarget
//////////////////////////////////////////////////////////////////////////

MousePress::DragTarget::DragTarget(wxWindow* parent, MousePress* mousePress, bool isImpl)
	: DragRegularTarget(parent)
{
	m_mousePress = mousePress;
	m_isImpl = isImpl;
}

bool MousePress::DragTarget::OnDropText(wxCoord x, wxCoord y, const wxString& data)
{
	RegularListItem* regular = createRegular(data);
	if (regular)
	{
		regular->createPanel(m_parent);
		m_mousePress->addRegular(regular, m_isImpl);
	}

	return true;
}
