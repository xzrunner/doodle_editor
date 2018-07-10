#include "PreviewDialog.h"
#include "PreviewPanel.h"
#include "StagePanel.h"

using namespace deditor::modeling;

PreviewDialog::PreviewDialog(StagePanel* stagePanel, 
							 wxgui::LibraryPanel* libraryPanel)
 	: wxDialog(stagePanel, wxID_ANY, wxT("Ô¤ÀÀ"), wxDefaultPosition, 
	wxSize(800, 600), wxCLOSE_BOX | wxCAPTION)
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);
	sizer->Add(new PreviewPanel(this, stagePanel, libraryPanel), 1, wxEXPAND);
	SetSizer(sizer);
}