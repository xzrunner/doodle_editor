#include "PasteTileRandomCMPT.h"
#include "StagePanel.h"

using namespace deditor::motox;

PasteTileRandomCMPT::PasteTileRandomCMPT(wxWindow* parent, const wxString& name,
										 StagePanel* editPanel, wxgui::LibraryPanel* libraryPanel)
	: wxgui::AbstractEditCMPT(parent, name, editPanel)
{
	m_randomWidget = new wxgui::PasteSymbolRandomWidget(this, libraryPanel);

	addChild(new wxgui::UniversalCMPT(this, wxT("ÆÕÍ¨"), editPanel, 
		new wxgui::PasteSymbolRandomOP(editPanel, editPanel, libraryPanel, m_randomWidget)));
	addChild(new wxgui::PasteSymbolPhysicsCMPT(this, wxT("ÎïÀí"), editPanel, editPanel, libraryPanel, 
		editPanel, editPanel->getWorld(), editPanel->getWorldReverse(), NULL, m_randomWidget));
}

wxSizer* PasteTileRandomCMPT::initLayout()
{
	wxSizer* topSizer = new wxBoxSizer(wxVERTICAL);
	{
		topSizer->Add(m_randomWidget);
	}
	topSizer->AddSpacer(10);
	{
		topSizer->Add(initChildrenLayout());
	}
	return topSizer;
}