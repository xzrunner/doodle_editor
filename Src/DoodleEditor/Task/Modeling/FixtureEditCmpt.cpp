#include "FixtureEditCmpt.h"
#include "StagePanel.h"
#include "SelectFixtureOP.h"

using namespace deditor::modeling;

FixtureEditCmpt::FixtureEditCmpt(wxWindow* parent, const wxString& name, 
								 StagePanel* editPanel, wxgui::PropertySettingPanel* propertyPanel)
	: wxgui::AbstractEditCMPT(parent, name, editPanel)
{
	m_editOP = new SelectFixtureOP(editPanel, propertyPanel);
}

wxSizer* FixtureEditCmpt::initLayout()
{
	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	return topSizer;
}