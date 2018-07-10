#include "Move.h"

using namespace GAME_FRUITS;
using namespace GAME_FRUITS::REGULAR;

Move::Move()
	: RegularListItem(wxT("Move"))
{
	SetText(m_name);
}

wxSizer* Move::createExtend(wxWindow* extend)
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(createAngleSetting(extend));
	sizer->Add(createSpeedSetting(extend));
	return sizer;	
}

wxSizer* Move::createAngleSetting(wxWindow* extend)
{
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->AddStretchSpacer(1);
	sizer->Add(new wxStaticText(extend, wxID_ANY, wxT("angle")), 0, wxALIGN_LEFT);
	sizer->AddStretchSpacer(1);
	m_angle = new wxTextCtrl(extend, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	sizer->Add(m_angle, 5, wxALIGN_RIGHT);
	sizer->AddStretchSpacer(1);
	return sizer;
}

wxSizer* Move::createSpeedSetting(wxWindow* extend)
{
	wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
	sizer->AddStretchSpacer(1);
	sizer->Add(new wxStaticText(extend, wxID_ANY, wxT("speed")), 0, wxALIGN_LEFT);
	sizer->AddStretchSpacer(1);
	m_speed = new wxTextCtrl(extend, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
	sizer->Add(m_speed, 5, wxALIGN_RIGHT);
	sizer->AddStretchSpacer(1);
	return sizer;
}