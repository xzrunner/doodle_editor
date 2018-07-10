#include "AEPartsCMPT.h"
#include "AEEditPanel.h"
#include "AEPartsOP.h"

using namespace deditor::motox;

AEPartsCMPT::AEPartsCMPT(wxWindow* parent, const wxString& name,
						 AEEditPanel* editPanel,
						 wxgui::PropertySettingPanel* propertyPanel)
	: wxgui::AbstractEditCMPT(parent, name, editPanel)
{
	m_editOP = new AEPartsOP(editPanel, this, propertyPanel);
}

wxSizer* AEPartsCMPT::initLayout()
{
	wxArrayString choices;
	choices.Add(wxT("头"));
	choices.Add(wxT("身体"));
	choices.Add(wxT("大臂"));
	choices.Add(wxT("小臂"));
	choices.Add(wxT("大腿"));
	choices.Add(wxT("小腿"));
	choices.Add(wxT("前轮"));
	choices.Add(wxT("后轮"));
	choices.Add(wxT("车身"));

	m_partChoice = new wxComboBox(this, wxID_ANY, wxT("部件"), wxDefaultPosition, wxDefaultSize, choices);
	m_partChoice->SetSelection(0);

	wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("部件"));
	wxBoxSizer* sizer = new wxStaticBoxSizer(bounding, wxVERTICAL);
	sizer->Add(m_partChoice);
	return sizer;
}