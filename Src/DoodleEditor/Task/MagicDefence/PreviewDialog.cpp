#include "PreviewDialog.h"
#include "PreviewCanvas.h"

using namespace deditor::magic_defence;

PreviewDialog::PreviewDialog(wxWindow* parent, StagePanel* stagePanel,
							 wxgui::LibraryPanel* libraryPanel)
 	: wxDialog(parent, wxID_ANY, wxT("Ô¤ÀÀ"), wxDefaultPosition, wxSize(800, 480), wxCLOSE_BOX | wxCAPTION)
{
	wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

	wxgui::EditPanel* editPanel = new wxgui::EditPanel(this);
	editPanel->setEditOP(new wxgui::NullEditOP(editPanel));
	editPanel->setCanvas(new PreviewCanvas(editPanel, stagePanel, libraryPanel));

	sizer->Add(editPanel, 1, wxEXPAND);
	SetSizer(sizer);
}