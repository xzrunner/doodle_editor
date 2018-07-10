#include "TileEditCMPT.h"
#include "TileIOCMPT.h"
#include "StagePanel.h"

using namespace deditor::hill_climb;

TileEditCMPT::TileEditCMPT(wxWindow* parent, const wxString& name, StagePanel* editPanel, 
						   wxgui::LibraryPanel* libraryPanel, wxgui::PropertySettingPanel* propertyPanel)
	: wxgui::AbstractEditCMPT(parent, name, editPanel)
{
	addChild(new TileIOCMPT(this, wxT("输入输出"), editPanel, libraryPanel));
	addChild(new wxgui::UniversalCMPT(this, wxT("粘贴元件"), editPanel, 
		new wxgui::PasteSymbolOP(editPanel, editPanel, libraryPanel)));
	addChild(new wxgui::UniversalCMPT(this, wxT("调整元件"), editPanel, 
		new wxgui::ArrangeSpriteOP<wxgui::SelectSpritesOP>(editPanel, editPanel, propertyPanel)));
}

wxSizer* TileEditCMPT::initLayout()
{
	return initChildrenLayout();
}