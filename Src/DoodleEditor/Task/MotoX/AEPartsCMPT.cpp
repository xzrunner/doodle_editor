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
	choices.Add(wxT("ͷ"));
	choices.Add(wxT("����"));
	choices.Add(wxT("���"));
	choices.Add(wxT("С��"));
	choices.Add(wxT("����"));
	choices.Add(wxT("С��"));
	choices.Add(wxT("ǰ��"));
	choices.Add(wxT("����"));
	choices.Add(wxT("����"));

	m_partChoice = new wxComboBox(this, wxID_ANY, wxT("����"), wxDefaultPosition, wxDefaultSize, choices);
	m_partChoice->SetSelection(0);

	wxStaticBox* bounding = new wxStaticBox(this, wxID_ANY, wxT("����"));
	wxBoxSizer* sizer = new wxStaticBoxSizer(bounding, wxVERTICAL);
	sizer->Add(m_partChoice);
	return sizer;
}