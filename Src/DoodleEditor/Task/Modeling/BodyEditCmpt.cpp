#include "BodyEditCmpt.h"
#include "StagePanel.h"
#include "SelectBodyOP.h"

using namespace deditor::modeling;

BodyEditCmpt::BodyEditCmpt(wxWindow* parent, const wxString& name, 
						   StagePanel* editPanel, wxgui::PropertySettingPanel* propertyPanel)
	: wxgui::AbstractEditCMPT(parent, name, editPanel)
{
	m_editOP = new wxgui::ArrangeSpriteOP<SelectBodyOP>(editPanel, editPanel, propertyPanel, NULL, false);
}

wxSizer* BodyEditCmpt::initLayout()
{
	wxBoxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	return topSizer;
}