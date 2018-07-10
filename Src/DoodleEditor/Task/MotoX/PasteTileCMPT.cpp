#include "PasteTileCMPT.h"
#include "PasteTileStaticCMPT.h"
#include "PasteTileRandomCMPT.h"
#include "PasteTileCombinationCMPT.h"
#include "PasteTileTemplateCMPT.h"
#include "StagePanel.h"

using namespace deditor::motox;

PasteTileCMPT::PasteTileCMPT(wxWindow* parent, const wxString& name, StagePanel* editPanel, 
							 wxgui::LibraryPanel* libraryPanel)
	: wxgui::AbstractEditCMPT(parent, name, editPanel)
{
	addChild(new PasteTileStaticCMPT(this, wxT("��ͨ"), editPanel, libraryPanel));
	addChild(new PasteTileRandomCMPT(this, wxT("���"), editPanel, libraryPanel));
	addChild(new PasteTileCombinationCMPT(this, wxT("���"), editPanel, libraryPanel));
	addChild(new PasteTileTemplateCMPT(this, wxT("ģ��"), editPanel, libraryPanel));
}

wxSizer* PasteTileCMPT::initLayout()
{
	return initChildrenLayout();
}
