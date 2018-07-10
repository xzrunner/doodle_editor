#include "ScaleSize.h"
#include <wx/spinctrl.h>

using namespace GAME_FRUITS::REGULAR;

ScaleSize::ScaleSize()
	: RegularListItem(wxT("Size Scale"))
{
	m_scaleCtrl = NULL;
	SetText(m_name);
}

float ScaleSize::getScaleValue() const
{
	return m_scaleCtrl->GetValue() * 0.01f;
}

wxSizer* ScaleSize::createExtend(wxWindow* extend)
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(createSetValueItem(extend));
	return sizer;
}

wxSizer* ScaleSize::createSetValueItem(wxWindow* extend)
{
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

	sizer->Add(new wxStaticText(extend, wxID_ANY, wxT("Scale to: ")));

	m_scaleCtrl = new wxSpinCtrl(extend, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 
		wxSP_ARROW_KEYS, 50, 200, 100, wxT("%"));
	sizer->Add(m_scaleCtrl, 0, wxALIGN_LEFT);

	sizer->Add(new wxStaticText(extend, wxID_ANY, wxT("  %")));

	return sizer;
}