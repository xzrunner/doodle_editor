#include "PasteTileCombinationCMPT.h"
#include "PasteTileCombinationOP.h"
#include "StagePanel.h"

using namespace deditor::motox;

PasteTileCombinationCMPT::PasteTileCombinationCMPT(wxWindow* parent, const wxString& name,
										   StagePanel* editPanel, wxgui::LibraryPanel* libraryPanel)
	: wxgui::AbstractEditCMPT(parent, name, editPanel)
{
	m_editOP = new PasteTileCombinationOP(editPanel, libraryPanel, this);
}

wxSizer* PasteTileCombinationCMPT::initLayout()
{
	wxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	{
		m_randomOpenCheck = new wxCheckBox(this, wxID_ANY, wxT("Ëæ»ú"));
		m_randomOpenCheck->SetValue(false);
		topSizer->Add(m_randomOpenCheck);
	}
	return topSizer;
}