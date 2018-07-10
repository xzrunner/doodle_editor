#include "PersistentPage.h"
#include "SrcPanel.h"
#include "Frame/Regulars/Move.h"

#include <wxGUI/wxGUI.h>

using namespace GAME_FRUITS::VIEW::BACKSTAGE;

PersistentPage::PersistentPage(SrcPanel* parent)
	: SrcPageBase(parent)
{
	initFunctions();
	Connect(GetId(), wxEVT_COMMAND_LIST_BEGIN_DRAG, wxListEventHandler(PersistentPage::onDragInit));
	SetDropTarget(new wxgui::DragTargetNull);
}

void PersistentPage::initFunctions()
{
	InsertItem(*(new REGULAR::Move));
}

void PersistentPage::onDragInit(wxListEvent& event)
{
	wxTextDataObject tdo(GetItemText(event.GetIndex()));
	wxDropSource ds(tdo, this);
	ds.DoDragDrop(wxDrag_CopyOnly);
}